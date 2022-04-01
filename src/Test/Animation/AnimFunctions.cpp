#include <cmath>

#include "AnimTest.hpp"

const double Functions::pi = 3.14159265358979323846;
const double Functions::pi2 = 2 * pi;
const double Functions::full60 = pi2 / 60.0;
const double Functions::full30 = pi2 / 30.0;

double Functions::sin60(const int& image) {
    return std::sin(image * full60);
}

double Functions::cos60(const int& image) {
    return std::cos(image * full60);
}

double Functions::sin30(const int& image) {
    return std::sin(image * full30);
}

double Functions::cos30(const int& image) {
    return std::cos(image * full30);
}

double Functions::sin(const int& image, const int& range) {
    double scalar = pi2 / range;
    return std::sin(image * scalar);
}

double Functions::cos(const int& image, const int& range) {
    double scalar = pi2 / range;
    return std::cos(image * scalar);
}
