#pragma once
#include <vector>
#include "Tile.hpp"

// TODO: Make World

class World {

    public:

        World();
        ~World();

    private:

        std::vector<Tile> tiles;

        void update();
        void readData();
};