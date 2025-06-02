#pragma once
#include <raylib.h>
#include <iostream>

#define print(x) std::cout << x << '\n'

struct Input {

    bool up;
    bool down;
    bool left;
    bool right;
};

Input getInput();

namespace Utils {

    extern Color testColor;
    Rectangle getScreenRect(); 

    bool isSameXY(Rectangle aObject, Rectangle bObject);
    bool isSameXY(Vector2 aObject, Vector2 bObject);
    bool isSameXY(Vector2 aObject, Vector2 bObject, Vector2 bObject2);
    
    void exitApp(std::string errorInfo);
} 

namespace Mouse {

    bool isHovering(Rectangle object);
    bool isClickedL(Rectangle object);
    bool isClickedR(Rectangle object);
}