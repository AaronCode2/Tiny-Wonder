#pragma once
#include <raylib.h>
#include <vector>
#include <map>
#include "../Entity_Classes/Tile.hpp"
#include "NeighborTypes.hpp"

class TileManager {

    public:

        TileManager();
        ~TileManager();

        void update();
        void updateFrameType(Rectangle contactedArea);
        std::vector<Tile> tiles;
        
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