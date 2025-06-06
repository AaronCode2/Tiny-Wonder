#include "World.hpp"

World::World() {

    selectorImage = LoadTexture("../Assets/UI/Selector.png");
}

World::~World() {

    UnloadTexture(selectorImage);
}

void World::update() {

    if(!tileManager.tiles.empty()) {
        
        worldPos.x += tileManager.tiles[0].getVeclocity().x;
        worldPos.y += tileManager.tiles[0].getVeclocity().y;
    }

    if(IsKeyPressed(KEY_E)) {

        int newSelectType = tileManager.selectedType;
        tileManager.selectedType = (tileManager.selectedType != DIRT) ? (TileType) ++newSelectType : 
            (TileType) 0;
    }

    tileManager.update();

    if(Settings::gameMode == GameMode::BUILD && !Settings::HoveringOverMenu) {

        checkMouseActions();
    }
}

void World::checkMouseActions() {
    
    for(float y = -4000; y < 4000; y += TILE_SIZE) {
        for(float x = -4000; x < 4000; x += TILE_SIZE) {
            
            selectionObject = {x + worldPos.x, y + worldPos.y, TILE_SIZE, TILE_SIZE};
            
            if(!Mouse::isHovering(selectionObject))
                continue;

            DrawTexturePro(
                selectorImage,
                {0, 0, (float) selectorImage.width, (float) selectorImage.height},
                selectionObject, {0, 0}, 0, WHITE
            );
            
            checkerArea = {selectionObject.x - 50, selectionObject.y - 50, 155, 155};
            deleteArea = {selectionObject.x + 10, selectionObject.y + 10, 30, 30};
            
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

                if(Utils::isSameXY(tile.getObject(), selectionObject) && tile.getType() == tileManager.selectedType)
                    return;
            }

            tileManager.tiles.push_back(Tile(
                selectionObject,
                UNKNOWN_TILE,
                tileManager.selectedType
            ));

            tileManager.updateFrameType(checkerArea);
        }
    }
}