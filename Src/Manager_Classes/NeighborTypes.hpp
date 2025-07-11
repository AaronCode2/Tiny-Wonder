#pragma once
#include <raylib.h>
#include <map>

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

enum Decoration {

    NOT_SET = -1,
    THREE_WEED,
    FOUR_WEED,
    GROWING_WEED,
    YELLOW_FLOWER,
    TWO_WHITE_FLOWER,
    THREE_WHITE_FLOWER,
    THE_ROCK, // :/ ???
    SEAWEED
};

namespace NeighborTypes {

    extern std::map<TileNeighborType, Vector2> groundMap;
    extern std::map<TileNeighborType, Vector2> lightGrassMap;
    extern std::map<TileNeighborType, Vector2> darkGrassMap;
    extern std::map<TileNeighborType, Vector2> dirtMap;
    extern std::map<Decoration, Vector2> decorationMap;
    
    void defineTypes();
};
