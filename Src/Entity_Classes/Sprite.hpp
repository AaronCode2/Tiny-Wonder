#pragma once
#include <raylib.h>

class Sprite {

    public:

        Sprite(Rectangle object, Vector2 frame);

        void update();

        Rectangle getObject() const { return object; };
        Vector2 getFrame() const { return frame; }; 

        static Texture2D image;
        Rectangle object;
        
    protected:
        
        Vector2 velocity = {0, 0};
        Rectangle srcRect;
        Vector2 frame;

        void draw(Texture2D image);
        void animate(const int frameEnd, const int frameStart = 0, const float frameDuration = 0.1f);

        int currentFrame = 0;
        float elapsedFrame = 0;
};