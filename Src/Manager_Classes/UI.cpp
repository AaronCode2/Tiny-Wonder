#include "UI.hpp"

UI::UI() {

    imageTilesSrcPos[GROUND] = {6, 7};
    imageTilesSrcPos[LIGHT_GRASS] = {5, 2};
    imageTilesSrcPos[DARK_GRASS] = {5, 4};
    imageTilesSrcPos[SMALL_GRASS] = {0, 0};
    imageTilesSrcPos[SEA_DECORATIONS] = {8, 7};
    imageTilesSrcPos[DIRT] = {3, 11};

    hotBar.base.color = {130, 130, 130, 230};

    BasesImage::setImage(basesImage);
    ButtonImage::setImage(buttonImage);

    for(int i = 0; i < MAX_SLOTS; i++) {

        hotBar.slots[i] = {
            {
                ((GetScreenWidth() / 2) - (450.0f / 2) + 30) + (i * 80.0f), 
                GetScreenHeight() - 110.0f, 
                70, 70
            },
        };
    }
}

void UI::update() {

    hotBar.base.object = {

        (GetScreenWidth() / 2) - (470.0f / 2),
        GetScreenHeight() - 130.0f,
        470,
        110, 
    };

    draw();
}

void UI::draw() {

    DrawTexturePro(
        basesImage, BasesImage::getImageSrc({0, 0}),
        hotBar.base.object,
        {0, 0}, 0,
        WHITE
    );

    for(int i = 0 ; i < MAX_SLOTS; i++) {

        Slot slot = hotBar.slots[i];
        Rectangle imageSrcRect = {

            (Tile::image.width / 9) * imageTilesSrcPos[(TileType) i].x,
            (Tile::image.height / 19) * imageTilesSrcPos[(TileType) i].y,
            (Tile::image.width / 9.0f), 
            (Tile::image.height / 19.0f)
        };

        Rectangle buttonObject = {
            slot.object.x - 24,
            slot.object.y - 25,
            120, 120
        };

        DrawTexturePro(
            buttonImage,
            ButtonImage::getImageSrc({0, 0}), buttonObject,
            {0, 0}, 0, WHITE
        );

        DrawTexturePro(
            Tile::image, imageSrcRect, 
            slot.object, {0, 0},
            0, WHITE
        );
    }   
}