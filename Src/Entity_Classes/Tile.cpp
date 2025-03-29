#include "Tile.hpp"

Texture2D Tile::image;

Tile::Tile(Rectangle object, Vector2 frame):
    Sprite(object, frame)
{
    srcRect.width = image.width / 9;
    srcRect.height = image.height / 20;
}

Tile::~Tile() {
    
}

void Tile::update() {

    srcRect.x = srcRect.width * frame.x;
    srcRect.y = srcRect.height * frame.y;
    
    if(CheckCollisionRecs(Utils::getScreenRect(), object))
        draw(image);

    move();
}

void Tile::move() {

    object.x += velocity.x * GetFrameTime();
    object.y += velocity.y * GetFrameTime();

    velocity = {0.0f, 0.0f};
}