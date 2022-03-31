#include <cmath>

#include "AnimTest.hpp"

const double Functions::pi = 3.14159265358979323846;
const double Functions::full60 = (2 * pi) / 60.0;
const double Functions::full30 = (2 * pi) / 30.0;

double Functions::sin60(const int& image) {
    return sin(image * full60);
}

double Functions::cos60(const int& image) {
    return cos(image * full60);
}

double Functions::sin30(const int& image) {
    return sin(image * full30);
}

double Functions::cos30(const int& image) {
    return cos(image * full30);
}
