#pragma once
#include <raylib.h>
#include <vector>
#include <map>
#include "../Entity_Classes/Tile.hpp"

enum TileNeighborType {

    CORNER_BOTTOM_LEFT = 0,
    CORNER_BOTTOM_RIGHT,
    CORNER_TOP_LEFT,
    CORNER_TOP_RIGHT,
    ROW_TOP,
    ROW_BOTTOM,
    ROW_LEFT,
    ROW_RIGHT,
    SIDE_CORNER_TOP_LEFT,
    SIDE_CORNER_TOP_RIGHT,
    SIDE_CORNER_BOTTOM_LEFT,
    SIDE_CORNER_BOTTOM_RIGHT,
    MIDDLE
};

static std::map<TileNeighborType, Vector2> groundMap;
static std::map<TileNeighborType, Vector2> lightGrassMap;
static std::map<TileNeighborType, Vector2> darkGrassMap;

class TileManager {

    public:

        TileManager();
        ~TileManager();

        void update();
        void updateFrameType(Rectangle contactedArea);
        std::vector<Tile> tiles;
        
        TileType selectedType = LIGHT_GRASS;

        private:
        
        
        void mapTileFrames();
        void checkNeighbors(Tile &thisTile);

};