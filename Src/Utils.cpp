#include "Utils.hpp"

Input getInput() {

    return {

        (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)),
        (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)),
        (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)),
        (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)),
    };
}

Color Utils::testColor = {255, 0, 0, 100};

bool Utils::isSameRect(Rectangle aObject, Rectangle bObject) {

    return (

        aObject.x == bObject.x &&
        aObject.y == bObject.y
    );
}

int Utils::countDecimalPlaces(float num) {

    std::string str = std::to_string(num);
    
    size_t lastNonZero = str.find_last_not_of('0');
    
    if(lastNonZero != std::string::npos && lastNonZero > str.find('.'))
        return (int) (lastNonZero - str.find('.'));
    
    return -1;
}

Rectangle Utils::getScreenRect() {

    return {0, 0, (float) GetScreenWidth(), (float) GetScreenHeight()};
}

bool Mouse::isHovering(Rectangle object) {

    return CheckCollisionPointRec(GetMousePosition(), object);
}

bool Mouse::isClickedL(Rectangle object) {

    return (CheckCollisionPointRec(GetMousePosition(), object) && IsMouseButtonDown(MOUSE_BUTTON_LEFT));
}

bool Mouse::isClickedR(Rectangle object) {

    return (CheckCollisionPointRec(GetMousePosition(), object) && IsMouseButtonDown(MOUSE_BUTTON_RIGHT));
}