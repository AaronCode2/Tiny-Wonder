#pragma once
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <raylib.h>
#include "../Utils.hpp"
#include "../Entity_Classes/Tile.hpp"
#include "TileManager.hpp"

class World {

    public:
        
        void update();

        TileManager tileManager;
    private:

        void placeTiles();
};