#include "NeighborTypes.hpp"

void NeighborTypes::defineTypes(){

    NeighborTypes::groundMap[CORNER_BOTTOM_RIGHT] = {1, 9};
    NeighborTypes::groundMap[CORNER_BOTTOM_LEFT] = {0, 9};
    NeighborTypes::groundMap[CORNER_TOP_RIGHT] = {1, 7};
    NeighborTypes::groundMap[CORNER_TOP_LEFT] = {0, 7};
    NeighborTypes::groundMap[ROW_TOP] = {3, 9};
    NeighborTypes::groundMap[ROW_RIGHT] = {2, 8};
    NeighborTypes::groundMap[ROW_LEFT] = {4, 8};
    NeighborTypes::groundMap[ROW_BOTTOM] = {3, 10};
    NeighborTypes::groundMap[SIDE_CORNER_BOTTOM_RIGHT] = {2, 10};
    NeighborTypes::groundMap[SIDE_CORNER_BOTTOM_LEFT] = {4, 10};
    NeighborTypes::groundMap[SIDE_CORNER_TOP_RIGHT] = {2, 9};
    NeighborTypes::groundMap[SIDE_CORNER_TOP_LEFT] = {4, 9};
    NeighborTypes::groundMap[MIDDLE] = {3, 1};

    NeighborTypes::lightGrassMap[CORNER_BOTTOM_RIGHT] = {7, 6};
    NeighborTypes::lightGrassMap[CORNER_BOTTOM_LEFT] = {5, 6};
    NeighborTypes::lightGrassMap[CORNER_TOP_RIGHT] = {7, 4};
    NeighborTypes::lightGrassMap[CORNER_TOP_LEFT] = {5, 4};
    NeighborTypes::lightGrassMap[ROW_TOP] = {6, 4};
    NeighborTypes::lightGrassMap[ROW_BOTTOM] = {6, 6};
    NeighborTypes::lightGrassMap[ROW_RIGHT] = {7, 5};
    NeighborTypes::lightGrassMap[ROW_LEFT] = {5, 5};
    NeighborTypes::lightGrassMap[SIDE_CORNER_TOP_RIGHT] = {3, 3};
    NeighborTypes::lightGrassMap[SIDE_CORNER_TOP_LEFT] = {2, 3};
    NeighborTypes::lightGrassMap[SIDE_CORNER_BOTTOM_RIGHT] = {3, 4};
    NeighborTypes::lightGrassMap[SIDE_CORNER_BOTTOM_LEFT] = {2, 4};
    NeighborTypes::lightGrassMap[MIDDLE] = {6, 5};

    NeighborTypes::darkGrassMap[CORNER_BOTTOM_RIGHT] = {7, 3};
    NeighborTypes::darkGrassMap[CORNER_BOTTOM_LEFT] = {5, 3};
    NeighborTypes::darkGrassMap[CORNER_TOP_RIGHT] = {7, 1};
    NeighborTypes::darkGrassMap[CORNER_TOP_LEFT] = {5, 1};
    NeighborTypes::darkGrassMap[ROW_TOP] = {6, 1};
    NeighborTypes::darkGrassMap[ROW_BOTTOM] = {6, 3};
    NeighborTypes::darkGrassMap[ROW_RIGHT] = {7, 2};
    NeighborTypes::darkGrassMap[ROW_LEFT] = {5, 2};
    NeighborTypes::darkGrassMap[SIDE_CORNER_TOP_RIGHT] = {3, 5};
    NeighborTypes::darkGrassMap[SIDE_CORNER_TOP_LEFT] = {2, 5};
    NeighborTypes::darkGrassMap[SIDE_CORNER_BOTTOM_RIGHT] = {3, 6};
    NeighborTypes::darkGrassMap[SIDE_CORNER_BOTTOM_LEFT] = {2, 6};
    NeighborTypes::darkGrassMap[MIDDLE] = {6, 2};

    NeighborTypes::dirtMap[CORNER_BOTTOM_RIGHT] = {7, 16};
    NeighborTypes::dirtMap[CORNER_BOTTOM_LEFT] = {5, 16};
    NeighborTypes::dirtMap[CORNER_TOP_RIGHT] = {7, 14};
    NeighborTypes::dirtMap[CORNER_TOP_LEFT] = {5, 14};
    NeighborTypes::dirtMap[ROW_TOP] = {6, 14};
    NeighborTypes::dirtMap[ROW_BOTTOM] = {6, 16};
    NeighborTypes::dirtMap[ROW_RIGHT] = {7, 15};
    NeighborTypes::dirtMap[ROW_LEFT] = {5, 15};
    NeighborTypes::dirtMap[SIDE_CORNER_TOP_RIGHT] = {2, 18};
    NeighborTypes::dirtMap[SIDE_CORNER_TOP_LEFT] = {3, 18};
    NeighborTypes::dirtMap[SIDE_CORNER_BOTTOM_RIGHT] = {2, 17};
    NeighborTypes::dirtMap[SIDE_CORNER_BOTTOM_LEFT] = {3, 17};
    NeighborTypes::dirtMap[MIDDLE] = {6, 15};

    NeighborTypes::decorationMap[THREE_WEED] = {0, 0};
    NeighborTypes::decorationMap[FOUR_WEED] = {0, 1};
    NeighborTypes::decorationMap[GROWING_WEED] = {0, 2};
    NeighborTypes::decorationMap[YELLOW_FLOWER] = {1, 0};
    NeighborTypes::decorationMap[THREE_WHITE_FLOWER] = {1, 1};
    NeighborTypes::decorationMap[TWO_WHITE_FLOWER] = {1, 2};
    NeighborTypes::decorationMap[THE_ROCK] = {8, 7};
    NeighborTypes::decorationMap[SEAWEED] = {8, 9};
}