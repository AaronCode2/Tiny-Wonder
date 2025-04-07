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

    float snappedX = ((int) GetMousePosition().x / TILE_SIZE) * TILE_SIZE;
    float snappedY = ((int) GetMousePosition().y / TILE_SIZE) * TILE_SIZE;

    Rectangle selectionObject = {snappedX, snappedY, TILE_SIZE, TILE_SIZE};
    Rectangle checkerArea = {selectionObject.x - 50, selectionObject.y - 50, 155, 155};

    DrawRectangleRec(selectionObject, Utils::testColor);

    if(Mouse::isClickedR(selectionObject)) {

        for(auto it = tileManager.tiles.begin(); it < tileManager.tiles.end();) {

            if(CheckCollisionRecs(it->getObject(), selectionObject)) {

                tileManager.tiles.erase(it);
                tileManager.updateFrameType(checkerArea);
                return;
            } else it++;
        }
    }

    if(!Mouse::isClickedL(selectionObject)) return;

    for(auto &tile : tileManager.tiles) {

        if(Utils::isSameRect(tile.getObject(), selectionObject))
            return;
    }

    tileManager.tiles.push_back(Tile(
        selectionObject,
        {2, 2}
    ));

    tileManager.updateFrameType(checkerArea);
} 