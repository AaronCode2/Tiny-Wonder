#include "Tile.hpp"

Tile::Tile(Rectangle object, Vector2 frame):
    Sprite(object, frame)
{

}

Tile::~Tile() {
    
}

void Tile::update() {

    draw();
}