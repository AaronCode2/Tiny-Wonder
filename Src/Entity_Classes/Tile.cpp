#include "Tile.hpp"

Texture2D Tile::image;

Tile::Tile(Rectangle object, Vector2 frame, TileType tileType, Decoration decorationType):
    Sprite(object, frame)
{   

    this->tileType = tileType;
    this->decorationType = decorationType;

    srcRect.width = image.width / 9;
    srcRect.height = image.height / 20;
}

void Tile::update() {

    srcRect.x = srcRect.width * frame.x;
    srcRect.y = srcRect.height * frame.y;

    if(CheckCollisionRecs(Utils::getScreenRect(), object))
        draw(image);

    move();

    if(tileType == GROUND) {

        if(Utils::isSameXY(frame, NeighborTypes::groundMap[ROW_TOP]))
            DrawRectangleRec(object, Utils::testColor);
    }
}

void Tile::move() {

    object.x += velocity.x;
    object.y += velocity.y;

    velocity = {0.0f, 0.0f};
}