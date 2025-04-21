#include "UI.hpp"

UI::UI() {

    imageSrcPos[GROUND] = {1, 2};

    inventory.base.color = {130, 130, 130, 230};

    for(int i = 0; i < MAX_SLOTS; i++) {

        unsigned char color = 200 - (i * 10);

        inventory.slots[i] = {
            {
                ((GetScreenWidth() / 2) - (450.0f / 2) + 30) + (i * 80.0f), 
                GetScreenHeight() - 110.0f, 
                70, 70
            },
            {color, color, color, 255},
            imageSrcPos[(TileType) i]
        };
    }
}

void UI::update() {

    inventory.base.object = {

        (GetScreenWidth() / 2) - (450.0f / 2),
        GetScreenHeight() - 120.0f,
        450,
        90, 
    };

    draw();
}

void UI::draw() {

    DrawRectangleRounded(inventory.base.object, 0.5f, 4, inventory.base.color);

    for(const auto slots : inventory.slots) {

        DrawRectangleRounded(slots.object, 0.5f, 4, slots.color);
    }   
}