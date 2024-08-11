#ifndef PROBLEM_H_
#define PROBLEM_H_

#include "units.h"
#include <stdio.h>
#include<cmath>

class Problem {
public:
    vector<Target *> targets;
    vector<Sensor *> sensors;

    Problem(const vector<Target *> &, const vector<Sensor *> &);

    ~Problem();

    void heuristic_initialize(Individual *p);

    void heuristic_initialize_by_max(Individual *p, const function<bool(pair<int, int>, pair<int, int>)> &);

    pair<int, int> get_coverage_by_sensor(Sensor *sensor, const double &alpha);

    vector<int> get_coverage(Individual *p);

    Vector<double> CCQ(Individual *p);

    Vector<double> DCCQ(Individual *p1, Individual *p2);

    Vector<double> RCCQ(Individual *p1, Individual *p2);

    static int count_active_sensor(Individual *p);

    double QBI(Individual *p);

    double CQ(Individual *p);

    double DI(Individual *p);

    double PC(Individual *p);

    pair<double, int> evaluate(Individual *p);

    static Problem *read_problem(const string &);
};

#endif // PROBLEM_H_
