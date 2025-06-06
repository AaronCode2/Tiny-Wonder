#pragma once
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <thread>
#include <raylib.h>
#include "NeighborTypes.hpp"
#include "../Utils.hpp"
#include "../Settings.hpp"
#include "../Entity_Classes/Tile.hpp"
#include "TileManager.hpp"

#define UNKNOWN_TILE (Vector2) {3, 11}

class World {

    public:
        
        World();
        ~World();

        TileManager tileManager;
        Vector2 worldPos = {0, 0};

        void update();
    private:

        Rectangle selectionObject;
        Rectangle checkerArea;
        Rectangle deleteArea;

        Texture2D selectorImage;

        void checkMouseActions();
};