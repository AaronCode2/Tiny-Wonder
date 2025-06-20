#pragma once
#include <raylib.h>
#include <iostream>

#define print(x) std::cout << x << '\n'
#define EMPTY_RECT (Rectangle) {0, 0, 0, 0}
#define WH_EMPTY_RECT (Rectangle) {0, 0, TILE_SIZE, TILE_SIZE}

struct Input {

    bool up;
    bool down;
    bool left;
    bool right;
};

Input getInput();

namespace Utils {

    extern Color const testColor;
    Rectangle getScreenRect(); 

    bool isSameXY(const Rectangle aObject, const Rectangle bObject);
    bool isSameXY(const Vector2 aObject, const Vector2 bObject);
    bool isSameXY(const Vector2 aObject, const Vector2 bObject, const Vector2 bObject2);
    
    void exitApp(const std::string errorInfo);
} 

namespace Mouse {

    bool isHovering(const Rectangle object);
    bool isClickedL(const Rectangle object);
    bool isClickedR(const Rectangle object);
}