#include "Sprite.hpp"

Texture2D Sprite::image;

Sprite::Sprite(Rectangle object, Vector2 frame) {

    this->object = object;
    this->frame = frame;
    
    srcRect.width = image.width / frame.x;
    srcRect.height = image.height / frame.y;
}

void Sprite::update() {
    
    srcRect.x = srcRect.width * currentFrame;
    srcRect.y = 0;

    animate(2);
    draw(image);
}

void Sprite::draw(Texture2D image) {

    DrawTexturePro(
        image,
        srcRect, object,
        {0, 0}, 0, WHITE
    );
}

void Sprite::animate(int frameEnd, int frameStart, float frameDuration) {

    elapsedFrame += GetFrameTime();

    if(elapsedFrame >= frameDuration) {
        
        elapsedFrame = 0.0f;

        if(currentFrame < frameEnd - 1) currentFrame++;
        else currentFrame = frameStart;
    }
}