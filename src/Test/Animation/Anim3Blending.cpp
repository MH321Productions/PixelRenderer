#include "AnimTest.hpp"
#include "AnimPart.hpp"
#include "PixelRenderer/Unicode.hpp"
#include "PixelRenderer/Geometry.hpp"

PixelRenderer::String32 blendDescription = U"Different blending modes";
PixelRenderer::String32 blendNoBlending = U"No blending";
PixelRenderer::String32 blendColor = U"Color blending";
PixelRenderer::String32 blendAlpha = U"Alpha blending";
PixelRenderer::Rect blendTableLeft{630, 200, 15, 880};
PixelRenderer::Rect blendTableRight{1275, 200, 15, 880};
PixelRenderer::Rect blendTableUp{0, 300, 1920, 10};

PixelRenderer::Rect blendFigNoBlending{215, 595, 200, 200};
PixelRenderer::Rect blendFigColor{845, 595, 200, 200};
PixelRenderer::Rect blendFigAlpha{1490, 595, 200, 200};
PixelRenderer::Color c(0xFF, 0, 0, 0);

void PartBlend::renderPart(const int& image) {
    anim->renderer->setColor(PixelRenderer::Colors::Green);
    anim->renderer->setBlendingMethod(PixelRenderer::BlendingMethod::AlphaBlending);
    anim->renderer->drawText(anim->robotoFont, blendDescription, 80, 140, 150);
    anim->renderer->drawText(anim->robotoFont, blendNoBlending, 70, 280, 80);
    anim->renderer->drawText(anim->robotoFont, blendColor, 690, 280, 80);
    anim->renderer->drawText(anim->robotoFont, blendAlpha, 1330, 280, 80);

    //table
    anim->renderer->setColor(PixelRenderer::Colors::Red);
    anim->renderer->fillRect(blendTableLeft);
    anim->renderer->fillRect(blendTableRight);
    anim->renderer->fillRect(blendTableUp);

    //Figures
    double alpha = Functions::linUp(image, 55) * 255;
    c.setValue((int) alpha, c.a);
    anim->renderer->setColor(c);

    anim->renderer->setBlendingMethod(PixelRenderer::BlendingMethod::NoBlending);
    anim->renderer->fillRect(blendFigNoBlending);

    anim->renderer->setBlendingMethod(PixelRenderer::BlendingMethod::ColorBlending);
    anim->renderer->fillRect(blendFigColor);

    anim->renderer->setBlendingMethod(PixelRenderer::BlendingMethod::AlphaBlending);
    anim->renderer->fillRect(blendFigAlpha);
}