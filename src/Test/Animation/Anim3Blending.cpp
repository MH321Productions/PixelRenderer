#include "AnimTest.hpp"
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

void AnimationTest::renderBlending(const int& image) {
    renderer->setColor(Colors::Green);
    renderer->setBlendingMethod(BlendingMethod::AlphaBlending);
    renderer->drawText(robotoFont, blendDescription, 80, 140, 150);
    renderer->drawText(robotoFont, blendNoBlending, 70, 280, 80);
    renderer->drawText(robotoFont, blendColor, 690, 280, 80);
    renderer->drawText(robotoFont, blendAlpha, 1330, 280, 80);

    //table
    renderer->setColor(Colors::Red);
    renderer->fillRect(blendTableLeft);
    renderer->fillRect(blendTableRight);
    renderer->fillRect(blendTableUp);

    //Figures
    double alpha = Functions::linUp(image, 55) * 255;
    c.setValue((int) alpha, c.a);
    renderer->setColor(c);

    renderer->setBlendingMethod(BlendingMethod::NoBlending);
    renderer->fillRect(blendFigNoBlending);

    renderer->setBlendingMethod(BlendingMethod::ColorBlending);
    renderer->fillRect(blendFigColor);

    renderer->setBlendingMethod(BlendingMethod::AlphaBlending);
    renderer->fillRect(blendFigAlpha);
}