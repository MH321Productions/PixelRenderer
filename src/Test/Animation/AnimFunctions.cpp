#include <cmath>

#include "AnimTest.hpp"

const double Functions::pi = 3.14159265358979323846;
const double Functions::pi2 = 2 * pi;

double Functions::sin(const int& image, const int& range) {
    double scalar = pi2 / range;
    return std::sin(image * scalar);
}

double Functions::cos(const int& image, const int& range) {
    double scalar = pi2 / range;
    return std::cos(image * scalar);
}
