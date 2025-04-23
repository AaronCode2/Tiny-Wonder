#include "UI.hpp"

UI::UI() {

    imageSrcPos[GROUND] = {6, 7};
    imageSrcPos[LIGHT_GRASS] = {5, 1};
    imageSrcPos[DARK_GRASS] = {5, 6};
    imageSrcPos[SMALL_GRASS] = {0, 0};
    imageSrcPos[SEA_DECORATIONS] = {8, 7};
    imageSrcPos[DIRT] = {3, 11};

    inventory.base.color = {130, 130, 130, 230};

    for(int i = 0; i < MAX_SLOTS; i++) {

        unsigned char color = 200 - (i * 10);

        inventory.slots[i] = {
            {
                ((GetScreenWidth() / 2) - (450.0f / 2) + 30) + (i * 80.0f), 
                GetScreenHeight() - 110.0f, 
                70, 70
            },
            {color, color, color, 255}
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

    for(int i = 0 ; i < MAX_SLOTS; i++) {

        Slot slot = inventory.slots[i];
        Rectangle imageSrcRect = {

            (Tile::image.width / 9) * imageSrcPos[(TileType) i].x,
            (Tile::image.height / 19) * imageSrcPos[(TileType) i].y,
            (Tile::image.width / 9.0f), 
            (Tile::image.height / 19.0f)
        };

        DrawRectangleRounded(slot.object, 0.5f, 4, slot.color);
        DrawTexturePro(
            Tile::image, imageSrcRect, 
            slot.object, {0, 0},
            0, WHITE
        );
    }   
}