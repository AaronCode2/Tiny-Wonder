#pragma once
#include <fstream>
#include <sstream>
#include <vector>
#include <raylib.h>
#include "../Utils.hpp"
#include "Tile.hpp"

// TODO: Make World

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