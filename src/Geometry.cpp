#include <iostream>

#include "PixelRenderer/Geometry.hpp"

using namespace std;

namespace PixelRenderer {
    
    const Rect Rect::emptyRect;

    bool Rect::isInside(const int& x, const int& y) {
        return x >= this->x && x < this->x + width && y >= this->y && y < this->y + height;
    }

    bool Rect::isInside(const Point& p) {
        return isInside(p.x, p.y);
    }

    bool SpriteInfo::isValid() const {
        return frames && frameWidth && frameHeight && framesPerRow;
    }
}