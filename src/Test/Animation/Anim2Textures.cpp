#include "AnimTest.hpp"
#include "PixelRenderer/Unicode.hpp"
#include "PixelRenderer/Geometry.hpp"

String32 texDescription = U"Render and scale textures";
String32 texFile = U"File", texMem = U"RAM", texLinear = U"Linear scaling", texNearest = U"Nearest scaling";
Rect texTableVertLeft {200, 130, 10, 950};
Rect texTableVertRight {1060, 130, 10, 950};
Rect texTableHorTop {0, 210, 1920, 10};
Rect texTableHorBottom {0, 645, 1920, 10};

void AnimationTest::renderTextures(const int& image) {
    //Description text
    renderer->setColor(Colors::Green);
    renderer->setBlendingMethod(BlendingMethod::ColorBlending);
    renderer->drawText(robotoFont, texDescription, 20, 120, 150);
    renderer->drawText(robotoFont, texFile, 50, 440, 60);
    renderer->drawText(robotoFont, texMem, 35, 910, 60);
    renderer->drawText(robotoFont, texLinear, 420, 190, 60);
    renderer->drawText(robotoFont, texNearest, 1275, 190, 60);

    //create table
    renderer->setColor(Colors::Red);
    renderer->setBlendingMethod(BlendingMethod::NoBlending);
    renderer->fillRect(texTableVertLeft);
    renderer->fillRect(texTableVertRight);
    renderer->fillRect(texTableHorTop);
    renderer->fillRect(texTableHorBottom);
}