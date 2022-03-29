#include <iostream>
#include <sstream>
#include <cmath>

#include "PixelRenderer/Renderer.hpp"
#include "PixelRenderer/Texture.hpp"
#include "PixelRenderer/Font.hpp"
#include "PixelRenderer/Unicode.hpp"
#include "PixelRenderer/Geometry.hpp"

using namespace std;

Renderer::Renderer(const int& width, const int& height)
: width(width), height(height), pixelCount(width * height), scalarX(1.0), scalarY(1.0),
  scaling(ScalingMethod::Linear), blending(BlendingMethod::NoBlending) {
    //Daten vorbereiten
    data = new Color[pixelCount];
    currentColor = Colors::Transparent;

    cout << "2D Renderer initialisiert (" << width << " x " << height << ")" << endl;
}

Renderer::~Renderer() {
    delete[] data;
}

int Renderer::isOutside(const int& x, const int& y) {
    int result = BoundResult::Inside;

    if (x < 0) result |= BoundResult::Left;
    if (x >= width) result |= BoundResult::Right;
    if (y < 0) result |= BoundResult::Top;
    if (y >= height) result |= BoundResult::Bottom;

    return result;
}

Color& Renderer::at(const int& x, const int& y) {
    return data[y * width + x];
}

void Renderer::setPixel(const int& x, const int& y, const Color& c) {
    if (c.a == 255 || blending == BlendingMethod::NoBlending) at(x, y) = c;
    else if (!c.a) return;
    else {
        double gray = c.a / 255.0, invertGray = (255 - c.a) / 255.0;
        Color& pixel = at(x, y);
        pixel *= invertGray;
        pixel += (c * gray);
        if (blending == BlendingMethod::ColorBlending) pixel.a = 255;
    }
}

int Renderer::getScaledPixel(const int& pixel, const double& scalar) {
    double scaled = pixel * scalar;
    
    if (scaling == ScalingMethod::Nearest) return (int) round(scaled);
    else return (int) scaled;
}

void Renderer::drawRect(const Rect& rect, const int& linesize) {
    //Wenn das Rechteck komplett außerhalb des Fensters ist, wird abgebrochen (Die zwei Eckpunkte werden getestet)
    if (isOutside(rect.x, rect.y) && isOutside(rect.x + rect.width, rect.y + rect.height)) return;

    int lineOffsetY = 0, lineOffsetX = 0;
    int maxLinesizeX = rect.width - linesize, maxLinesizeY = rect.height - linesize;
    int boundResult;
    for (int y = rect.y; y < rect.y + rect.height; y++) {
        for (int x = rect.x; x < rect.x + rect.width; x++) {
            
            //Testen nach Grenzen
            boundResult = isOutside(x, y);
            //Oben, Unten oder Rechts außerhalb -> Neue Zeile
            //Links außerhalb -> nächster Pixel
            if (boundResult & BoundResult::Bottom || boundResult & BoundResult::Top || boundResult & BoundResult::Right) break;
            if (boundResult & BoundResult::Left) continue;

            //Zeichnen
            if (lineOffsetX < linesize || lineOffsetY < linesize || lineOffsetX >= maxLinesizeX || lineOffsetY >= maxLinesizeY) {
                at(x, y) = currentColor;
            }

            lineOffsetX++;
        }
        //Neue Zeile
        lineOffsetX = 0;
        lineOffsetY++;
    }
}

void Renderer::fillRect(const Rect& rect) {
    //Wenn das Rechteck komplett außerhalb des Fensters ist, wird abgebrochen (Die zwei Eckpunkte werden getestet)
    if (isOutside(rect.x, rect.y) && isOutside(rect.x + rect.width, rect.y + rect.height)) return;

    int boundResult;
    for (int y = rect.y; y < rect.y + rect.height; y++) {
        for (int x = rect.x; x < rect.x + rect.width; x++) {
            //Testen nach Grenzen
            boundResult = isOutside(x, y);
            //Oben, Unten oder Rechts außerhalb -> Neue Zeile
            //Links außerhalb -> nächster Pixel
            if (boundResult & BoundResult::Bottom || boundResult & BoundResult::Top || boundResult & BoundResult::Right) break;
            if (boundResult & BoundResult::Left) continue;

            //Zeichnen
            at(x, y) = currentColor;
        }
    }
}

