#include "AnimTest.hpp"
#include "AnimPart.hpp"
#include "PixelRenderer/Unicode.hpp"
#include "PixelRenderer/Geometry.hpp"

PixelRenderer::String32 description = U"Render basic shapes";
PixelRenderer::Rect fill, lineRect{120, 800, 200, 200};
int fillOffset, lineRectSize;

void PartShapes::renderPart(const int& image) {
    anim->renderer->setColor(PixelRenderer::Colors::Green);
    anim->renderer->setBlendingMethod(PixelRenderer::BlendingMethod::AlphaBlending);
    anim->renderer->drawText(anim->robotoFont, description, 80, 150, 180);
    anim->renderer->setBlendingMethod(PixelRenderer::BlendingMethod::NoBlending);

    //Fill rect
    anim->renderer->setColor(PixelRenderer::Colors::Red);
    fillOffset = (int) (Functions::sin(image, 60) * 100);
    fill = {120, 300, 200 + fillOffset, 200 + 2 * fillOffset};
    anim->renderer->fillRect(fill);

    //Draw line rect
    anim->renderer->setColor(PixelRenderer::Colors::Yellow);
    lineRectSize = (int) (Functions::linUp(image, 60) * 100);
    anim->renderer->drawRect(lineRect, lineRectSize);

    //TODO: Render other shapes when they are implemented
}