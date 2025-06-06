#pragma once
#include <raylib.h>

class Sprite {

    public:

        Sprite(Rectangle object, Vector2 frame);

        void update();

        Rectangle getObject() { return object; };
        Vector2 getFrame() { return frame; }; 

        static Texture2D image;
        Rectangle object;
        
    protected:
        
        Vector2 velocity;
        Rectangle srcRect;
        Vector2 frame;

        void draw(Texture2D image);
        void animate(int frameEnd, int frameStart = 0, float frameDuration = 0.1f);

        int currentFrame = 0;
        float elapsedFrame = 0;
};