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
    scaleX = Functions::linDown(image, 60);
    texFruitSrc.x = 2080 - (scaleX * 1589);
    texFruitSrc.y = 1694 - (scaleX * 1694);
    texFruitSrc.width = 935 + (scaleX * 2978);
    texFruitSrc.height = 780 + (scaleX * 2484);
    renderer->drawTexture(cross, texFruitSrc, texFruitDest);    

    //memory
    if (image < 30) {
        scaleX = Functions::linUp(image, 30) * 910;
        scaleY = scaleX / 3.0;
        texCheck.width = 21 + (int) scaleX;
        texCheck.height = 20 + (int) scaleY;
    } else {
        scaleY = Functions::linUp(image - 30, 30) * 456.66666666666666 + 303.3333333333333;
        texCheck.width = 931;
        texCheck.height = 20 + (int) scaleY;
    }
    renderer->drawTexture(check, Rect::emptyRect, texCheck);
}