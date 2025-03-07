#pragma once
#include <fstream>
#include <sstream>
#include <vector>
#include <raylib.h>
#include "../Utils.hpp"
#include "Tile.hpp"

// TODO: Make World

#define NUM_SIZE 7

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

        void init();
        void update();

    private:

        std::vector<Tile> tiles;

        void readData();
        void writeData();
};