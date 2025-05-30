#pragma once
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <raylib.h>
#include <cmath>
#include "../Utils.hpp"
#include "../Entity_Classes/Tile.hpp"
#include "TileManager.hpp"
#include <cmath>

class World {

    public:
        
        void update();

        TileManager tileManager;
        Vector2 worldPos = {0, 0};
    private:


        void placeTiles();
};