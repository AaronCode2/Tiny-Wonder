#pragma once
#include <raylib.h>

class Sprite {

    public:

        Sprite(Rectangle object, Vector2 frame);

        void update();

        static Texture2D image;

    protected:

        Rectangle object;
        Rectangle srcRect;
        Vector2 frame;

        void draw(Texture2D image);
        void animate(int frameEnd, int frameStart = 0, float frameDuration = 0.1f);

        int currentFrame = 0;
        float elapsedFrame = 0;
};