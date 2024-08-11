#include "units.h"

Target::~Target() = default;

Target::Target(const double &x, const double &y, const int &q, const int &id) : pos(Vector<double>({x, y})) {
    this->q = q;
    this->id = id;
}

