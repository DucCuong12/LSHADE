#ifndef UNITS_H_
#define UNITS_H_

#include <bits/stdc++.h>

using namespace std;

#include "utils.h"
#include "myVector.h"


class Target {
public:

    Vector<double> pos;
    int q, id;

    ~Target();

    Target(const double &, const double &, const int &, const int &);
};

class Sensor {
public:

    Vector<double> pos;
    double theta, radius;
    vector<int> targets_inside;

    ~Sensor();

    Sensor(const double &, const double &, const double &, const double &, const vector<Target *> &);

    bool is_covered(Target *, const double &) const &;
};

class Individual {
public:
    int dim;
    pair<double, int> fitness;
    Vector<int> state;
    Vector<double> direction;
    Vector<double> CCQ;

    explicit Individual(int);

};

#endif // UNITS_H_
