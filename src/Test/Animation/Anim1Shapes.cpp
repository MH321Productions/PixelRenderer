#include "AnimTest.hpp"
#include "PixelRenderer/Unicode.hpp"
#include "PixelRenderer/Geometry.hpp"

String32 description = U"Render basic shapes";
Rect fill, lineRect{120, 800, 200, 200};
int fillOffset, lineRectSize;

void AnimationTest::renderShapes(const int& image) {
    renderer->setColor(Colors::Green);
    renderer->setBlendingMethod(BlendingMethod::ColorBlending);
    renderer->drawText(robotoFont, description, 80, 150, 180);
    renderer->setBlendingMethod(BlendingMethod::NoBlending);

    //Fill rect
    renderer->setColor(Colors::Red);
    fillOffset = (int) (Functions::sin60(image) * 100);
    fill = {120, 300, 200 + fillOffset, 200 + 2 * fillOffset};
    renderer->fillRect(fill);

    //TODO: Draw line rect
    renderer->setColor(Colors::Yellow);
    lineRectSize = (int) (Functions::cos60(image) * 100);
    renderer->drawRect(lineRect, lineRectSize);

    //TODO: Render other shapes when they are implemented
}