#include "utils.h"
#include "units.h"

Sensor::~Sensor() = default;

Sensor::Sensor(const double &x, const double &y,
               const double &theta, const double &radius,
               const vector<Target *> &targets) : pos(Vector<double>({x, y})) {
    this->theta = theta;
    this->radius = radius;
    for (Target *target: targets) {
        if (is_less_equal(get_distance(this->pos, target->pos), this->radius)) {
            this->targets_inside.push_back(target->id);
        }
    }
}

bool Sensor::is_covered(Target *target, const double &alpha) const &{
    if (in_list(target->id, this->targets_inside)) {
        Vector<double> f_vector({cos(alpha), sin(alpha)});
        Vector<double> v_vector = target->pos - this->pos;

        double angle = get_angle(f_vector, v_vector);
        return is_less_equal(angle, this->theta / 2);
    } else {
        return false;
    }
}
