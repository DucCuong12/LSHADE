#include <cmath>
#include<math.h>
#include<stdio.h>
#include "problem.h"
Problem::Problem(const vector<Target *> &targets, const vector<Sensor *> &sensors) {
    this->targets = targets;
    this->sensors = sensors;
}

Problem::~Problem() {
    for (auto p: this->sensors)
        delete p;
    this->sensors.clear();
    for (auto p: this->targets)
        delete p;
    this->targets.clear();
}

void Problem::heuristic_initialize(Individual *p) {
    for (int i = 0; i < (int) sensors.size(); i++) {
        Sensor *sensor = sensors[i];
        p->state.set(i, !sensor->targets_inside.empty());
        if (p->state[i]) {
            Target *target = targets[random.choice(Vector<int>(sensor->targets_inside))];
            Vector<double> v_vector = target->pos - sensor->pos;
            double angle = atan2(v_vector[1], v_vector[0]);
            double alpha = angle + random.uniform(-sensor->theta / 2, sensor->theta / 2);
            while (alpha < 0)
                alpha += D_PI;
            while (alpha > D_PI)
                alpha -= D_PI;
            p->direction.set(i, alpha);
        }
    }
}

void Problem::heuristic_initialize_by_max(Individual *p,
                                          const function<bool(pair<int, int>, pair<int, int>)> &cmp) {
    for (int i = 0; i < (int) sensors.size(); i++) {
        Sensor *sensor = sensors[i];
        p->state.set(i, !sensor->targets_inside.empty());
        if (p->state[i]) {
            double result_alpha = 0;
            vector<pair<pair<int, int>, double>> list_alpha;
            for (int target_id: sensor->targets_inside) {
                Target *target = targets[target_id];
                Vector<double> v_vector = target->pos - sensor->pos;
                double angle = atan2(v_vector[1], v_vector[0]);
                double alpha = angle - sensor->theta / 2;
                while (alpha < 0)
                    alpha += D_PI;
                while (alpha > D_PI)
                    alpha -= D_PI;

                pair<int, int> coverage = get_coverage_by_sensor(sensor, alpha);
                list_alpha.emplace_back(coverage, alpha);
                alpha = angle + sensor->theta / 2;
                while (alpha < 0)
                    alpha += D_PI;
                while (alpha > D_PI)
                    alpha -= D_PI;
                coverage = get_coverage_by_sensor(sensor, alpha);
                list_alpha.emplace_back(coverage, alpha);
            }
            sort(list_alpha.begin(), list_alpha.end(),
                 [&](pair<pair<int, int>, double> x, pair<pair<int, int>, double> y) {
                     return cmp(x.first, y.first);
                 });
            for (auto e: list_alpha) {
                result_alpha = e.second;
                if (random.random() <= 0.667)
                    break;
            }
            p->direction.set(i, result_alpha);
        }
    }

}

pair<int, int> Problem::get_coverage_by_sensor(Sensor *sensor, const double &alpha) {
    int q_is_covered = 0, number_is_covered = 0;
    for (int target_id: sensor->targets_inside)
        if (sensor->is_covered(targets[target_id], alpha)) {
            q_is_covered += targets[target_id]->q;
            number_is_covered++;
        }
    return {q_is_covered, number_is_covered};
}

vector<int> Problem::get_coverage(Individual *p) {
    vector<int> phi(targets.size());

    for (int i = 0; i < (int) sensors.size(); i++) {
        Sensor *sensor = sensors[i];
        if (!p->state[i])
            continue;
        double alpha = p->direction[i];
        for (int target_id: sensor->targets_inside) {
            if (sensor->is_covered(targets[target_id], alpha)) {
                phi[target_id] += 1;
            }
        }
    }

    for (int i = 0; i < (int) targets.size(); i++)
        phi[i] = min(phi[i], targets[i]->q);

    return phi;
}

