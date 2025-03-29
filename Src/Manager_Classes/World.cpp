#include "World.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

void World::update(Vector2 playerVeclocity) {

    if(!tileManager.tiles.empty()) {

        offsetCheckObject.x += tileManager.tiles[0].getVeclocity().x;
        offsetCheckObject.y += tileManager.tiles[0].getVeclocity().y;
    }

    tileManager.update();
    placeTiles();
}

void World::placeTiles() {

    // DrawRectangleRec(offsetCheckObject, Utils::testColor); 

    for(float y = -2000; y < 20000; y += 60) {
        for(float x = -2000; x < 20000; x += 60) {

            Rectangle object = {x + offsetCheckObject.x, y + offsetCheckObject.y, 60, 60};
            Rectangle checkerArea = {object.x - 50, object.y - 50, 155, 155};

            if(Mouse::isHovering(object)) 
                DrawRectangleRec(object, Utils::testColor);
            else continue;

            if(Mouse::isClickedR(object)) {

                for(auto it = tileManager.tiles.begin(); it < tileManager.tiles.end();) {

                    if(CheckCollisionRecs(it->getObject(), object)) {

                        tileManager.tiles.erase(it);
                        tileManager.updateFrameType(checkerArea);
                        return;
                    } else it++;
                }
            }

            if(!Mouse::isClickedL(object)) continue;

            for(auto &tile : tileManager.tiles) {

                if(Utils::isSameRect(tile.getObject(), object))
                    return;
            }

            tileManager.tiles.push_back(Tile(
                object,
                {2, 2}
            ));

            tileManager.updateFrameType(checkerArea);
        }       
    }
}
