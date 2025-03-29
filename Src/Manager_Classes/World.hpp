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
        Rectangle offsetCheckObject = {0, 0, 60, 60};
    private:


        void placeTiles();
};