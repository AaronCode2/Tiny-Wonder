#pragma once
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <thread>
#include <math.h>
#include <raylib.h>
#include "NeighborTypes.hpp"
#include "../Utils.hpp"
#include "../Settings.hpp"
#include "../Entity_Classes/Tile.hpp"
#include "TileManager.hpp"
#include "Elements.hpp"

#define UNKNOWN_TILE (Vector2) {3, 11}

class World {

    public:
        
        World(Slot &selectedSlot);
        ~World();

        TileManager tileManager;
        Vector2 worldPos = {0, 0};

        void update();
        static Texture2D selectorImage;
        Slot &selectedSlot;
    private:

        Rectangle selectionObject;
        Rectangle checkerArea;
        Rectangle deleteArea;

        void checkMouseActions();
};