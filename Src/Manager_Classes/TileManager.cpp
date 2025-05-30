#include "TileManager.hpp"

TileManager::TileManager() {

    Tile::image = LoadTexture("../Assets/Tiles/Tile.png");
    mapTileFrames();
    updateFrameType(Utils::getScreenRect());
}

TileManager::~TileManager() {

    UnloadTexture(Tile::image);
}

void TileManager::update() {

    for(auto &tile : tiles) {

        tile.update();
    }
}

void TileManager::updateFrameType(Rectangle contactedArea) {

    for(auto &tile : tiles) {

        if(!CheckCollisionRecs(contactedArea, tile.getObject())) 
            continue;

        checkNeighbors(tile);
    }
}

void TileManager::checkNeighbors(Tile &thisTile) {

    Rectangle thisObject = thisTile.getObject();
    Rectangle checkerArea = {thisObject.x - 50, thisObject.y - 50, 150, 150};
    
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
            !CheckCollisionRecs(checkerArea, otherTileObject) || 
            thisTile.getType() != tile.getType()
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
    
    
        if(CheckCollisionRecs(otherTileObject, neighborHoodRect))
            frameOptions[SIDE_CORNER_TOP_RIGHT] = false;
    
        neighborHoodRect = thisObject;
        neighborHoodRect.x -= 60;
        neighborHoodRect.y -= 60;
    
        if(CheckCollisionRecs(otherTileObject, neighborHoodRect))
            frameOptions[SIDE_CORNER_TOP_LEFT] = false;
    
        neighborHoodRect = thisObject;
        neighborHoodRect.x -= 60;
        neighborHoodRect.y += 60;
    
        if(CheckCollisionRecs(otherTileObject, neighborHoodRect))
            frameOptions[SIDE_CORNER_BOTTOM_LEFT] = false;
    
        neighborHoodRect = thisObject;
        neighborHoodRect.x += 60;
        neighborHoodRect.y += 60;
    
        if(CheckCollisionRecs(otherTileObject, neighborHoodRect))
            frameOptions[SIDE_CORNER_BOTTOM_RIGHT] = false;
        
    }
    
    for(int i = 0; i < maxOptions; i++) {
    
        if(frameOptions[i]) {
            
            TileNeighborType tileNeighborTile = (TileNeighborType) i;

            switch(thisTile.getType()) {

                case GROUND:

                    thisTile.setFrame(groundMap[tileNeighborTile]);
                    return;

                case LIGHT_GRASS:

                    thisTile.setFrame(lightGrassMap[tileNeighborTile]);
                    return;

                case DARK_GRASS:

                    thisTile.setFrame(darkGrassMap[tileNeighborTile]);
                    return;

                case DIRT:

                    // TODO: Implement the Dirt code
                    return;
            }
        }
    }
}

void TileManager::mapTileFrames() {
    
    groundMap[CORNER_BOTTOM_RIGHT] = {1, 8};
    groundMap[CORNER_BOTTOM_LEFT] = {0, 8};
    groundMap[CORNER_TOP_RIGHT] = {1, 7};
    groundMap[CORNER_TOP_LEFT] = {0, 7};
    groundMap[ROW_TOP] = {3, 9};
    groundMap[ROW_BOTTOM] = {3, 7};
    groundMap[ROW_RIGHT] = {2, 8};
    groundMap[ROW_LEFT] = {4, 8};
    groundMap[SIDE_CORNER_TOP_RIGHT] = {2, 9};
    groundMap[SIDE_CORNER_TOP_LEFT] = {4, 9};
    groundMap[SIDE_CORNER_BOTTOM_RIGHT] = {2, 7};
    groundMap[SIDE_CORNER_BOTTOM_LEFT] = {4, 7};
    groundMap[MIDDLE] = {3, 1};

    lightGrassMap[CORNER_BOTTOM_RIGHT] = {7, 6};
    lightGrassMap[CORNER_BOTTOM_LEFT] = {5, 6};
    lightGrassMap[CORNER_TOP_RIGHT] = {7, 4};
    lightGrassMap[CORNER_TOP_LEFT] = {5, 4};
    lightGrassMap[ROW_TOP] = {6, 4};
    lightGrassMap[ROW_BOTTOM] = {6, 6};
    lightGrassMap[ROW_RIGHT] = {7, 5};
    lightGrassMap[ROW_LEFT] = {5, 5};
    lightGrassMap[SIDE_CORNER_TOP_RIGHT] = {3, 3};
    lightGrassMap[SIDE_CORNER_TOP_LEFT] = {2, 3};
    lightGrassMap[SIDE_CORNER_BOTTOM_RIGHT] = {3, 4};
    lightGrassMap[SIDE_CORNER_BOTTOM_LEFT] = {2, 4};
    lightGrassMap[MIDDLE] = {6, 5};

    darkGrassMap[CORNER_BOTTOM_RIGHT] = {7, 3};
    darkGrassMap[CORNER_BOTTOM_LEFT] = {5, 3};
    darkGrassMap[CORNER_TOP_RIGHT] = {7, 1};
    darkGrassMap[CORNER_TOP_LEFT] = {5, 1};
    darkGrassMap[ROW_TOP] = {6, 1};
    darkGrassMap[ROW_BOTTOM] = {6, 3};
    darkGrassMap[ROW_RIGHT] = {7, 2};
    darkGrassMap[ROW_LEFT] = {5, 2};
    darkGrassMap[SIDE_CORNER_TOP_RIGHT] = {3, 5};
    darkGrassMap[SIDE_CORNER_TOP_LEFT] = {2, 5};
    darkGrassMap[SIDE_CORNER_BOTTOM_RIGHT] = {3, 6};
    darkGrassMap[SIDE_CORNER_BOTTOM_LEFT] = {2, 6};
    darkGrassMap[MIDDLE] = {6, 2};
}