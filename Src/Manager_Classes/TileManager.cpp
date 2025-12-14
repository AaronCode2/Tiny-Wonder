#include "TileManager.hpp"

TileManager::TileManager() {

    Tile::image = LoadTexture("../Assets/Tiles/Tile.png");
    Plant::plantImage = LoadTexture("../Assets/Items/plants.png");
    Plant::mapPlants();
    
    NeighborTypes::defineTypes();

    updateFrameType(Utils::getScreenRect());
}

TileManager::~TileManager() {

    UnloadTexture(Tile::image);
    UnloadTexture(Plant::plantImage);
}

void TileManager::update() {

    animate();

    for(auto &tile : tiles) {

        setFrameAnimationForSpecficTiles(tile);
        tile.update();
    }

    for(auto &plant : plants) {

        plant.update();
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

    if(thisTile.decorationType != NOT_SET)
        return;

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
            Utils::isSameXY(thisTile.getObject(), tile.getObject()) || 
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

                    thisTile.setFrame(NeighborTypes::groundMap[tileNeighborTile]);
                    return;

                case LIGHT_GRASS:

                    thisTile.setFrame(NeighborTypes::lightGrassMap[tileNeighborTile]);
                    return;

                case DARK_GRASS:

                    thisTile.setFrame(NeighborTypes::darkGrassMap[tileNeighborTile]);
                    return;

                case DIRT:

                    thisTile.setFrame(NeighborTypes::dirtMap[tileNeighborTile]);
                    return;

                case DECORATIONS:

                    int index = decoration;
                    decoration = (Decoration) ((index++ == 8) ? THREE_WEED : index);

                    thisTile.setFrame(NeighborTypes::decorationMap[decoration]);
                    thisTile.decorationType = decoration;
                    return;
            }
        }
    }
}

void TileManager::animate() {

    elapsedFrame += GetFrameTime();

    if(elapsedFrame >= 1.0f) {
        
        elapsedFrame = 0.0f;

        if(currentFrame < 1)currentFrame++;
        else currentFrame = 0;
    }
    
    float cornersFrame = (currentFrame == 1) ? 9 : 8;
    
    NeighborTypes::groundMap[CORNER_BOTTOM_RIGHT] = {1, cornersFrame};
    NeighborTypes::groundMap[CORNER_BOTTOM_LEFT] = {0, cornersFrame};
    
    float sideCornersFrame = (currentFrame == 1) ? 10 : 7;

    NeighborTypes::groundMap[ROW_BOTTOM] = {3, sideCornersFrame};
    NeighborTypes::groundMap[SIDE_CORNER_BOTTOM_RIGHT] = {2, sideCornersFrame};
    NeighborTypes::groundMap[SIDE_CORNER_BOTTOM_LEFT] = {4, sideCornersFrame};

    NeighborTypes::decorationMap[THE_ROCK] = {8, 7.0f + currentFrame};
    NeighborTypes::decorationMap[SEAWEED] = {8, 9.0f + currentFrame};
}

void TileManager::setFrameAnimationForSpecficTiles(Tile &tile) {

    if(Utils::isSameXY(tile.getFrame(), {8, 9}, {8, 10}))
        tile.setFrame(NeighborTypes::decorationMap[SEAWEED]);

    if(Utils::isSameXY(tile.getFrame(), {8, 7}, {8, 8}))
        tile.setFrame(NeighborTypes::decorationMap[THE_ROCK]);

    if(Utils::isSameXY(tile.getFrame(), {1, 8}, {1, 9}))
        tile.setFrame(NeighborTypes::groundMap[CORNER_BOTTOM_RIGHT]);

    if(Utils::isSameXY(tile.getFrame(), {0, 8}, {0, 9}))
        tile.setFrame(NeighborTypes::groundMap[CORNER_BOTTOM_LEFT]);

    if(Utils::isSameXY(tile.getFrame(), {3, 7}, {3, 10}))
        tile.setFrame(NeighborTypes::groundMap[ROW_BOTTOM]);

    if(Utils::isSameXY(tile.getFrame(), {2, 7}, {2, 10}))
        tile.setFrame(NeighborTypes::groundMap[SIDE_CORNER_BOTTOM_RIGHT]);

    if(Utils::isSameXY(tile.getFrame(), {4, 7}, {4, 10}))
        tile.setFrame(NeighborTypes::groundMap[SIDE_CORNER_BOTTOM_LEFT]);
}

void TileManager::mapTileFrames() {

}