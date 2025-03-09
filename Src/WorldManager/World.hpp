#pragma once
#include <fstream>
#include <sstream>
#include <vector>
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

class World {

    public:

        World();
        ~World();
        
        void update();
        void writeData();

    private:

        std::vector<Tile> tiles;

        void readData();
        void frameLogicNeighbor(Tile &thisTile);
};