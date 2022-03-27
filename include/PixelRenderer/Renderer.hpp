#pragma once

#include <array>
//#include "Geometry.hpp"

using rgb = unsigned char;

class Texture;        //Texture/Texture.hpp
class Font;             //2D/Font.hpp
class String32;         //2D/Unicode.cpp
class Point;            //2D/Geometry.hpp
class Rect;             //2D/Geometry.hpp

class Color {
    private:
        void checkValue(const int& input, rgb& rgba);

    public:
        rgb r, g, b, a;

        Color(const rgb& r, const rgb& g, const rgb& b, const rgb& a): r(r), g(g), b(b), a(a) {}
        Color(const int& r, const int& g, const int& b, const int& a);
        Color(const Color& c) : r(c.r), g(c.g), b(c.b), a(c.a) {}
        Color(Color& c) : r(c.r), g(c.g), b(c.b), a(c.a) {}
        Color() : r(0), g(0), b(0), a(0) {}

        Color& operator = (const Color& c);
        Color& operator = (Color& c);
        Color operator + (Color& c) const;
        Color operator + (Color c) const;
        Color& operator += (Color& c);
        Color& operator += (const Color& c);
        Color operator - (Color& c) const;
        Color& operator -= (Color& c);
        Color operator * (const rgb& scalar) const;
        Color& operator *= (const rgb& scalar);
        Color operator / (const rgb& scalar) const;
        Color& operator /= (const rgb& scalar);
};

class Colors {
    private:
        Colors() {} //Wird nicht genutzt
    
    public:
        static const Color Transparent;
        static const Color Black;
        static const Color White;
        static const Color Red;
        static const Color Green;
        static const Color Blue;
        static const Color Yellow;
};

enum BoundResult{Inside = 0, Top = 1, Left = 2, Right = 4, Bottom = 8};

/**
 * Beschreibt die Skaliermethode, die der Renderer beim Skalieren von
 * Texturen nutzen soll
 */ 
enum ScalingMethod : char {Linear, Nearest};

/**
 * Der 2D Renderer, um GUIs, HUDs und ähnliches zu rendern.
 * Er muss in folgender Weise benutzt werden:
 * 1. setColor(Colors::Transparent)
 * 2. clear()
 * 3. Sämtliche Rendermethoden
 * 4. render(): Als letztes in der OpenGL Reihenfolge rendern
 */ 
class Renderer {
    private:
        Color* data; //Pixeldaten
        Color currentColor;
        
        int isOutside(const int& x, const int& y);
        Color& at(const int& x, const int& y);
        int getScaledPixel(const int& pixel, const double& scalar);
        double scalarX, scalarY;
        ScalingMethod method;

    public:
        const int width, height, pixelCount;

        Renderer(const int& width, const int& height);
        Renderer() : Renderer(1920, 1080) {}
        ~Renderer();

        //Rendermethoden
        /**
         * Leert die Daten und setzt alle Pixel auf die aktuell gesetzte Farbe
         */ 
        void clear();

        /**
         * Setzt die aktuelle Farbe
         * @param c Die zu setzende Farbe
         */ 
        void setColor(const Color& c);

        /**
         * Setzt die aktuelle Rendermethode
         * @param method Die zu verwendende Methode
         */ 
        void setScalingMethod(ScalingMethod method);

        /**
         * Sets one Pixel to the specified Color (with blending enabled)
         * @param x The x coordinate
         * @param y The y coordinate
         * @param c The color
         * @param setFullyOpaque If the alpha value should be set to 255 (instead of using the blended one)
         */ 
        void setPixelBlending(const int& x, const int& y, const Color& c, const bool& setFullyOpaque = true);

        /**
         * Sets one Pixel to the specified Color
         * @param x The x coordinate
         * @param y The y coordinate
         * @param c The color
         */ 
        void setPixel(const int& x, const int& y, const Color& c);

        /**
         * Returns the currently rendered pixel data for further processing
         */ 
        Color* getData();

        /**
         * Skaliert den Renderer auf eine neue Größe
         * @param width Die neue Breite in Pixeln
         * @param height Die neue Höhe in Pixeln
         */ 
        void resize(const int& width, const int& height);

        /**
         * Gibt die eingebene Position relativ zur Renderergröße aus,
         * damit die Koordinaten beim Skalieren des Fensters
         * konstant bleiben
         * 
         * @param x Die X-Koordinate der absoluten Position
         * @param y Die Y-Koordinate der absoluten Position
         * @returns Ein Punkt mit relativen Mauskoordinaten
         */ 
        Point getRelPos(const int& x, const int& y);

        /**
         * Gibt die eingebene Position relativ zur Renderergröße aus,
         * damit die Koordinaten beim Skalieren des Fensters
         * konstant bleiben
         * 
         * @param pos Die absolute Position
         * @returns Ein Punkt mit relativen Mauskoordinaten
         */ 
        Point getRelPos(const Point& pos);

        /**
         * Zeichnet den Rand eines Rechtecks mit der ausgewählten Farbe
         * 
         * @param rect Das zu zeichnende Rechteck
         * @param linesize Die Breite der Linien
         */ 
        void drawRect(const Rect& rect, const int& linesize = 1);

        /**
         * Zeichnet ein gefülltes Rechteck mit der ausgewählten Farbe
         * 
         * @param rect Das zu zeichnende Rechteck
         */ 
        void fillRect(const Rect& rect);

        /**
         * Zeichnet eine Textur (oder Teile davon)
         * @param texture Die zu kopierende Textur
         * @param src Der Ausschnitt der Textur, der kopiert werden soll, oder Rect::emptyRect für die ganze Textur
         * @param dest Der Ausschnitt des Bildes, in den kopiert werden soll, oder Rect::emptyRect für das ganze Bild
         */ 
        void drawTexture(Texture* texture, const Rect& src, const Rect& dest);

        /**
         * Rendert UTF-32 Text mit der ausgewählten Farbe
         * @param font Der Font, der den Text darstellen soll
         * @param text Der UTF-32 Text
         * @param x Der x-Wert der oberen linken Ecke
         * @param y Der y-Wert der oberen linken Ecke
         * @param size Die Schriftgröße in Pixeln
         * @param charSpacing Der Abstand zwischen zwei Buchstaben in Pixeln (Standardmäßig 1/10 der Schriftgröße)
         */ 
        void drawText(Font* font, const String32& text, const int& x, const int& y, const int& size, int charSpacing = -1);

        /**
         * Rendert die aktuellen FPS in die obere Linke Ecke mit der ausgewählten Farbe
         */ 
        void drawFPS(const int& fps, Font* font);
};