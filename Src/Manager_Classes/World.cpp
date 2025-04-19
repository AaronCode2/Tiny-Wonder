#include "World.hpp"
#include "../Game.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

void World::update(Vector2 playerVeclocity) {
    
    if(!tileManager.tiles.empty()) {
        
        worldPos.x += tileManager.tiles[0].getVeclocity().x;
        worldPos.y += tileManager.tiles[0].getVeclocity().y;
    }

    if(IsKeyPressed(KEY_E))
        tileManager.selectedType = (tileManager.selectedType == GRASS) ? GROUND : GRASS;

    tileManager.update();

    if(gameMode == GameMode::BUILD) 
        placeTiles();
}

void World::placeTiles() {
    
    for(float y = -20000; y < 20000; y += TILE_SIZE) {
        for(float x = -20000; x < 20000; x += TILE_SIZE) {
            
            Rectangle selectionObject = {x + worldPos.x, y + worldPos.y, TILE_SIZE, TILE_SIZE};
            
            if(!Mouse::isHovering(selectionObject))
                continue;
            
            Rectangle checkerArea = {selectionObject.x - 50, selectionObject.y - 50, 155, 155};
            Rectangle deleteArea = {selectionObject.x + 10, selectionObject.y + 10, 30, 30};

            DrawRectangleRec(selectionObject, Utils::testColor);
            
            if(Mouse::isClickedR(selectionObject)) {

                for(auto it = tileManager.tiles.begin(); it < tileManager.tiles.end();) {

                    if(CheckCollisionRecs(it->getObject(), deleteArea)) {

                        tileManager.tiles.erase(it);
                        tileManager.updateFrameType(checkerArea);
                        return;
                    } it++;
                }
            }

            if(!Mouse::isClickedL(selectionObject)) return;

            for(auto &tile : tileManager.tiles) {

                if(Utils::isSameRect(tile.getObject(), selectionObject) && tile.getType() == tileManager.selectedType)
                    return;
            }

            tileManager.tiles.push_back(Tile(
                selectionObject,
                {2, 2},
                tileManager.selectedType
            ));

            tileManager.updateFrameType(checkerArea);
        }
    }
} 