Vector<double> Problem::CCQ(Individual *p) {
    if (p->CCQ.length == 0) {
        vector<double> phi(p->dim);
        for (int i = 0; i < (int) sensors.size(); i++) {
            Sensor *sensor = sensors[i];
            double alpha = p->direction[i];
            for (int target_id: sensor->targets_inside) {
                Vector<double> f_vector({cos(alpha), sin(alpha)});
                Vector<double> v_vector = targets[target_id]->pos - sensor->pos;
                double angle = get_angle(f_vector, v_vector);
                if (is_less_equal(angle, sensor->theta / 2))
                    phi[i] += 1;
                else
                    phi[i] += 1. / (1. + angle);
            }
        }
        p->CCQ = Vector<double>(phi);
        if (p->CCQ[0] < 0)
            cerr << 1;
    }
    return p->CCQ;
}

Vector<double> Problem::DCCQ(Individual *p1, Individual *p2) {
    Vector<double> xi1 = CCQ(p1);
    Vector<double> xi2 = CCQ(p2); 
    return maximum1(xi1, xi2);
}

Vector<double> Problem::RCCQ(Individual *p1, Individual *p2) {
    Vector<double> xi1 = CCQ(p1);
    Vector<double> xi2 = CCQ(p2);
    return xi1 / maximum(xi1, xi2);
}

int Problem::count_active_sensor(Individual *p) {
    int res = 0;
    for (int i = 0; i < p->dim; i++)
        res += p->state[i];
    return res;
}

double Problem::QBI(Individual *p) {
    vector<int> coverage = get_coverage(p);
    vector<double> tmp;
    tmp.reserve(coverage.size());
    for (auto x: coverage)
        tmp.push_back((double) x);
    Vector<double> phi(tmp);
    tmp.clear();
    tmp.reserve(coverage.size());
    for (auto target: targets)
        tmp.push_back(target->q);
    Vector<double> q(tmp);
    if (amax(phi) == 0)
        return 0;
    return (cube(sum(phi)) / cube(sum(q))) * (sum(q.square()) / sum(phi.square()));
}

double Problem::CQ(Individual *p) {
    double cq = 0;
    for (int i = 0; i < (int) sensors.size(); i++) {
        Sensor *sensor = sensors[i];
        for (int target_id: sensor->targets_inside)
            if (sensor->is_covered(targets[target_id], p->direction[i]))
                cq += 1 - square(get_distance(sensor->pos, targets[target_id]->pos) / sensor->radius);
    }
    return cq;
}

double Problem::DI(Individual *p) {
    vector<int> coverage = get_coverage(p);
    vector<double> tmp;
    tmp.reserve(coverage.size());
    for (auto x: coverage)
        tmp.push_back((double) x);
    Vector<double> phi(tmp);
    tmp.clear();
    tmp.reserve(coverage.size());
    for (auto target: targets)
        tmp.push_back(target->q);
    Vector<double> q(tmp);

    double numerator = sum((phi - q) * (phi - q));
    double denominator = sum(q * q);
    return 1 - numerator / denominator;
}

double Problem::PC(Individual *p) {
    double Pa = 5.268;
    double Ps = 0.058;
    double active = Pa * this->count_active_sensor(p);
    double inactive = Ps * (p->dim - this->count_active_sensor(p));
    return active + inactive;
}

pair<double, int> Problem::evaluate(Individual *p) {
    return {QBI(p), -count_active_sensor(p)};
}

Problem *Problem::read_problem(const string &input_path) {

    ifstream input_file(input_path);
    double theta, radius;
    input_file >> theta >> radius;
    theta = theta / 180.0 * M_PI;
    string tmp;
    input_file >> tmp;
    int n, m;
    input_file >> n;
    input_file >> m;
    vector<Sensor *> sensors(m);
    vector<Target *> targets(n);
    for (int i = 0; i < n; i++) {
        input_file >> tmp;
        vector<string> temp = split(tmp, ",");
        double x = stringToDouble(temp[0]);
        double y = stringToDouble(temp[1]);
        int q = stringToInt(temp[2]);
        targets[i] = new Target(x, y, q, i);
    }
    for (int i = 0; i < m; i++) {
        input_file >> tmp;
        vector<string> temp = split(tmp, ",");
        double x = stringToDouble(temp[0]);
        double y = stringToDouble(temp[1]);
        sensors[i] = new Sensor(x, y, theta, radius, targets);
    }
    input_file.close();
    return new Problem(targets, sensors);
}
