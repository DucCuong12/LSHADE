#ifndef DE_H_
#define DE_H_

#include "units.h"
#include "problem.h"
#include <future>

using namespace std;

class DE {
private:
    Problem *problem;
    int D;
    int MIN_POPULATION_SIZE = 4;
    int INIT_POPULATION_SIZE;
    int POPULATION_SIZE;
    int NA = 2;
    int MAX_GENERATION = 1000;
    int NUMBER_CONVERGE_ITERATION = 250;
    int ARCHIVE_SIZE;
    vector<Individual *> population;
    double p_percent = 0.05;
    int H = 6;
    int BATCH_SIZE = 8;
    double std = 0.1;
    vector<double> F;
    vector<double> CR;
    vector<double> MF;
    vector<double> MCR;
    vector<double> SF;
    vector<double> SCR;
    vector<double> denta_f;
    vector<double> denta_active;
    vector<Individual *> A;

    static bool compare_individual(Individual *p1, Individual *p2);

public:
    vector<pair<double, int>> history;

    explicit DE(Problem *);

    ~DE();

    void initialize();

    Individual *get_best();

    Individual *mutate(Individual *, Individual *, Individual *, Individual *, int);

    Individual *crossover(Individual *, Individual *, int, int);

    void refactor(int);

    void reproduction(int);

    Individual *run(string);

    Individual *reproduction_single(const int &, const vector<Individual *> &, const int &);

    vector<Individual *>
    reproduction_batch(const int &l, const int &r, const vector<Individual *> &sik2, const int &best_percent);
};

#endif // DE_H_
