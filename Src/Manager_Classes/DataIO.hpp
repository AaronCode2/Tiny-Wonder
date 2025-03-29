#pragma once
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include "../Entity_Classes/Tile.hpp"

#define NUM_SIZE 7
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

        DataIO(std::vector<Tile> &tiles);
        ~DataIO() { writeTileData(); };

        void writeTileData();
        void readTileData();

        void readWorldPosData(Vector2 &newWorldPos);
        void writeWorldPosData(Vector2 worldPos);

    private:

    std::vector<Tile> &tiles;
};
