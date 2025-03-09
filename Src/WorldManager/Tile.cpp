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

    draw(image);
}
