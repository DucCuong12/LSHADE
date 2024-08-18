#include "DE.h"
#include "problem.h"

DE::DE(Problem *problem) {
    this->problem = problem;
    this->D = (int) problem->sensors.size();
    this->INIT_POPULATION_SIZE = 10 * this->D;
    this->BATCH_SIZE = 8;
    this->POPULATION_SIZE = this->INIT_POPULATION_SIZE;
    this->ARCHIVE_SIZE = (int) this->NA * this->POPULATION_SIZE;
    this->F = vector<double>(this->POPULATION_SIZE, 0);
    this->CR = vector<double>(this->POPULATION_SIZE, 0);
    this->MF = vector<double>(this->H, 0.5);
    this->MCR = vector<double>(this->H, 0.5);
}

void DE::initialize() {
    for (int i = 0; i < this->POPULATION_SIZE; i++)
        this->population.push_back(new Individual(this->D));
    int s1 = (int) (0.5 * this->POPULATION_SIZE);
    int s2 = (int) (0.8 * this->POPULATION_SIZE);
    int s3 = (int) (0.9 * this->POPULATION_SIZE);
    for (int i = s1; i < s2; i++)
        this->problem->heuristic_initialize(this->population[i]);
    for (int i = s2; i < s3; i++)
        this->problem->heuristic_initialize_by_max(this->population[i],
                                                   [](pair<int, int> pair1, pair<int, int> pair2) {
                                                       if (pair1.second == pair2.second)
                                                           return pair1.first > pair2.first;
                                                       return pair1.second > pair2.second;
                                                   });
    for (int i = s3; i < this->POPULATION_SIZE; i++)
        this->problem->heuristic_initialize_by_max(this->population[i],
                                                   [](pair<int, int> pair1, pair<int, int> pair2) {
                                                       return pair1 > pair2;
                                                   });
    for (Individual *p: this->population)
        p->fitness = this->problem->evaluate(p);
    sort(this->population.begin(), this->population.end(), compare_individual);
}

Individual *DE::get_best() {
    Individual *best = this->population[0];
    for (auto p: this->population) {
        if ((is_less_than(best->fitness.first, p->fitness.first)) ||
            (is_equal(best->fitness.first, p->fitness.first) &&
             best->fitness.second < p->fitness.second))
            best = p;
    }
    return best;
}

// Individual *DE::mutate(Individual *i1, Individual *i2, Individual *ik, Individual *best, int k) {
//     auto *vk = new Individual(i1->dim);
//     vk->state = i1->state - i2->state;
//     for (int i = 0; i < vk->dim; i++) {
//         if (random.random() < this->F[k]) {
//             if (vk->state[i] > 0)       
//                 vk->state.set(i, 0);
//             else if (vk->state[i] < 0)
//                 vk->state.set(i, 1);
//             else
//                 vk->state.set(i, ik->state[i]);
//         } else
//             vk->state.set(i, ik->state[i]);
//     }

//     Vector<double> custom_F = this->problem->RCCQ(best, ik) * this->F[k];
//     vk->direction = ik->direction + custom_F * (best->direction - ik->direction)
//                     + (i1->direction - i2->direction) * this->F[k];
//     for (int i = 0; i < vk->dim; i++) {
//         while (vk->direction[i] < 0)
//             vk->direction.set(i, vk->direction[i] + D_PI);
//         while (vk->direction[i] > D_PI)
//             vk->direction.set(i, vk->direction[i] - D_PI);
//     }
//     return vk;
// }

