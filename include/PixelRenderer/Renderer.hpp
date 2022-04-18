#pragma once

#include <array>

using rgb = unsigned char;

class Texture;          //Texture/Texture.hpp
class Font;             //2D/Font.hpp
class String32;         //2D/Unicode.cpp
class Point;            //2D/Geometry.hpp
class Rect;             //2D/Geometry.hpp

class Color {
    public:
        rgb r, g, b, a;

        Color(const rgb& r, const rgb& g, const rgb& b, const rgb& a): r(r), g(g), b(b), a(a) {}
        Color(const int& r, const int& g, const int& b, const int& a);
        Color(const Color& c) : r(c.r), g(c.g), b(c.b), a(c.a) {}
        Color(Color& c) : r(c.r), g(c.g), b(c.b), a(c.a) {}
        Color() : r(0), g(0), b(0), a(0) {}

        void setValue(const int& input, rgb& rgba);

        Color& operator = (const Color& c);
        Color& operator = (Color& c);
        Color operator + (Color& c) const;
        Color operator + (const Color& c) const;
        Color& operator += (Color& c);
        Color& operator += (const Color& c);
        Color operator - (Color& c) const;
        Color& operator -= (Color& c);
        Color operator * (const rgb& scalar) const;
        Color& operator *= (const rgb& scalar);
        Color operator / (const rgb& scalar) const;
        Color& operator /= (const rgb& scalar);
        Color operator * (const double& scalar) const;
        Color& operator *= (const double& scalar);
        Color operator / (const double& scalar) const;
        Color& operator /= (const double& scalar);
};

class Colors {
    private:
        Colors() {} //Isn't used
    
    public:
        static const Color Transparent;
        static const Color Black;
        static const Color White;
        static const Color Red;
        static const Color Green;
        static const Color Blue;
        static const Color Yellow;
        static const Color Magenta;
};

//Internal
enum BoundResult{Inside = 0, Top = 1, Left = 2, Right = 4, Bottom = 8};

/**
 * Contains the three different blending methods:
 * 1. NoBlending: No blending at all, just overwrite the pixel
 * 2. ColorBlending: Add the new color to the old color
 * 3. AlphaBlending: Blend between the old color and the new color
 */ 
enum class BlendingMethod : char {NoBlending, ColorBlending, AlphaBlending};

/**
 * Contains the three different repetition modes:
 * 1. X: only repeat the horizontal pixels, scale the vertical ones, if necessary
 * 2. Y: only repeat the vertical pixels, scale the horizontal ones, if necessary
 * 3: XY: repeat both horizontal and vertical pixels, equivalent to (X | Y)
 * The None option scales all pixels (it just redirects to drawTexture)
 */ 
enum RepetitionMode: char {None, X, Y, XY};

/**
 * The 2D Renderer to render GUIs, HUDs etc.
 * It works a bit like OpenGL as a state mashine.
 * The color for drawing shapes and texts, as well as the blending method
 * are saved and have to be set via setBlendingMethod/setColor.
 * 
 * The render sequence is roughly the following:
 * 1. setColor(Colors::Transparent)
 * 2. clear()
 * 3. render everything
 * 4. get the rendered data via getData() //TODO: Update docs after implementing callback rendering
 */ 
class Renderer {
    private:
        Color* data; //Pixel data
        Color currentColor;
        
        int isOutside(const int& x, const int& y);
        Color& at(const int& x, const int& y);
        inline int getScaledPixel(const int& pixel, const double& scalar);
        inline int getRepeatedPixel(const int& pixel, const int& srcBounds);
        Point getRepeatedPixel(Texture* texture, const Rect& src, const int& x, const int& y,
            const double& scX, const double& scY, RepetitionMode mode);
        
        double scalarX, scalarY;
        BlendingMethod blending;

    public:
        const int width, height, pixelCount;

        Renderer(const int& width, const int& height);
        Renderer() : Renderer(1920, 1080) {}
        ~Renderer();

        //Rendering methods
        /**
         * Clears the data and sets all pixels to the current color
         */ 
        void clear();

        /**
         * Sets the current color for the next rendering operations
         * @param c The new color
         */ 
        void setColor(const Color& c);

        /**
         * Set the current blending method for the next rendering operations
         * @param method The new method
         */ 
        void setBlendingMethod(BlendingMethod method);

        /**
         * Sets one Pixel to the specified Color (with the current blending mode)
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
         * Scales the renderer to a new relative size.
         * This doesn't affect the real size of the canvas,
         * it just affects the scalars for the getRelPos methods
         * @param width The new relative width
         * @param height Die new relative height
         */ 
        void resize(const int& width, const int& height);

        /**
         * Returns the relative position of the given coordinates.
         * If the renderer is scaled, it returns the coordinates on the renderer side.
         * An example:
         * If the renderer was initialized as 800x600 and then scaled
         * to a 400x300 window, the absolute (window) coordinate (1, 2) would return the
         * relative (renderer) coordinate (2, 4). This is useful for UIs on different
         * window sizes: The renderer renders in one size and gets scaled to the window,
         * but the relative coordinates stay the same.
         * 
         * @param x The x-coordinate of the absolute position
         * @param y The y-coordinate of the absolute position
         * @returns A Point with the relative position
         */ 
        Point getRelPos(const int& x, const int& y);

        /**
         * Returns the relative position of the given position.
         * If the renderer is scaled, it returns the coordinates on the renderer side.
         * An example:
         * If the renderer was initialized as 800x600 and then scaled
         * to a 400x300 window, the absolute (window) coordinates (1, 2) would return the
         * relative (renderer) coordinates (2, 4). This is useful for UIs on different
         * window sizes: The renderer renders in one size and gets scaled to the window,
         * but the relative coordinates stay the same.
         * 
         * @param pos The absolute position
         * @returns A Point with the relative position
         */ 
        Point getRelPos(const Point& pos);

        /**
         * Draws the outline of a rect with the current color and blending mode
         * 
         * @param rect The rect
         * @param linesize The width of the outlines
         */ 
        void drawRect(const Rect& rect, const int& linesize = 1);

        /**
         * Draws a filled rect with the current color and blending mode
         * 
         * @param rect The rect
         */ 
        void fillRect(const Rect& rect);

        /**
         * Draws a texture (or a part of it) with the current blending method
         * @param texture The texture
         * @param src The part of the texture that should be copied, or Rect::emptyRect/NULL for the whole texture
         * @param dest The part of the canvas that should be copied into, or Rect::emptyRect/NULL for the entire canvas
         */ 
        void drawTexture(Texture* texture, const Rect& src, const Rect& dest);

        /**
         * Draws a texture (or a part of it) with the current blending method and given repetition mode
         * @param texture The texture
         * @param src The part of the texture that should be copied, or Rect::emptyRect/NULL for the whole texture
         * @param dest The part of the canvas that should be copied into, or Rect::emptyRect/NULL for the entire canvas
         * @param mode The repetition mode
         */  
        void drawRepeatingTexture(Texture* texture, const Rect& src, const Rect& dest, RepetitionMode mode);

        //TODO: Update docs for text when more font methods are implemented
        /**
         * Draws UTF-32 text with the current color and blending mode
         * @param font The font to display the text
         * @param text The UTF-32 text
         * @param x The x-coordinate
         * @param y The y-coordinate
         * @param size The size (pixel)
         * @param charSpacing The spacing between two charakters (normally 1/10 of the size)
         */ 
        void drawText(Font* font, const String32& text, const int& x, const int& y, const int& size, int charSpacing = -1);
};