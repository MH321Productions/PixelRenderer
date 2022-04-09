#include "PixelRenderer/Renderer.hpp"

const Color Colors::Transparent;
const Color Colors::Black(0, 0, 0, 0xFF);
const Color Colors::White(0xFF, 0xFF, 0xFF, 0xFF);
const Color Colors::Red(0xFF, 0, 0, 0xFF);
const Color Colors::Green(0, 0xFF, 0, 0xFF);
const Color Colors::Blue(0, 0, 0xFF, 0xFF);
const Color Colors::Yellow(0xFF, 0xFF, 0, 0xFF);
const Color Colors::Magenta(0xFF, 0, 0xFF, 0xFF);

Color::Color(const int& r, const int& g, const int& b, const int& a) {
    setValue(r, Color::r);
    setValue(g, Color::g);
    setValue(b, Color::b);
    setValue(a, Color::a);
}

void Color::setValue(const int& input, rgb& rgba) {
    if (input < 0) rgba = 0;
    else if (input > 0xFF) rgba = 0xFF;
    else rgba = (rgb) input;
}

Color& Color::operator = (const Color& c) {
    r = c.r;
    g = c.g;
    b = c.b;
    a = c.a;

    return *this;
}

Color& Color::operator = (Color& c) {
    r = c.r;
    g = c.g;
    b = c.b;
    a = c.a;

    return *this;
}

Color Color::operator + (Color& c) const {
    return {r + c.r, g + c.g, b + c.b, a + c.a};
}

Color Color::operator + (const Color& c) const {
    return {r + c.r, g + c.g, b + c.b, a + c.a};
}

Color& Color::operator += (Color& c) {
    setValue(r + c.r, r);
    setValue(g + c.g, g);
    setValue(b + c.b, b);
    setValue(a + c.a, a);

    return *this;
}

Color& Color::operator += (const Color& c) {
    setValue(r + c.r, r);
    setValue(g + c.g, g);
    setValue(b + c.b, b);
    setValue(a + c.a, a);

    return *this;
}

Color Color::operator - (Color& c) const {
    return {r - c.r, g - c.g, b - c.b, a - c.a};
}

Color& Color::operator -= (Color& c) {
    setValue(r - c.r, r);
    setValue(g - c.g, g);
    setValue(b - c.b, b);
    setValue(a - c.a, a);

    return *this;
}

Color Color::operator * (const rgb& scalar) const {
    return {r * scalar, g * scalar, b * scalar, a * scalar};
}

Color& Color::operator *= (const rgb& scalar) {
    setValue(r * scalar, r);
    setValue(g * scalar, g);
    setValue(b * scalar, b);
    setValue(a * scalar, a);

    return *this;
}

Color Color::operator / (const rgb& scalar) const {
    return {r / scalar, g / scalar, b / scalar, a / scalar};
}

Color& Color::operator /= (const rgb& scalar) {
    setValue(r / scalar, r);
    setValue(g / scalar, g);
    setValue(b / scalar, b);
    setValue(a / scalar, a);

    return *this;
}

Color Color::operator * (const double& scalar) const {
    return {(rgb) (r * scalar), (rgb) (g * scalar), (rgb) (b * scalar), (rgb) (a * scalar)};
}

Color& Color::operator *= (const double& scalar) {
    setValue(r * scalar, r);
    setValue(g * scalar, g);
    setValue(b * scalar, b);
    setValue(a * scalar, a);

    return *this;
}

Color Color::operator / (const double& scalar) const {
    return {(rgb) (r / scalar), (rgb) (g / scalar), (rgb) (b / scalar), (rgb) (a / scalar)};
}

Color& Color::operator /= (const double& scalar) {
    setValue(r / scalar, r);
    setValue(g / scalar, g);
    setValue(b / scalar, b);
    setValue(a / scalar, a);

    return *this;
}