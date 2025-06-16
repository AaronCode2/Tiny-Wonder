#pragma once
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include "../Entity_Classes/Tile.hpp"
#include "../Manager_Classes/NeighborTypes.hpp"

#define NUM_SIZE 8
#define POS_ELEMENTS 4
#define FLOAT_PRECISION 0 // To avoid Tiles not aligning with each other
#define POS_PATH "../Data/Pos.txt"
#define TILE_MAP_PATH "../Data/TileMap.txt"

enum fileReadStructure {

    X = 0,
    Y,
    WIDTH,
    HEIGHT,
    FRAME_X,
    FRAME_Y,
    ID,
    DECORATION_ID
};

enum PosStructure {

    ERROR = -1,
    WORLD_X,
    WORLD_Y,
    PLAYER_X,
    PLAYER_Y
};

class DataIO {
    
    public:

        DataIO(std::vector<Tile> &tiles, Vector2 &worldPos, Rectangle &playerObject);
        ~DataIO();

        void writeTileData();
        void readTileData();

        void readPosData();
        void writePosData();

    private:

    std::vector<Tile> &tiles;
    Vector2 &worldPos;
    Rectangle &playerObject;
};
