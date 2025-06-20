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

    hitBoxesAjusters[0] = {

        10,
        60,
        40,
        40
    };

    if(tileType == GROUND) {

        if(Utils::isSameXY(frame, NeighborTypes::groundMap[ROW_TOP])) {

            DrawRectangleRec(hitBoxes[0], Utils::testColor);
        }
    }
}

void Tile::updateHitBox() {

    for(auto &hitBox : hitBoxes) {
        for(const auto hitBoxAjust : hitBoxesAjusters) {

            hitBox.x = object.x + hitBoxAjust.x;
            hitBox.y = object.y + hitBoxAjust.y;
        }
    }
}

void Tile::move() {

    object.x += velocity.x;
    object.y += velocity.y;

    updateHitBox();

    velocity = {0.0f, 0.0f};
}