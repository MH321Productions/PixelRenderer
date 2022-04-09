#include "AnimTest.hpp"
#include "PixelRenderer/Unicode.hpp"
#include "PixelRenderer/Geometry.hpp"

String32 description = U"Render basic shapes";
Rect fill, lineRect{120, 800, 200, 200};
int fillOffset, lineRectSize;

void AnimationTest::renderShapes(const int& image) {
    renderer->setColor(Colors::Green);
    renderer->setBlendingMethod(BlendingMethod::AlphaBlending);
    renderer->drawText(robotoFont, description, 80, 150, 180);
    renderer->setBlendingMethod(BlendingMethod::NoBlending);

    //Fill rect
    renderer->setColor(Colors::Red);
    fillOffset = (int) (Functions::sin(image, 60) * 100);
    fill = {120, 300, 200 + fillOffset, 200 + 2 * fillOffset};
    renderer->fillRect(fill);

    //Draw line rect
    renderer->setColor(Colors::Yellow);
    lineRectSize = (int) (Functions::linUp(image, 60) * 100);
    renderer->drawRect(lineRect, lineRectSize);

    //TODO: Render other shapes when they are implemented
}