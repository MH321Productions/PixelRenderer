#include "AnimTest.hpp"
#include "PixelRenderer/Unicode.hpp"
#include "PixelRenderer/Geometry.hpp"

String32 texDescription = U"Render and scale textures";
String32 texFile = U"File", texMem = U"Memory";
Rect texTableVert {955, 130, 10, 950};
Rect texTableHor {0, 270, 1920, 10};
Rect texCross {10, 290, 18, 18};
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
    int offsetX, offsetY;

    if (image < 30) {
        scaleX = Functions::linUp(image, 30) * 910;
        scaleY = scaleX / 3.0;
        offsetX = (int) scaleX;
        offsetY = (int) scaleY;
    } else {
        scaleY = Functions::linUp(image - 30, 30) * 456.66666666666666 + 303.3333333333333;
        offsetX = 910;
        offsetY = (int) scaleY;
    }

    //file
    texCross.width = 18 + offsetX;
    texCross.height = 18 + offsetY;
    renderer->drawTexture(cross, Rect::emptyRect, texCross);


    //memory
    texCheck.width = 21 + offsetX;
    texCheck.height = 20 + offsetY;
    renderer->drawTexture(check, Rect::emptyRect, texCheck);
}