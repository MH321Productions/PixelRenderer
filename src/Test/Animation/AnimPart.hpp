#pragma once

#include <string>

class AnimationTest;

class Part {
    protected:
        AnimationTest* anim;
    
    public:
        std::string name, videoName;
        virtual void renderPart(const int& image) = 0;

        Part(AnimationTest* anim, const std::string& name, const std::string& videoName): anim(anim), name(name), videoName(videoName) {}
};

class PartShapes: public virtual Part {
    public:
        virtual void renderPart(const int& image);

        PartShapes(AnimationTest* anim) : Part(anim, "Shapes", "Shapes.mp4") {}
};

class PartTexture: public virtual Part {
    public:
        virtual void renderPart(const int& image);

        PartTexture(AnimationTest* anim) : Part(anim, "Textures", "Textures.mp4") {}
};

class PartBlend: public virtual Part {
    public:
        virtual void renderPart(const int& image);

        PartBlend(AnimationTest* anim) : Part(anim, "Blending", "Blending.mp4") {}
};

class PartRepetition: public virtual Part {
    public:
        virtual void renderPart(const int& image);

        PartRepetition(AnimationTest* anim) : Part(anim, "Repetition", "Repetition.mp4") {}
};

class PartFont: public virtual Part {
    public:
        virtual void renderPart(const int& image);

        PartFont(AnimationTest* anim) : Part(anim, "Fonts", "Fonts.mp4") {}
};

class PartSprite: public virtual Part {
    public:
        virtual void renderPart(const int& image);

        PartSprite(AnimationTest* anim) : Part(anim, "Sprites", "Sprites.mp4") {}
};