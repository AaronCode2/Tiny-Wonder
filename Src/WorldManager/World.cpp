#include "World.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

World::World() {

    Tile::image = LoadTexture("../Assets/Tiles/Tile.png");
    readData();
}

World::~World() {
    
    UnloadTexture(Tile::image);
}

void World::update() {
    
    for(auto &tile : tiles) {
        

        frameLogicNeighbor(tile);
        tile.update();
    }

    for(float y = 0; y < GetScreenHeight(); y += 60) {
        for(float x = 0; x < GetScreenWidth(); x += 60) {
                
            Rectangle object = {x, y, 60, 60};
    
            if(Mouse::isHovering(object)) {
    
                DrawRectangleRec(object, Utils::testColor);
            } 

            if(Mouse::isClickedL(object)) {
                    
                bool skip = false;

                for(auto &tile : tiles) {

                    if(tile.getObject().x == object.x && tile.getObject().y == object.y) {

                        skip = true;
                        break;
                    }
                }

                if(skip) break;

                tiles.push_back(Tile(
                    object,
                    {2, 2}
                ));
            }

            if(Mouse::isClickedR(object)) {

                for(auto it = tiles.begin(); it < tiles.end();) {
                        
                    if(it->getObject().x == object.x && it->getObject().y == object.y) {

                        it = tiles.erase(it);
                        break;
                    }

                    it++;
                }
            }
        }
    }

}


void World::readData() {

    std::ifstream file(FILE_NAME);

    if(!file.is_open()) {

        std::cerr << "\033[31mError: Could not read Data in TileMap.txt\n\033[0m";
        exit(EXIT_FAILURE);
    }

    std::string line;

    while(std::getline(file, line)) {

        int numbers[NUM_SIZE]; 
        int count = 0;        
        bool insideBraces = false;
        std::string temp;

        for(size_t i = 0; i < line.length(); i++) {

            if(line[i] == '{')
                continue;

            if(line[i] == '}')
                break;

            temp += line[i];  
        
        }

        std::stringstream ss(temp);
        std::string token;

        while (std::getline(ss, token, ',') && count < NUM_SIZE - 1) {

            try{

                int num = std::stoi(token);
                numbers[count++] = num;

            } catch (...) {}
        }

        tiles.push_back(Tile(
            {
                (float) numbers[X],
                (float) numbers[Y],
                (float) numbers[WIDTH],
                (float) numbers[HEIGHT]
            },
            {(float) numbers[FRAME_X], (float) numbers[FRAME_Y]}
        ));
    }

    file.close();
}

void World::frameLogicNeighbor(Tile &thisTile) {

    Rectangle neighborhoodRight = thisTile.getObject();
    neighborhoodRight.x += 30;

    Rectangle neighborhoodLeft = thisTile.getObject();
    neighborhoodLeft.x -= 30;

    Rectangle neighborhoodUp = thisTile.getObject();
    neighborhoodUp.y -= 30;

    Rectangle neighborhoodDown = thisTile.getObject();
    neighborhoodDown.y += 30;

    bool cornerBottomLeftTiles = true;
    bool cornerBottomRightTiles = true;

    bool cornerTopLeftTiles = true;
    bool cornerTopRightTiles = true;

    bool bottomRowTiles = true;
    bool topRowTiles = true;

    bool sideLeftRowTiles = true;
    bool sideRightRowTiles = true;

    bool sideCornerBottomLeft = true;

    for(auto &otherTile : tiles) {

        if(Utils::isSameRect(thisTile.getObject(), otherTile.getObject())) 
            continue;

        if(CheckCollisionRecs(otherTile.getObject(), neighborhoodRight)) {

            cornerBottomRightTiles = false;
            cornerTopRightTiles = false;
            sideRightRowTiles = false;
            break;
        }
    }

    for(auto &other0Tile : tiles) {

        if(Utils::isSameRect(thisTile.getObject(), other0Tile.getObject())) 
            continue;

        if(CheckCollisionRecs(other0Tile.getObject(), neighborhoodLeft)) {

            cornerBottomLeftTiles = false;
            cornerTopLeftTiles = false;
            sideLeftRowTiles = false;
            break;
        }
    }

    for(auto &other2Tile : tiles) {

        if(Utils::isSameRect(thisTile.getObject(), other2Tile.getObject())) 
            continue;

        if(CheckCollisionRecs(other2Tile.getObject(), neighborhoodDown)) {

            bottomRowTiles = false;
            cornerBottomRightTiles = false;
            cornerBottomLeftTiles = false;
            break;
        }
    }

    for(auto &other3Tile : tiles) {

        if(Utils::isSameRect(thisTile.getObject(), other3Tile.getObject())) 
            continue;

        if(CheckCollisionRecs(other3Tile.getObject(), neighborhoodUp)) {

            cornerTopLeftTiles = false;
            cornerTopRightTiles = false;
            topRowTiles = false;
            break;
        }
    }
            
    if(cornerBottomLeftTiles) thisTile.setFrame({2, 2});
    else if(cornerBottomRightTiles) thisTile.setFrame({4, 2});

    else if(cornerTopLeftTiles) thisTile.setFrame({2, 0});
    else if(cornerTopRightTiles) thisTile.setFrame({4, 0});

    else if(topRowTiles) thisTile.setFrame({3, 0});
    else if(bottomRowTiles) thisTile.setFrame({3, 2});

    else if(sideLeftRowTiles) thisTile.setFrame({2, 1});
    else if(sideRightRowTiles) thisTile.setFrame({4, 1});

    else thisTile.setFrame({3, 1});
}

void World::writeData() {

    std::ofstream file(FILE_NAME);

    if(!file.is_open()) {

        std::cerr << "\033[31mError: Could not write Data in TileMap.txt\n\033[0m";
        exit(EXIT_FAILURE);
    }

    for(auto tile : tiles) {  

       file << "{"

                << tile.getObject().x << ", " << tile.getObject().y << ", "
                << tile.getObject().width << ", " << tile.getObject().height << ", "
                << tile.getFrame().x << ", " << tile.getFrame().y << ", "
                << tile.getType()   

            << "}\n";  
    }

    file.close();
}
