#include "Utils.hpp"

Input getInput() {

    return {

        (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)),
        (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)),
        (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)),
        (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)),
    };
}

Color const Utils::testColor = {255, 0, 0, 100};
float Utils::deltaTimeIt = 0.0f;

Font Utils::font;
int Utils::fontSize;

void Utils::exitApp(const std::string errorInfo) {

    CloseWindow();
    std::cerr << "\033[31m" << errorInfo << '\n';

#if DEBUG_ENABLED

    __debugbreak;
#else

    std::cout << "Press ENTER to exit the Application as a Error has occured [PLAYER]: ";
    std::cin.get();

    exit(EXIT_FAILURE);
#endif
} 

bool Utils::isSameXY(const Rectangle aObject, const Rectangle bObject) {

    return (
        aObject.x == bObject.x &&
        aObject.y == bObject.y
    );
}

bool Utils::isSameXY(const Vector2 aObject, const Vector2 bObject) {

    return (
        aObject.x == bObject.x &&
        aObject.y == bObject.y
    );
}

bool Utils::isSameXY(const Vector2 aObject, const Vector2 bObject, const Vector2 bObject2) {

    return (
        (
            aObject.x == bObject.x &&
            aObject.y == bObject.y
        ) 
        ||
        (
            aObject.x == bObject2.x &&
            aObject.y == bObject2.y
        )
    );
}

void Utils::collisionActionX(Rectangle &aObject, const Rectangle ahitBox, const Rectangle bHitBox, Vector2 &aVelocity, bool resetVelocity) {

    // Double-check Collision #BUG-FIX

    if(!CheckCollisionRecs(ahitBox, bHitBox)) 
        return;
            
    DrawText("COLLISON!!!", 400, 400, 30, RED);

    if(aVelocity.x > 0) {
                
        const float offset = ahitBox.x - aObject.x + ahitBox.width + 0.01;

        aObject.x = bHitBox.x - offset;
    }
        
    if(aVelocity.x < 0) {
                
        const float offset = ahitBox.x - aObject.x - 0.01;

        aObject.x = bHitBox.x + bHitBox.width - offset;
    }

    if(resetVelocity) aVelocity.x = 0;
}

void Utils::collisionActionY(Rectangle &aObject, const Rectangle ahitBox, const Rectangle bHitBox, Vector2 &aVelocity, bool resetVelocity) {

    // Double-check Collision #BUG-FIX

    if(!CheckCollisionRecs(ahitBox, bHitBox)) 
        return;
            
    DrawText("COLLISON!!!", 400, 400, 30, RED);

    if(aVelocity.y > 0) {
                
        const float offset = ahitBox.y - aObject.y + ahitBox.height;

        aObject.y = bHitBox.y - offset;
    }
        
    if(aVelocity.y < 0) {
                
        const float offset = ahitBox.y - aObject.y;

        aObject.y = bHitBox.y + bHitBox.height - offset;
    }

    if(resetVelocity) aVelocity.y = 0;
}

Rectangle Utils::getScreenRect() {

    return {0, 0, (float) GetScreenWidth(), (float) GetScreenHeight()};
}

bool Mouse::isHovering(const Rectangle object) {

    return CheckCollisionPointRec(GetMousePosition(), object);
}

bool Mouse::isClickedL(const Rectangle object) {

    return (CheckCollisionPointRec(GetMousePosition(), object) && IsMouseButtonDown(MOUSE_BUTTON_LEFT));
}

bool Mouse::isClickedR(const Rectangle object) {

    return (CheckCollisionPointRec(GetMousePosition(), object) && IsMouseButtonDown(MOUSE_BUTTON_RIGHT));
}

bool Mouse::isClickedOnceR(const Rectangle object) {


    return (CheckCollisionPointRec(GetMousePosition(), object) && IsMouseButtonPressed(MOUSE_BUTTON_RIGHT));
}

std::string Utils::formatZeros(int num, int width) {

    std::string numText = std::to_string(num);

    int leadingZero = width - numText.length();
    
    numText = 'x' + std::string(leadingZero, '0') + numText;

    return numText;
}
