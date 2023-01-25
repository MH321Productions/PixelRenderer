#include "AnimTest.hpp"
#include "AnimPart.hpp"
#include "PixelRenderer/Unicode.hpp"
#include "PixelRenderer/Geometry.hpp"

PixelRenderer::String32 texDescription = U"Render and scale textures";
PixelRenderer::String32 texFile = U"File", texMem = U"Memory";
PixelRenderer::Rect texTableVert {955, 130, 10, 950};
PixelRenderer::Rect texTableHor {0, 270, 1920, 10};
PixelRenderer::Rect texFruitDest {10, 290, 935, 780};
PixelRenderer::Rect texFruitSrc {491, 0, 3913, 3264};
PixelRenderer::Rect texCheck {975, 290, 18, 18};

void PartTexture::renderPart(const int& image) {
    //description texts
    anim->renderer->setColor(PixelRenderer::Colors::Green);
    anim->renderer->setBlendingMethod(PixelRenderer::BlendingMethod::AlphaBlending);
    anim->renderer->drawText(anim->robotoFont, texDescription, 20, 120, 150);
    anim->renderer->drawText(anim->robotoFont, texFile, 400, 240, 100);
    anim->renderer->drawText(anim->robotoFont, texMem, 1275, 240, 100);

    //create table
    anim->renderer->setColor(PixelRenderer::Colors::Red);
    anim->renderer->fillRect(texTableVert);
    anim->renderer->fillRect(texTableHor);

    //render images
    double scaleX, scaleY;

    //file
    scaleX = Functions::linDown(image, 60);
    texFruitSrc.x = 2080 - (scaleX * 1589);
    texFruitSrc.y = 1694 - (scaleX * 1694);
    texFruitSrc.width = 935 + (scaleX * 2978);
    texFruitSrc.height = 780 + (scaleX * 2484);
    anim->renderer->drawTexture(anim->fruit, texFruitSrc, texFruitDest);    

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
    anim->renderer->drawTexture(anim->check, PixelRenderer::Rect::emptyRect, texCheck);
}