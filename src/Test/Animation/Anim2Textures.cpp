#include "AnimTest.hpp"
#include "PixelRenderer/Unicode.hpp"
#include "PixelRenderer/Geometry.hpp"

String32 texDescription = U"Render and scale textures";
String32 texFile = U"File", texMem = U"Memory";
Rect texTableVert {955, 130, 10, 950};
Rect texTableHor {0, 270, 1920, 10};
Rect texFruitDest {10, 290, 935, 780};
Rect texFruitSrc {491, 0, 3913, 3264};
Rect texCheck {975, 290, 18, 18};

void AnimationTest::renderTextures(const int& image) {
    //description texts
    renderer->setColor(Colors::Green);
    renderer->setBlendingMethod(BlendingMethod::AlphaBlending);
    renderer->drawText(robotoFont, texDescription, 20, 120, 150);
    renderer->drawText(robotoFont, texFile, 400, 240, 100);
    renderer->drawText(robotoFont, texMem, 1275, 240, 100);

    //create table
    renderer->setColor(Colors::Red);
    renderer->fillRect(texTableVert);
    renderer->fillRect(texTableHor);

    //render images
    double scaleX, scaleY;

    //file
    renderer->drawTexture(cross, texFruitSrc, texFruitDest);

    //memory
    if (image < 30) {
        scaleX = Functions::linUp(image, 30) * 910;
        scaleY = scaleX / 3.0;
        texCheck.width = (int) scaleX;
        texCheck.height = (int) scaleY;
    } else {
        scaleY = Functions::linUp(image - 30, 30) * 456.66666666666666 + 303.3333333333333;
        texCheck.width = 910;
        texCheck.height = (int) scaleY;
    }
    renderer->drawTexture(check, Rect::emptyRect, texCheck);
}