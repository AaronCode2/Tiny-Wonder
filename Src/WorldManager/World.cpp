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

    Rectangle thisObject = thisTile.getObject();

    Rectangle neighborHoodRect = thisObject;

    bool cornerBottomLeft = true, cornerBottomRight = true;
    bool cornerTopLeft = true, cornerTopRight = true;
    bool bottomRow = true, topRow = true;
    bool leftRow = true, rightRow = true;
    
    bool sideCornerTopRight = true, sideCornerTopLeft = true;
    bool sideCornerBottomRight = true, sideCornerBottomLeft = true;

    for(auto &tile : tiles) {

        if(Utils::isSameRect(thisTile.getObject(), tile.getObject())) 
            continue;

        neighborHoodRect = thisObject;
        neighborHoodRect.x += 30;

        if(CheckCollisionRecs(tile.getObject(), neighborHoodRect)) {

            cornerBottomRight = false;
            cornerTopRight = false;
            rightRow = false;
        }

        neighborHoodRect = thisObject;
        neighborHoodRect.x -= 30;

        if(CheckCollisionRecs(tile.getObject(), neighborHoodRect)) {

            cornerBottomLeft = false;
            cornerTopLeft = false;
            leftRow = false;
        }

        neighborHoodRect = thisObject;
        neighborHoodRect.y += 30;

        if(CheckCollisionRecs(tile.getObject(), neighborHoodRect)) {

            bottomRow = false;
            cornerBottomRight = false;
            cornerBottomLeft = false;
        }
        
        neighborHoodRect = thisObject;
        neighborHoodRect.y -= 30;

        if(CheckCollisionRecs(tile.getObject(), neighborHoodRect)) {

            cornerTopLeft = false;
            cornerTopRight = false;
            topRow = false;
        }

        neighborHoodRect = thisObject;
        neighborHoodRect.x += 60;
        neighborHoodRect.y -= 30;
        neighborHoodRect.width = 10;
        neighborHoodRect.height = 10;

        if(CheckCollisionRecs(tile.getObject(), neighborHoodRect)) {

            sideCornerTopRight = false;
        }

        neighborHoodRect = thisObject;
        neighborHoodRect.x -= 60;
        neighborHoodRect.y -= 30;
        neighborHoodRect.width = 10;
        neighborHoodRect.height = 10;

        if(CheckCollisionRecs(tile.getObject(), neighborHoodRect)) {

            sideCornerTopLeft = false;
        }

        neighborHoodRect = thisObject;
        neighborHoodRect.x -= 60;
        neighborHoodRect.y += 60;
        neighborHoodRect.width = 10;
        neighborHoodRect.height = 10;

        if(CheckCollisionRecs(tile.getObject(), neighborHoodRect)) {

            sideCornerBottomLeft = false;
        }

        neighborHoodRect = thisObject;
        neighborHoodRect.x += 60;
        neighborHoodRect.y += 60;
        neighborHoodRect.width = 10;
        neighborHoodRect.height = 10;

        if(CheckCollisionRecs(tile.getObject(), neighborHoodRect)) {

            sideCornerBottomRight = false;
        }
    }
    
    const TileFrameOption options[] = {

        {cornerBottomLeft,      CORNER_BOTTOM_LEFT},
        {cornerBottomRight,     CORNER_BOTTOM_RIGHT},
        {cornerTopLeft,         CORNER_TOP_LEFT},
        {cornerTopRight,        CORNER_TOP_RIGHT},
        {bottomRow,             ROW_BOTTOM},
        {topRow,                ROW_TOP},
        {leftRow,               ROW_LEFT},
        {rightRow,              ROW_RIGHT},
        {sideCornerTopRight,    SIDE_CORNER_TOP_RIGHT},
        {sideCornerTopLeft,     SIDE_CORNER_TOP_LEFT},
        {sideCornerBottomRight, SIDE_CORNER_BOTTOM_RIGHT},
        {sideCornerBottomLeft,  SIDE_CORNER_BOTTOM_LEFT}
    };

    for(const auto option : options) {

        if(option.condition) {

            thisTile.setFrame(tileFrameMap[option.frameType]);
            return;
        }
    }

    thisTile.setFrame(tileFrameMap[MIDDLE]);
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
