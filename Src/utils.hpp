#pragma once
#include <raylib.h>
#include <iostream>

#define DEBUG_ACTIVE false
#define print(x) std::cout << x << '\n'
#define EMPTY_RECT (Rectangle) {0, 0, 0, 0}
#define WH_EMPTY_RECT (Rectangle) {0, 0, TILE_SIZE, TILE_SIZE}

#define SAVY_YELLOW (Color) {255, 209, 157, 255}
#define MOUSE_BROWN (Color) {163, 90, 66, 255}
#define SAVY_BROWN (Color) {215, 147, 106, 255}
#define DARK_BROWN (Color) {181, 108, 78, 255}

#define FONT_SIZE 30
#define FONT_SPACING 1


struct Input {

    bool up;
    bool down;
    bool left;
    bool right;
};

Input getInput();

namespace Utils {

    extern float deltaTimeIt;
    extern Color const testColor;
    Rectangle getScreenRect(); 

    std::string formatZeros(int num, int width);

    bool isSameXY(const Rectangle aObject, const Rectangle bObject);
    bool isSameXY(const Vector2 aObject, const Vector2 bObject);
    bool isSameXY(const Vector2 aObject, const Vector2 bObject, const Vector2 bObject2);
    
    void collisionActionX(Rectangle &aObject, const Rectangle ahitBox, const Rectangle bHitBox, Vector2 &aVelocity, bool resetVelocity = true);
    void collisionActionY(Rectangle &aObject, const Rectangle ahitBox, const Rectangle bHitBox, Vector2 &aVelocity, bool resetVelocity = true);

    void exitApp(const std::string errorInfo);

    extern Font font;
} 

namespace Mouse {

    bool isHovering(const Rectangle object);
    bool isClickedL(const Rectangle object);
    bool isClickedR(const Rectangle object);

    bool isClickedOnceR(const Rectangle object);
}