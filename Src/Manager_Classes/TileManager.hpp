#pragma once
#include <raylib.h>
#include <vector>
#include <map>
#include "../Entity_Classes/Tile.hpp"
#include "../Entity_Classes/Plant.hpp"
#include "Elements.hpp"
#include "NeighborTypes.hpp"

class TileManager {

    public:

        TileManager();
        ~TileManager();

        void update();
        void updateFrameType(const Rectangle contactedArea);

        std::vector<Tile> tiles;
        std::vector<Plant> plants;
        
        TileType selectedType = GROUND;
        Decoration decoration;
        
        private:
        
        float elapsedFrame = 0.0f;
        int currentFrame = 0;

        void animate();
        void setFrameAnimationForSpecficTiles(Tile &tile);
        void mapTileFrames();
        void checkNeighbors(Tile &thisTile);

};