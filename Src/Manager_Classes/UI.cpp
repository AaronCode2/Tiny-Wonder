#include "UI.hpp"

void UI::update() {

    inventory.base.object = {

        (GetScreenWidth() / 2) - (700.0f / 2),
        GetScreenHeight() - 120.0f,
        700,
        70, 
    };

    draw();
}

void UI::draw() {

    DrawRectangleRounded(inventory.base.object, 0.5f, 4, GRAY);
}