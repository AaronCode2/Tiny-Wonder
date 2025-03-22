#pragma once
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include "../Entity_Classes/Tile.hpp"

#define NUM_SIZE 7

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

        DataIO(std::vector<Tile> &tiles, std::string path);
        ~DataIO() { writeTileData(); };

        void writeTileData();
        void readTileData();
    private:

    std::vector<Tile> &tiles;
    std::string path;

};
