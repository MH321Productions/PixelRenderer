#include <iostream>

#include "AnimTest.hpp"
#include "AnimPart.hpp"
#include "PixelRenderer/Geometry.hpp"
#include "PixelRenderer/Unicode.hpp"

using namespace std;

PixelRenderer::SpriteInfo info(400, 400, 10, 4);
PixelRenderer::Rect animDest(100, 300, 400, 400);
PixelRenderer::String32 sprDescription = U"Render spritesheets";
PixelRenderer::Rect sprDest(800, 250, 1000, 750);
PixelRenderer::Rect sprFrame(0, 0, 250, 250);

void calculateFrame(const int& image);

void PartSprite::renderPart(const int& image) {
    anim->renderer->setColor(PixelRenderer::Colors::Green);
    anim->renderer->setBlendingMethod(PixelRenderer::BlendingMethod::AlphaBlending);
    anim->renderer->drawText(anim->robotoFont, sprDescription, 30, 180, 200);

    anim->renderer->drawSpritesheet(anim->sprite, animDest, info, image / 2, true);
    anim->renderer->drawTexture(anim->sprite, PixelRenderer::Rect::emptyRect, sprDest);

    calculateFrame(image);
    anim->renderer->setColor(PixelRenderer::Colors::Red);
    anim->renderer->drawRect(sprFrame, 5);
}

void calculateFrame(const int& image) {
    int realFrame = image % 10;
    sprFrame.x = (realFrame % 4) * 250 + sprDest.x; //Same calculation as in Sprite sheet, but with destination offset
    sprFrame.y = (realFrame / 4) * 250 + sprDest.y;
    cout << sprFrame.x << " " << sprFrame.y << endl;
}