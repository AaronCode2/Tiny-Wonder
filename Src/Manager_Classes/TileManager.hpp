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


class TileManager {

    public:

        TileManager();
        ~TileManager();

        void update();
        void updateFrameType(Rectangle contactedArea);
        std::vector<Tile> tiles;
        
        TileType selectedType = LIGHT_GRASS;

        private:
        
        std::map<TileNeighborType, Vector2> groundMap;
        std::map<TileNeighborType, Vector2> lightGrassMap;
        std::map<TileNeighborType, Vector2> darkGrassMap;
        
        void mapTileFrames();
        void checkNeighbors(Tile &thisTile);

};