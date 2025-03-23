#include "World.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

void World::update(Vector2 playerVeclocity) {

    tileManager.update();
    placeTiles();
}

void World::placeTiles() {
    
    for(float y = 0; y < GetScreenHeight(); y += 60) {
        for(float x = 0; x < GetScreenWidth(); x += 60) {
                
            Rectangle object = {x, y, 60, 60};
            Rectangle checkerArea = {object.x - 50, object.y - 50, 150, 150};

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
