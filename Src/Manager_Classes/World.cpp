#include "World.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

void World::update() {

    tileManager.update();
    placeTiles();
}

void World::placeTiles() {

    for(float y = 0; y < GetScreenHeight(); y += 60) {
        for(float x = 0; x < GetScreenWidth(); x += 60) {
                
            Rectangle object = {x, y, 60, 60};
    
            if(Mouse::isHovering(object)) {
    
                DrawRectangleRec(object, Utils::testColor);
            } else continue;

            if(!Mouse::isClickedL(object)) continue;
                    
            bool skip = false;

            for(auto &tile : tileManager.tiles) {

                if(tile.getObject().x == object.x && tile.getObject().y == object.y) {

                    skip = true;
                    break;
                }
            }

            if(skip) break;

            tileManager.tiles.push_back(Tile(
                object,
                {2, 2}
            ));
        }       
    }
}
