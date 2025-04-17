#pragma once
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include "../Entity_Classes/Tile.hpp"

#define NUM_SIZE 7
#define FLOAT_PRECISION 2
#define WORLD_POS_PATH "../Data/WorldPos.txt"
#define TILE_MAP_PATH "../Data/TileMap.txt"

enum fileReadStructure {

    X = 0,
    Y,
    WIDTH,
    HEIGHT,
    FRAME_X,
    FRAME_Y,
    ID
};

class DataIO {
    
    public:

        DataIO(std::vector<Tile> &tiles, Vector2 &worldPos);
        ~DataIO();

        void writeTileData();
        void readTileData();

        void readWorldPosData();
        void writeWorldPosData();

    private:

    std::vector<Tile> &tiles;
    Vector2 &worldPos;
};
