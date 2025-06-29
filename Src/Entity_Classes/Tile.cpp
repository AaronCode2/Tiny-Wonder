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
    getHitBoxData();
}

void Tile::updateHitBox() {

    if(!isSolid) return;

    for(int i = 0; i < 2; i++) {

        Rectangle &hitBox = hitBoxes[i];
        Rectangle &hitBoxAjust = hitBoxAjusters[i];

        hitBox.x = object.x + hitBoxAjust.x;
        hitBox.y = object.y + hitBoxAjust.y;
        hitBox.width = hitBoxAjust.width;
        hitBox.height = hitBoxAjust.height;
    }
}

void Tile::getHitBoxData(){

    if(IsKeyDown(KEY_T)) 
        __ta = !__ta;

    if(__ta) {

        isSolid = false;
        return;
    }

    if(tileType != GROUND) return;

    isSolid = true;
    hitBoxes[0] = EMPTY_RECT;
    hitBoxes[1] = EMPTY_RECT;
    hitBoxAjusters[0] = EMPTY_RECT; 
    hitBoxAjusters[1] = EMPTY_RECT;

    if(Utils::isSameXY(frame, NeighborTypes::groundMap[ROW_TOP]))
        hitBoxAjusters[0] = {0, -2, 60, 10};
    else if(Utils::isSameXY(frame, NeighborTypes::groundMap[ROW_BOTTOM]))
        hitBoxAjusters[0] = {0, 20, 60, 10};
    else if(Utils::isSameXY(frame, NeighborTypes::groundMap[ROW_LEFT]))
        hitBoxAjusters[0] = {-2, 0, 10, 60};
    else if(Utils::isSameXY(frame, NeighborTypes::groundMap[ROW_RIGHT]))
        hitBoxAjusters[0] = {52, 0, 10, 60};

    else if(Utils::isSameXY(frame, NeighborTypes::groundMap[CORNER_TOP_LEFT])) {

        hitBoxAjusters[0] = {0, -2, 60, 10};
        hitBoxAjusters[1] = {-2, 0, 10, 60};
    } else if(Utils::isSameXY(frame, NeighborTypes::groundMap[CORNER_TOP_RIGHT])) {

        hitBoxAjusters[0] = {0, -2, 60, 10};
        hitBoxAjusters[1] = {52, 0, 10, 60};
    } else if(Utils::isSameXY(frame, NeighborTypes::groundMap[CORNER_BOTTOM_LEFT])) {

        hitBoxAjusters[0] = {0, 20, 60, 10};
        hitBoxAjusters[1] = {-2, 0, 10, 60};
    } else if(Utils::isSameXY(frame, NeighborTypes::groundMap[CORNER_BOTTOM_RIGHT])) {

        hitBoxAjusters[0] = {0, 20, 60, 10};
        hitBoxAjusters[1] = {52, 0, 10, 60};
    }

    else if(Utils::isSameXY(frame, NeighborTypes::groundMap[SIDE_CORNER_BOTTOM_LEFT]))
        hitBoxAjusters[0] = {-2, 30, 10, 60};
    else if(Utils::isSameXY(frame, NeighborTypes::groundMap[SIDE_CORNER_BOTTOM_RIGHT]))
        hitBoxAjusters[0] = {52, 30, 10, 60};
    else isSolid = false;

    updateHitBox();

    DrawRectangleRec(hitBoxes[0], Utils::testColor);
    DrawRectangleRec(hitBoxes[1], Utils::testColor);
}

void Tile::move() {

    object.x += velocity.x;
    object.y += velocity.y;

    updateHitBox();

    velocity = {0.0f, 0.0f};
}