Individual *DE::mutate(Individual *i1, Individual *i2, Individual *ik, Individual *best, int k) {
    auto *vk = new Individual(i1->dim);
    vk->state = i1->state - i2->state;
    for (int i = 0; i < vk->dim; i++) {
        if (random.random() < this->F[k]) {
            if (vk->state[i] > 0)       
                vk->state.set(i, 0);
            else if (vk->state[i] < 0)
                vk->state.set(i, 1);
            else
                vk->state.set(i, ik->state[i]);
        } else
            vk->state.set(i, ik->state[i]);
    }

    // Vector<double> custom_F = this->problem->RCCQ(best, ik) * this->F[k];
    vk->direction = ik->direction + (best->direction - ik->direction) * this->F[k]
                    + (i1->direction - i2->direction) * this->F[k];
    for (int i = 0; i < vk->dim; i++) {
        while (vk->direction[i] < 0)
            vk->direction.set(i, vk->direction[i] + D_PI);
        while (vk->direction[i] > D_PI)
            vk->direction.set(i, vk->direction[i] - D_PI);
    }
    return vk;
}

// Individual *DE::crossover(Individual *ik, Individual *vk, int j, int k) {
//     auto *ok = new Individual(ik->dim);
//     for (int i = 0; i < ik->dim; i++) {
//         if (random.random() < this->CR[k])
//             ok->state.set(i, vk->state[i]);
//         else
//             ok->state.set(i, ik->state[i]);
//     }
//     Vector<double> denta = this->problem->DCCQ(vk, ik);


//     for (int i = 0; i < ik->dim; i++) {
//         if (random.random() < this->CR[k] + denta[i])
//             ok->direction.set(i, vk->direction[i]);
//         else
//             ok->direction.set(i, ik->direction[i]);
//     }

//     ok->state.set(j, vk->state[j]);
//     ok->direction.set(j, vk->direction[j]);

//     return ok;
// }

Individual *DE::crossover(Individual *ik, Individual *vk, int j, int k) {
    auto *ok = new Individual(ik->dim);
    for (int i = 0; i < ik->dim; i++) {
        if (random.random() < this->CR[k])
            ok->state.set(i, vk->state[i]);
        else
            ok->state.set(i, ik->state[i]);
    }
    Vector<double> denta = this->problem->DCCQ(vk, ik);


    for (int i = 0; i < ik->dim; i++) {
        if (random.random() < this->CR[k])
            ok->direction.set(i, vk->direction[i]);
        else
            ok->direction.set(i, ik->direction[i]);
    }

    ok->state.set(j, vk->state[j]);
    ok->direction.set(j, vk->direction[j]);

    return ok;
}

void DE::refactor(int k) {
    if (this->denta_f.empty())
        return;
    k = k % this->H;
    Vector<double> denta(this->denta_f);
    if (amax(denta) != 0) {
        Vector<double> w = denta / sum(denta);
        Vector<double> SetF(this->SF);
        Vector<double> SetCR(this->SCR);
        this->MF[k] = sum(w * SetF.square()) / sum(w * SetF);
        this->MCR[k] = sum(w * SetCR.square()) / sum(w * SetCR);
    }
    this->SF.clear();
    this->SCR.clear();
    this->denta_f.clear();
    this->denta_active.clear();
}

Individual *DE::reproduction_single(const int &k, const vector<Individual *> &sik2, const int &best_percent) {
    int k1 = random.randInt(0, POPULATION_SIZE, true);
    while (k1 == k)
        k1 = random.randInt(0, POPULATION_SIZE, true);

    int k2 = random.randInt(0, (int) sik2.size(), true);
    while (k2 == k || k2 == k1)
        k2 = random.randInt(0, (int) sik2.size(), true);
    auto *ik2 = sik2[k2];
    auto *ik = population[k];
    int k_best = random.randInt(0, best_percent);
    auto *vk = mutate(population[k1],
                      ik2,
                      ik,
                      population[k_best],
                      k);
    int j = random.randInt(0, vk->dim, true);
    auto ok = crossover(ik, vk, j, k);
    delete vk;
    ok->fitness = this->problem->evaluate(ok);
    return ok;
}

vector<Individual *> DE::reproduction_batch(const int &l, const int &r, const vector<Individual *> &sik2,
                                   const int &best_percent) {
    vector<Individual *> res;
    for (int i = l; i < r; i++)
        res.push_back(reproduction_single(i, sik2, best_percent));
    return res;
}