void Renderer::drawTexture(Texture* texture, const Rect& src, const Rect& dest) {
    Rect rSrc, rDest;

    //Teste nach gültigkeit des Starts, sonst 0, 0, width, height
    if (src.isValid()) rSrc = src;
    else rSrc = {0, 0, texture->width, texture->height};

    //Teste nach Gültigkeit des Ziels, sonst 0, 0, renderWidth, renderHeight
    if (dest.isValid()) rDest = dest;
    else rDest = {0, 0, width, height};

    //Wenn das Rechteck komplett außerhalb des Fensters ist, wird abgebrochen (Die zwei Eckpunkte werden getestet)
    if (isOutside(rDest.x, rDest.y) && isOutside(rDest.x + rDest.width, rDest.y + rDest.height)) return;

    //Skalar berechnen
    double scX = rSrc.width / rDest.width;
    double scY = rSrc.height / rDest.height;

    int boundResult;
    for (int y = 0; y < rDest.height; y++) {
        for (int x = 0; x < rDest.width; x++) {
            //Testen nach Grenzen
            boundResult = isOutside(x + rDest.x, y + rDest.y);
            //Oben, Unten oder Rechts außerhalb -> Neue Zeile
            //Links außerhalb -> nächster Pixel
            if (boundResult & BoundResult::Bottom || boundResult & BoundResult::Top || boundResult & BoundResult::Right) break;
            if (boundResult & BoundResult::Left) continue;

            //Zeichnen
            if (texture->isOutside(x + rSrc.x, y + rSrc.y)) continue;//at(x + rDest.x, y + rDest.y) = Colors::Transparent;
            else at(x + rDest.x, y + rDest.y) = texture->at(getScaledPixel(x + rSrc.x, scX), getScaledPixel(y + rSrc.y, scY));
        }
    }
}

void Renderer::drawText(Font* font, const String32& text, const int& x, const int& y, const int& size, int charSpacing) {
    if (text.isEmpty() || size < 1 || !font->setSize(size)) return;

    int xPos = x;
    uint32_t glyphIndex;
    FT_GlyphSlot slot = font->face->glyph;
    FT_Bitmap map;
    if (charSpacing < 0) charSpacing = size / 10 + 1;
    int spaceSpacing = size / 2;
    Color temp;

    for (const uint32_t& i: text) {
        if (i == 32) {
            xPos += spaceSpacing;
            continue;
        }

        glyphIndex = FT_Get_Char_Index(font->face, i);
        if (!FontManager::checkFTError(
            FT_Load_Glyph(font->face, glyphIndex, FT_LOAD_DEFAULT),
            "Konnte Glyph nicht laden"
        )) continue;

        if (!FontManager::checkFTError(
            FT_Render_Glyph(slot, FT_RENDER_MODE_NORMAL),
            "Konnte Glyph nicht rendern"
        )) continue;

        //Über generierte Bitmap iterieren. Grayscale Wert als alpha setzen
        int index = 0;
        map = slot->bitmap;
        int boundResult;
        int startY = y - slot->bitmap_top;
        for (int tempY = y - slot->bitmap_top; tempY < y + map.rows - slot->bitmap_top; tempY++) {
            for (int tempX = xPos; tempX < xPos + map.width; tempX++) {

                //Testen nach Grenzen
                boundResult = isOutside(tempX, tempY);
                //Oben, Unten oder Rechts außerhalb -> Neue Zeile
                //Links außerhalb -> nächster Pixel
                if (boundResult & BoundResult::Bottom || boundResult & BoundResult::Top || boundResult & BoundResult::Right) break;
                if (boundResult & BoundResult::Left) continue;

                index = (tempY - startY) * map.width + (tempX - xPos);

                if (map.buffer[index] != 0) {
                    temp = currentColor;
                    temp.a = map.buffer[index];
                    setPixel(tempX, tempY, temp);
                }
            }
        }

        xPos += map.width + charSpacing;
    }

}

Color* Renderer::getData() {
    return data;
}

void Renderer::clear() {
    for (int i = 0; i < pixelCount; i++) {
        data[i] = currentColor;
    }
}

void Renderer::setColor(const Color& c) {
    currentColor = c;
}

void Renderer::setScalingMethod(ScalingMethod method) {
    scaling = method;
}

void Renderer::setBlendingMethod(BlendingMethod method) {
    blending = method;
}

void Renderer::resize(const int& width, const int& height) {
    if (width < 1 || height < 1) return;

    //Skalare Vorbereiten
    scalarX = (double) this->width / (double) width;
    scalarY = (double) this->height / (double) height;
}

Point Renderer::getRelPos(const int& x, const int& y) {
    return {(int) (x * scalarX), (int) (y * scalarY)};
}

Point Renderer::getRelPos(const Point& pos) {
    return {(int) (pos.x * scalarX), (int) (pos.y * scalarY)};
}

void Renderer::drawFPS(const int& fps, Font* font) {
    currentColor = Colors::Green;

    ostringstream str;
    str << fps;
    string s = str.str();
    str.clear();

    drawText(font, s, 10, 30, 40);
}