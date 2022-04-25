#include "AnimTest.hpp"
#include "AnimPart.hpp"
#include "PixelRenderer/Unicode.hpp"
#include "PixelRenderer/Geometry.hpp"

String32 blendDescription = U"Different blending modes";
String32 blendNoBlending = U"No blending";
String32 blendColor = U"Color blending";
String32 blendAlpha = U"Alpha blending";
Rect blendTableLeft{630, 200, 15, 880};
Rect blendTableRight{1275, 200, 15, 880};
Rect blendTableUp{0, 300, 1920, 10};

Rect blendFigNoBlending{215, 595, 200, 200};
Rect blendFigColor{845, 595, 200, 200};
Rect blendFigAlpha{1490, 595, 200, 200};
Color c(0xFF, 0, 0, 0);

void PartBlend::renderPart(const int& image) {
    anim->renderer->setColor(Colors::Green);
    anim->renderer->setBlendingMethod(BlendingMethod::AlphaBlending);
    anim->renderer->drawText(anim->robotoFont, blendDescription, 80, 140, 150);
    anim->renderer->drawText(anim->robotoFont, blendNoBlending, 70, 280, 80);
    anim->renderer->drawText(anim->robotoFont, blendColor, 690, 280, 80);
    anim->renderer->drawText(anim->robotoFont, blendAlpha, 1330, 280, 80);

    //table
    anim->renderer->setColor(Colors::Red);
    anim->renderer->fillRect(blendTableLeft);
    anim->renderer->fillRect(blendTableRight);
    anim->renderer->fillRect(blendTableUp);

    //Figures
    double alpha = Functions::linUp(image, 55) * 255;
    c.setValue((int) alpha, c.a);
    anim->renderer->setColor(c);

    anim->renderer->setBlendingMethod(BlendingMethod::NoBlending);
    anim->renderer->fillRect(blendFigNoBlending);

    anim->renderer->setBlendingMethod(BlendingMethod::ColorBlending);
    anim->renderer->fillRect(blendFigColor);

    anim->renderer->setBlendingMethod(BlendingMethod::AlphaBlending);
    anim->renderer->fillRect(blendFigAlpha);
}