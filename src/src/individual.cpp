#include "units.h"
#include <iostream>

Individual::Individual(int dim) :
        state(random.choice(Vector<int>({0, 1}), dim)),
        direction(random.uniform(0, D_PI, dim, true)){
    this->dim = dim;
    this->fitness = {0, 0};
}

int main()
    {
        cout<<0;
    }