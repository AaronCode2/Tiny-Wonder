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
#include "../GlobalVars.hpp"
#include "../Entity_Classes/Tile.hpp"
#include "TileManager.hpp"

struct Slot;

#define UNKNOWN_TILE (Vector2) {3, 11}

class World {

    public:
        
        World();
        ~World();

        TileManager tileManager;
        Vector2 worldPos = {0, 0};

        void update();
        static Texture2D selectorImage;
        static Slot *selectedSlot;
        static void getSelectedSlot(Slot *newSelectedSlot);

    private:

        Rectangle selectionObject;
        Rectangle checkerArea;
        Rectangle deleteArea;

        void checkMouseActions();
};