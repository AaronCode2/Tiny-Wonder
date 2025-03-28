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

class World {

    public:
        
        void update(Vector2 playerVeclocity);

        TileManager tileManager;
    private:

        Rectangle offsetCheckObject = {60, 60, 60, 60};

        void placeTiles();
};