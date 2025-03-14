#pragma once
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <raylib.h>
#include "../Utils.hpp"
#include "Tile.hpp"

#define NUM_SIZE 7
#define FILE_NAME "../Data/TileMap.txt"

enum fileReadStructure {

    X = 0,
    Y,
    WIDTH,
    HEIGHT,
    FRAME_X,
    FRAME_Y,
    ID
};

enum TileFrameType {

    CORNER_BOTTOM_LEFT = 0,
    CORNER_BOTTOM_RIGHT,
    CORNER_TOP_LEFT,
    CORNER_TOP_RIGHT,
    ROW_TOP,
    ROW_BOTTOM,
    ROW_LEFT,
    ROW_RIGHT,
    SIDE_CORNER_TOP_LEFT,
    SIDE_CORNER_TOP_RIGHT,
    SIDE_CORNER_BOTTOM_LEFT,
    SIDE_CORNER_BOTTOM_RIGHT,
    MIDDLE
};

struct TileFrameOption {

    bool condition;
    TileFrameType frameType;
};

class World {

    public:

        World();
        ~World();
        
        void update(Vector2 playerVelocity);
        void frameLogicNeighbor(Tile &thisTile);
        void writeData();

        std::vector<Tile> tiles;
    private:

        std::map<TileFrameType, Vector2> tileFrameMap;

        void readData();
        void mapOutTileFrames();
};