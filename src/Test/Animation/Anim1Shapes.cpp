#include "AnimTest.hpp"
#include "PixelRenderer/Unicode.hpp"

static String32 description = U"Render basic shapes";

void AnimationTest::renderShapes(const int& image) {
    renderer->setColor(Colors::Green);
    renderer->setBlendingMethod(BlendingMethod::ColorBlending);
    renderer->drawText(robotoFont, description, 80, 150, 180);
}