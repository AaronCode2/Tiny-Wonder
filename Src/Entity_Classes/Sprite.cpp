#include "Sprite.hpp"

Texture2D Sprite::image;

Sprite::Sprite(Rectangle object, Vector2 frame) {

    this->object = object;
    this->frame = frame;
    
    if(image.id == 0) {

        Sprite::image = LoadTexture("../Assets/Items/coin.png");
        image = Sprite::image;
    }

    srcRect.width = image.width / frame.x;
    srcRect.height = image.height / frame.y;
    srcRect.y = 0;
}

void Sprite::update() {
    
    srcRect.x = srcRect.width * currentFrame;

    animate(frame.x);
    draw();
}

void Sprite::draw(Texture2D image) {

    DrawTexturePro(
        image,
        srcRect, object,
        {0, 0}, 0, WHITE
    );
}

void Sprite::animate(const int frameEnd, const int frameStart, const float frameDuration) {

    elapsedFrame += GetFrameTime();

    if(elapsedFrame >= frameDuration) {
        
        elapsedFrame = 0.0f;

        if(currentFrame < frameEnd - 1) currentFrame++;
        else currentFrame = frameStart;
    }
}