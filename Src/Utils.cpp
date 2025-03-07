#include "Utils.hpp"

Input getInput() {

    return {

        IsKeyDown(KEY_W),
        IsKeyDown(KEY_S),
        IsKeyDown(KEY_A),
        IsKeyDown(KEY_D),
    };
}

bool Mouse::isHovering(Rectangle object) {

    return CheckCollisionPointRec(GetMousePosition(), object);
}

bool Mouse::isClicked(Rectangle object) {

    return (CheckCollisionPointRec(GetMousePosition(), object) && IsMouseButtonDown(MOUSE_BUTTON_LEFT));
}