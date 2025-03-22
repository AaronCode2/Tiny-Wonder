#include "Utils.hpp"

Input getInput() {

    return {

        (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)),
        (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)),
        (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)),
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