void DE::reproduction(int step_loop) {
    for (int i = 0; i < POPULATION_SIZE; i++) {
        int ri = random.randInt(0, this->H, true);
        this->F[i] = random.cauchy(this->MF[ri], this->std);
        while (this->F[i] < 0 || this->F[i] > 1)
            this->F[i] = random.cauchy(this->MF[ri], this->std);
        this->CR[i] = random.normal(this->MCR[ri], this->std);
        if (this->CR[i] > 1)
            this->CR[i] = 1;
        if (this->CR[i] < 0)
            this->CR[i] = 0;
    }

    vector<Individual *> sik2;
    sik2.reserve(population.size() + A.size());
    for (auto p: population)
        sik2.push_back(p);
    for (auto p: A)
        sik2.push_back(p);
    int best_percent = (int) (this->p_percent * POPULATION_SIZE);

    vector<future<vector<Individual *>>> futures;

    vector<Individual *> result;

    futures.reserve(POPULATION_SIZE);
    for (int k = 0; k < POPULATION_SIZE; k += BATCH_SIZE) {
        int lim = min(k + BATCH_SIZE, POPULATION_SIZE);
        futures.push_back(async(launch::async, &DE::reproduction_batch, this, k, lim, ref(sik2), best_percent));
    }

    for (int k = 0; k < POPULATION_SIZE; k += BATCH_SIZE) {
        auto batch_result = futures[k / BATCH_SIZE].get();
        int lim = min(BATCH_SIZE, POPULATION_SIZE - k);
        for (int i = 0; i < lim; i++)
            result.push_back(batch_result[i]);
    }
    futures.clear();

    for (int k = 0; k < POPULATION_SIZE; k++) {
        auto ik = population[k];
        auto ok = result[k];

        if (ok->fitness > ik->fitness) {
            population[k] = ok;
            this->SF.push_back(this->F[k]);
            this->SCR.push_back(this->CR[k]);
            this->denta_f.push_back(ok->fitness.first - ik->fitness.first);
            this->denta_active.push_back(ok->fitness.second - ik->fitness.second);
            this->A.push_back(ik);
        } else {
            delete ok;
        }
    }
    result.clear();
    this->POPULATION_SIZE = (int) round((double) (MIN_POPULATION_SIZE - INIT_POPULATION_SIZE)
                                        * step_loop / MAX_GENERATION + INIT_POPULATION_SIZE);
    sort(population.begin(), population.end(), compare_individual);
    ARCHIVE_SIZE = (int) (NA * POPULATION_SIZE);
//    while ((int) population.size() > POPULATION_SIZE) {
//        A.push_back(population.back());
//        population.pop_back();
//    }
    while ((int) A.size() > ARCHIVE_SIZE) {
        swap(A[random.randInt(0, (int) A.size(), true)], A.back());
        A.pop_back();
    }

}

Individual *DE::run(string output) {
    initialize();
    int cnt = 0;
    auto *best = get_best();
    history.push_back(best->fitness);
    for (int step_loop = 0; step_loop < MAX_GENERATION; step_loop++) {
        reproduction(step_loop);
        refactor(step_loop);
        auto best1 = get_best();
        if (best1->fitness > best->fitness)
            best = best1;
//        if (is_less_than(best1->fitness.first, best->fitness.first))
//            cnt++;
//        else if (is_equal(best1->fitness.first, best->fitness.first)) {
//            if (best1->fitness.second <= best->fitness.second)
//                cnt++;
//            else {
//                cnt = 0;
//                best = best1;
//            }
//        } else {
//            cnt = 0;
//            best = best1;
//        }
        history.push_back(best->fitness);
//        if (cnt == NUMBER_CONVERGE_ITERATION)
//            break;
    }
    return best;
}

bool DE::compare_individual(Individual *p1, Individual *p2) {
    if (is_equal(p1->fitness.first, p2->fitness.first))
        return p1->fitness.second > p2->fitness.second;
    return p1->fitness.first > p2->fitness.first;
}

DE::~DE() {
    delete this->problem;
    for (auto p: A)
        delete p;
    A.clear();
    this->problem = nullptr;
}
