#include "TileManager.hpp"

TileManager::TileManager() {

    Tile::image = LoadTexture("../Assets/Tiles/Tile.png");
    mapGrassFrames();
}

TileManager::~TileManager() {

    UnloadTexture(Tile::image);
}

void TileManager::update() {

    for(auto &tile : tiles) {

        tile.update();
    }
}

void TileManager::mapGrassFrames() {

    enum TileFrameType {

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
}
