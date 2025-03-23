#include "TileManager.hpp"

TileManager::TileManager() {

    Tile::image = LoadTexture("../Assets/Tiles/Tile.png");
    mapGrassFrames();
}

TileManager::~TileManager() {

    UnloadTexture(Tile::image);
}

void TileManager::update() {

    for(auto &tile : tiles) {

        tile.update();
    }
}

void TileManager::checkNeighbors(Tile &thisTile) {

    Rectangle thisObject = thisTile.getObject();
    Rectangle checkerArea = {thisObject.x - 300, thisObject.y - 300, 400, 400};
    
    thisObject.width = 5;
    thisObject.height = 5;
    
    Rectangle neighborHoodRect = thisObject;
    
    const int maxOptions = 14;
    
    bool frameOptions[maxOptions];
    
    for(auto &frameOption : frameOptions) 
        frameOption = true;
    
    for(auto &tile : tiles) {
    
        Rectangle otherTileObject = tile.getObject();
        otherTileObject.width = 30;
        otherTileObject.height = 30;
    
        if(
            Utils::isSameRect(thisTile.getObject(), tile.getObject()) || 
            !CheckCollisionRecs(checkerArea, otherTileObject)
        ) continue;
    
        neighborHoodRect = thisObject;
        neighborHoodRect.x += 60;
    
        if(CheckCollisionRecs(otherTileObject, neighborHoodRect)) {
    
            frameOptions[CORNER_BOTTOM_RIGHT] = false;
            frameOptions[CORNER_TOP_RIGHT] = false;
            frameOptions[ROW_RIGHT] = false;
        }
    
        neighborHoodRect = thisObject;
        neighborHoodRect.x -= 60;
    
        if(CheckCollisionRecs(otherTileObject, neighborHoodRect)) {
    
            frameOptions[CORNER_BOTTOM_LEFT] = false;
            frameOptions[CORNER_TOP_LEFT] = false;
            frameOptions[ROW_LEFT] = false;
        }
    
        neighborHoodRect = thisObject;
        neighborHoodRect.y += 60;
    
        if(CheckCollisionRecs(otherTileObject, neighborHoodRect)) {
    
            frameOptions[ROW_BOTTOM] = false;
            frameOptions[CORNER_BOTTOM_RIGHT] = false;
            frameOptions[CORNER_BOTTOM_LEFT] = false;
        }
            
        neighborHoodRect = thisObject;
        neighborHoodRect.y -= 60;
    
        if(CheckCollisionRecs(otherTileObject, neighborHoodRect)) {
    
            frameOptions[CORNER_TOP_LEFT] = false;
            frameOptions[CORNER_TOP_RIGHT] = false;
            frameOptions[ROW_TOP] = false;
        }
    
        neighborHoodRect = thisObject;
        neighborHoodRect.x += 60;
        neighborHoodRect.y -= 60;
    
    
        if(CheckCollisionRecs(otherTileObject, neighborHoodRect)) {
    
            frameOptions[SIDE_CORNER_TOP_RIGHT] = false;
        }
    
        neighborHoodRect = thisObject;
        neighborHoodRect.x -= 60;
        neighborHoodRect.y -= 60;
    
    
        if(CheckCollisionRecs(otherTileObject, neighborHoodRect)) {
    
            frameOptions[SIDE_CORNER_TOP_LEFT] = false;
        }
    
        neighborHoodRect = thisObject;
        neighborHoodRect.x -= 60;
        neighborHoodRect.y += 60;
    
    
        if(CheckCollisionRecs(otherTileObject, neighborHoodRect)) {
    
            frameOptions[SIDE_CORNER_BOTTOM_LEFT] = false;
        }
    
        neighborHoodRect = thisObject;
        neighborHoodRect.x += 60;
        neighborHoodRect.y += 60;
    
        if(CheckCollisionRecs(otherTileObject, neighborHoodRect)) {
    
            frameOptions[SIDE_CORNER_BOTTOM_RIGHT] = false;
        }
    }
    
    for(int i = 0; i < maxOptions; i++) {
    
        if(frameOptions[i]) {
    
            thisTile.setFrame(grassMap[(GrassType) i]);
            return;
        }
    }
}

void TileManager::mapGrassFrames() {
    
    grassMap[CORNER_BOTTOM_RIGHT] = {4, 2};
    grassMap[CORNER_BOTTOM_LEFT] = {2, 2};
    grassMap[CORNER_TOP_RIGHT] = {4, 0};
    grassMap[CORNER_TOP_LEFT] = {2, 0};
    grassMap[ROW_TOP] = {3, 0};
    grassMap[ROW_BOTTOM] = {3, 2};
    grassMap[ROW_RIGHT] = {4, 1};
    grassMap[ROW_LEFT] = {2, 1};
    grassMap[SIDE_CORNER_TOP_RIGHT] = {0, 4};
    grassMap[SIDE_CORNER_TOP_LEFT] = {1, 4};
    grassMap[SIDE_CORNER_BOTTOM_RIGHT] = {0, 3};
    grassMap[SIDE_CORNER_BOTTOM_LEFT] = {1, 3};
    grassMap[MIDDLE] = {3, 1};
}
