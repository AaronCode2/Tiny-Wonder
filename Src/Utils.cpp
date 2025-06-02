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

void Utils::exitApp(std::string errorInfo) {

    CloseWindow();
    std::cerr << "\033[31m" << errorInfo << '\n';

#ifdef DEBUG

    __debugbreak;
#else

    std::cout << "Press ENTER to exit the Application as a Error has occured [PLAYER]: ";
    std::cin.get();

    exit(EXIT_FAILURE);
#endif
} 

bool Utils::isSameXY(Rectangle aObject, Rectangle bObject) {

    return (
        aObject.x == bObject.x &&
        aObject.y == bObject.y
    );
}

bool Utils::isSameXY(Vector2 aObject, Vector2 bObject) {

    return (
        aObject.x == bObject.x &&
        aObject.y == bObject.y
    );
}

bool Utils::isSameXY(Vector2 aObject, Vector2 bObject, Vector2 bObject2) {

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