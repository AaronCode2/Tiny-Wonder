#pragma once
#include <raylib.h>
#include <iostream>

#define print(x) std::cout << x << '\n'
#define EMPTY_RECT (Rectangle) {0, 0, 0, 0}
#define WH_EMPTY_RECT (Rectangle) {0, 0, TILE_SIZE, TILE_SIZE}

        // for(const auto tileHitBox : tile.getHitBoxes()) {

        //     if(!CheckCollisionRecs(hitBox, tileHitBox)) continue;
            
        //     DrawText("COLLISON!!!", 400, 400, 30, RED);

        //     if(velocity.y > 0) {
                
        //         const float offset = hitBox.y - object.y + hitBox.height;

        //         object.y = tileHitBox.y - offset;
        //     }
        
        //     if(velocity.y < 0) {
                
        //         const float offset = hitBox.y - object.y;

        //         object.y = tileHitBox.y + tileHitBox.height - offset;
        //     }

        //     velocity.y = 0;
        //     break;
        // }

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
    
    void collisionActionX(Rectangle &aObject, const Rectangle ahitBox, const Rectangle bHitBox, Vector2 &aVelocity);
    void collisionActionY(Rectangle &aObject, const Rectangle ahitBox, const Rectangle bHitBox, Vector2 &aVelocity);

    void exitApp(const std::string errorInfo);
} 

namespace Mouse {

    bool isHovering(const Rectangle object);
    bool isClickedL(const Rectangle object);
    bool isClickedR(const Rectangle object);
}