#include "World.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

void World::update(Vector2 playerVeclocity) {

    if(!tileManager.tiles.empty()) {

        worldPos.x += tileManager.tiles[0].getVeclocity().x;
        worldPos.y += tileManager.tiles[0].getVeclocity().y;
    }

    tileManager.update();
    placeTiles();
}

void World::placeTiles() {

    float mouseWorldX = GetMousePosition().x + worldPos.x;
    float mouseWorldY = GetMousePosition().y + worldPos.y;

    float snappedWorldX = floorf(mouseWorldX / TILE_SIZE) * TILE_SIZE;
    float snappedWorldY = floorf(mouseWorldY / TILE_SIZE) * TILE_SIZE;

    Rectangle selectionObject = {snappedWorldX - worldPos.x, snappedWorldY - worldPos.y, TILE_SIZE, TILE_SIZE};
    Rectangle checkerArea = {selectionObject.x - 50, selectionObject.y - 50, 155, 155};

    Rectangle worldTileRect = {
        snappedWorldX,
        snappedWorldY,
        TILE_SIZE,
        TILE_SIZE
    };

    DrawRectangleRec(selectionObject, Utils::testColor);

    if(Mouse::isClickedR(selectionObject)) {

        for(auto it = tileManager.tiles.begin(); it < tileManager.tiles.end();) {

            if(CheckCollisionRecs(it->getObject(), worldTileRect)) {

                tileManager.tiles.erase(it);
                tileManager.updateFrameType(checkerArea);
                return;
            } else it++;
        }
    }

    if(!Mouse::isClickedL(selectionObject)) return;

    for(auto &tile : tileManager.tiles) {

        if(Utils::isSameRect(tile.getObject(), worldTileRect))
            return;
    }

    tileManager.tiles.push_back(Tile(
        worldTileRect,
        {2, 2}
    ));

    tileManager.updateFrameType(checkerArea);
} 