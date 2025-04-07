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

    float snappedX = ((int) GetMousePosition().x / 60) * 60;
    float snappedY = ((int) GetMousePosition().y / 60) * 60;

    Rectangle selectionObject = {snappedX + worldPos.x, snappedY + worldPos.y, 60, 60};
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

    // for(float y = -2000; y < 20000; y += 60) {
    //     for(float x = -2000; x < 20000; x += 60) {

    //         Rectangle object = {x + worldPos.x, y + worldPos.y, 60, 60};
    //         Rectangle checkerArea = {object.x - 50, object.y - 50, 155, 155};

    //         if(Mouse::isHovering(object)) 
    //             DrawRectangleRec(object, Utils::testColor);
    //         else continue;

    //         if(Mouse::isClickedR(object)) {

    //             for(auto it = tileManager.tiles.begin(); it < tileManager.tiles.end();) {

    //                 if(CheckCollisionRecs(it->getObject(), object)) {

    //                     tileManager.tiles.erase(it);
    //                     tileManager.updateFrameType(checkerArea);
    //                     return;
    //                 } else it++;
    //             }
    //         }

    //         if(!Mouse::isClickedL(object)) continue;

    //         for(auto &tile : tileManager.tiles) {

    //             if(Utils::isSameRect(tile.getObject(), object))
    //                 return;
    //         }

    //         tileManager.tiles.push_back(Tile(
    //             object,
    //             {2, 2}
    //         ));

    //         tileManager.updateFrameType(checkerArea);
    //     }       
    // }
