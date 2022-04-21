#pragma once

class Point {
    public:
        int x, y;
    
        Point(const int& x, const int& y) : x(x), y(y) {}
        Point() : x(0), y(0) {}
};

class Rect {
    public:
        int x, y, width, height;

        Rect(const int& x, const int& y, const int& width, const int& height) : x(x), y(y), width(width), height(height) {}

        /**
         * Initialize the rect as invalid
         */ 
        Rect() : x(0), y(0), width(0), height(0) {}
        
        /**
         * Initialize an invalid rect with a pointer (You can use NULL as a parameter in functions, like in SDL)
         * 
         * @param null a pointer (NULL/nullptr normally)
         */ 
        Rect(const void* null) : x(0), y(0), width(0), height(0) {}

        inline bool isValid() const {return x >= 0 && y >= 0 && width > 0 && height > 0;}
        bool isInside(const int& x, const int& y);
        bool isInside(const Point& p);

        /**
         * An invalid rect. You can use this instead of giving NULL as a parameter in functions
         */ 
        static const Rect emptyRect;
};
