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

    animate();

    for(auto &tile : tiles) {

        setFrameAnimationForSpecficTiles(tile);
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

                    thisTile.setFrame(groundMap[tileNeighborTile]);
                    return;

                case LIGHT_GRASS:

                    thisTile.setFrame(lightGrassMap[tileNeighborTile]);
                    return;

                case DARK_GRASS:

                    thisTile.setFrame(darkGrassMap[tileNeighborTile]);
                    return;

                case DIRT:

                    thisTile.setFrame(dirtMap[tileNeighborTile]);
                    return;

                case DECORATIONS:

                    int index = decoration;
                    decoration = (Decoration) ((index++ == 8) ? THREE_WEED : index);

                    thisTile.setFrame(decorationMap[decoration]);
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
    
    groundMap[CORNER_BOTTOM_RIGHT] = {1, cornersFrame};
    groundMap[CORNER_BOTTOM_LEFT] = {0, cornersFrame};
    
    float sideCornersFrame = (currentFrame == 1) ? 10 : 7;

    groundMap[ROW_BOTTOM] = {3, sideCornersFrame};
    groundMap[SIDE_CORNER_BOTTOM_RIGHT] = {2, sideCornersFrame};
    groundMap[SIDE_CORNER_BOTTOM_LEFT] = {4, sideCornersFrame};

    decorationMap[THE_ROCK] = {8, 7.0f + currentFrame};
    decorationMap[SEAWEED] = {8, 9.0f + currentFrame};
}

void TileManager::setFrameAnimationForSpecficTiles(Tile &tile) {

    if(Utils::isSameXY(tile.getFrame(), {8, 9}, {8, 10}))
        tile.setFrame(decorationMap[SEAWEED]);

    if(Utils::isSameXY(tile.getFrame(), {8, 7}, {8, 8}))
        tile.setFrame(decorationMap[THE_ROCK]);

    if(Utils::isSameXY(tile.getFrame(), {1, 8}, {1, 9}))
        tile.setFrame(groundMap[CORNER_BOTTOM_RIGHT]);

    if(Utils::isSameXY(tile.getFrame(), {0, 8}, {0, 9}))
        tile.setFrame(groundMap[CORNER_BOTTOM_LEFT]);

    if(Utils::isSameXY(tile.getFrame(), {3, 7}, {3, 10}))
        tile.setFrame(groundMap[ROW_BOTTOM]);

    if(Utils::isSameXY(tile.getFrame(), {2, 7}, {2, 10}))
        tile.setFrame(groundMap[SIDE_CORNER_BOTTOM_RIGHT]);

    if(Utils::isSameXY(tile.getFrame(), {4, 7}, {4, 10}))
        tile.setFrame(groundMap[SIDE_CORNER_BOTTOM_LEFT]);
}

void TileManager::mapTileFrames() {

    groundMap[CORNER_BOTTOM_RIGHT] = {1, 9};
    groundMap[CORNER_BOTTOM_LEFT] = {0, 9};
    groundMap[CORNER_TOP_RIGHT] = {1, 7};
    groundMap[CORNER_TOP_LEFT] = {0, 7};
    groundMap[ROW_TOP] = {3, 9};
    groundMap[ROW_RIGHT] = {2, 8};
    groundMap[ROW_LEFT] = {4, 8};
    groundMap[ROW_BOTTOM] = {3, 10};
    groundMap[SIDE_CORNER_BOTTOM_RIGHT] = {2, 10};
    groundMap[SIDE_CORNER_BOTTOM_LEFT] = {4, 10};
    groundMap[SIDE_CORNER_TOP_RIGHT] = {2, 9};
    groundMap[SIDE_CORNER_TOP_LEFT] = {4, 9};
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

    dirtMap[CORNER_BOTTOM_RIGHT] = {7, 16};
    dirtMap[CORNER_BOTTOM_LEFT] = {5, 16};
    dirtMap[CORNER_TOP_RIGHT] = {7, 14};
    dirtMap[CORNER_TOP_LEFT] = {5, 14};
    dirtMap[ROW_TOP] = {6, 14};
    dirtMap[ROW_BOTTOM] = {6, 16};
    dirtMap[ROW_RIGHT] = {7, 15};
    dirtMap[ROW_LEFT] = {5, 15};
    dirtMap[SIDE_CORNER_TOP_RIGHT] = {2, 18};
    dirtMap[SIDE_CORNER_TOP_LEFT] = {3, 18};
    dirtMap[SIDE_CORNER_BOTTOM_RIGHT] = {2, 17};
    dirtMap[SIDE_CORNER_BOTTOM_LEFT] = {3, 17};
    dirtMap[MIDDLE] = {6, 15};

    decorationMap[THREE_WEED] = {0, 0};
    decorationMap[FOUR_WEED] = {0, 1};
    decorationMap[GROWING_WEED] = {0, 2};
    decorationMap[YELLOW_FLOWER] = {1, 0};
    decorationMap[THREE_WHITE_FLOWER] = {1, 1};
    decorationMap[TWO_WHITE_FLOWER] = {1, 2};
    decorationMap[THE_ROCK] = {8, 7};
    decorationMap[SEAWEED] = {8, 9};
}