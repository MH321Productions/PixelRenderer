#include <iostream>

#include "AnimTest.hpp"
#include "AnimPart.hpp"
#include "PixelRenderer/Geometry.hpp"

using namespace std;

SpriteInfo info(400, 400, 10, 4);
Rect animDest(100, 100, 400, 400);

void PartSprite::renderPart(const int& image) {
    anim->renderer->drawSpritesheet(anim->sprite, animDest, info, image / 2, true);
}