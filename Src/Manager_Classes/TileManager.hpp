#pragma once
#include <raylib.h>
#include <vector>
#include <map>
#include "../Entity_Classes/Tile.hpp"

enum GrassType {

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
        void checkNeighbors(Tile &thisTile);
        std::vector<Tile> tiles;

    private:

        std::map<GrassType, Vector2> grassMap;

        void mapGrassFrames();

};