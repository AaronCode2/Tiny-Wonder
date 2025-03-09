#include "Utils.hpp"

Input getInput() {

    return {

        IsKeyDown(KEY_W),
        IsKeyDown(KEY_S),
        IsKeyDown(KEY_A),
        IsKeyDown(KEY_D),
    };
}

Color Utils::testColor = {255, 0, 0, 100};

bool Utils::isSameRect(Rectangle aObject, Rectangle bObject) {

    return (

        aObject.x == bObject.x &&
        aObject.y == bObject.y &&
        aObject.width == aObject.width &&
        aObject.height == aObject.height
    );
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