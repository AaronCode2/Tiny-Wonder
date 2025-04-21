#include "UI.hpp"

void UI::update() {

    inventoryRec = {

        GetScreenWidth() - 1200.0f,
        GetScreenHeight() - 120.0f,
        700,
        70, 
    };

    draw();
}

void UI::draw() {

    DrawRectangleRounded(inventoryRec, 0.5f, 4, GRAY);
}