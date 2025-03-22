#include "World.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>


World::World() {

    Tile::image = LoadTexture("../Assets/Tiles/Tile.png");

    tileFrameMap[CORNER_BOTTOM_RIGHT] = {4, 2};
    tileFrameMap[CORNER_BOTTOM_LEFT] = {2, 2};
    tileFrameMap[CORNER_TOP_RIGHT] = {4, 0};
    tileFrameMap[CORNER_TOP_LEFT] = {2, 0};
    tileFrameMap[ROW_TOP] = {3, 0};
    tileFrameMap[ROW_BOTTOM] = {3, 2};
    tileFrameMap[ROW_RIGHT] = {4, 1};
    tileFrameMap[ROW_LEFT] = {2, 1};
    tileFrameMap[SIDE_CORNER_TOP_RIGHT] = {0, 4};
    tileFrameMap[SIDE_CORNER_TOP_LEFT] = {1, 4};
    tileFrameMap[SIDE_CORNER_BOTTOM_RIGHT] = {0, 3};
    tileFrameMap[SIDE_CORNER_BOTTOM_LEFT] = {1, 3};
    tileFrameMap[MIDDLE] = {3, 1};

    readData();

    for(auto &tile : tileManager.tiles) {

        frameLogicNeighbor(tile);
    }
}

World::~World() {

    UnloadTexture(Tile::image);
}

void World::update(Vector2 playerVelocity) {

    for(auto &tile : tileManager.tiles) {

        tile.update();
        tile.setVelocity({0.0f, 0.0f});
    }


    for(float y = 0; y < GetScreenHeight(); y += 60) {
        for(float x = 0; x < GetScreenWidth(); x += 60) {
                
            Rectangle object = {x, y, 60, 60};
    
            if(Mouse::isHovering(object)) {
    
                DrawRectangleRec(object, Utils::testColor);
            } 

            if(Mouse::isClickedL(object)) {
                    
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
      
                for(auto &tile : tileManager.tiles) {

                    if(!CheckCollisionRecs(Utils::getScreenRect(), tile.getObject()))
                        continue;

                    frameLogicNeighbor(tile);
                }
            }

            if(Mouse::isClickedR(object)) {

                for(auto it = tileManager.tiles.begin(); it < tileManager.tiles.end();) {

                    if(CheckCollisionRecs(Utils::getScreenRect(), it->getObject()) && CheckCollisionRecs(object, it->getObject())) {

                        it = tileManager.tiles.erase(it);
                        continue;
                    }
                    
                    frameLogicNeighbor(*it);
                    it++;
                }
            }
        }
    }

}


void World::readData() {


}

void World::frameLogicNeighbor(Tile &thisTile) {

    Rectangle thisObject = thisTile.getObject();
    Rectangle checkerArea = {thisObject.x - 300, thisObject.y - 300, 400, 400};

    thisObject.width = 5;
    thisObject.height = 5;

    Rectangle neighborHoodRect = thisObject;

    const int maxOptions = 14;

    bool frameOptions[maxOptions];

    for(auto &frameOption : frameOptions) 
        frameOption = true;

    for(auto &tile : tileManager.tiles) {

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

        // Diagonal checks
        neighborHoodRect = thisObject;
        neighborHoodRect.x += 60;
        neighborHoodRect.y -= 60;


        if (CheckCollisionRecs(otherTileObject, neighborHoodRect)) {

            frameOptions[SIDE_CORNER_TOP_RIGHT] = false;
        }

        neighborHoodRect = thisObject;
        neighborHoodRect.x -= 60;
        neighborHoodRect.y -= 60;


        if (CheckCollisionRecs(otherTileObject, neighborHoodRect)) {

            frameOptions[SIDE_CORNER_TOP_LEFT] = false;
        }

        neighborHoodRect = thisObject;
        neighborHoodRect.x -= 60;
        neighborHoodRect.y += 60;


        if (CheckCollisionRecs(otherTileObject, neighborHoodRect)) {

            frameOptions[SIDE_CORNER_BOTTOM_LEFT] = false;
        }

        neighborHoodRect = thisObject;
        neighborHoodRect.x += 60;
        neighborHoodRect.y += 60;

        if (CheckCollisionRecs(otherTileObject, neighborHoodRect)) {

            frameOptions[SIDE_CORNER_BOTTOM_RIGHT] = false;
        }
    }

    for(int i = 0; i < maxOptions; i++) {

        if(frameOptions[i]) {

            thisTile.setFrame(tileFrameMap[(TileFrameType) i]);
            return;
        }
    }
}

void World::writeData() {

}
