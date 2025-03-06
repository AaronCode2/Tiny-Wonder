#include "Tile.hpp"

Texture2D Tile::image;

Tile::Tile(Rectangle object, Vector2 frame):
    Sprite(object, frame)
{

}

Tile::~Tile() {
    
}

void Tile::update() {

    srcRect.width = image.width / 9;
    srcRect.height = image.height / 20;
    srcRect.x = srcRect.width * frame.x;
    srcRect.y = srcRect.height * frame.y;

    draw(image);
}