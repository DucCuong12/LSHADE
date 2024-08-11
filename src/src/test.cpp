#include <stdio.h>
#include <cmath>

// Hàm để tính tích phân từ y đến x của 1 / (t + c)
double integrate(double y, double x) {
    return log((x + 1) / (y + 1));
}

// Hàm để tính delta(x, y)
double delta(double x, double y) {
    double integral_value = integrate(y, x);
    double normalization_factor = (log(x+1) > log(y+1)) ? log(x+1) : log(y+1);
    return integral_value / normalization_factor;
}

int main() {
    double x = 5.0;
    double y = 3.0;

    double result = delta(x, y);
    printf("Delta(x, y) = %f\n", result);

    return 0;
}
