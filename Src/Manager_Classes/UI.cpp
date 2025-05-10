#include "UI.hpp"

UI::UI(TileType &selectedType):
    selectedType(selectedType)
{

    imageTilesSrcPos[GROUND] = {6, 7};
    imageTilesSrcPos[DARK_GRASS] = {5, 2};
    imageTilesSrcPos[LIGHT_GRASS] = {5, 4};
    imageTilesSrcPos[SMALL_GRASS] = {0, 0};
    imageTilesSrcPos[SEA_DECORATIONS] = {8, 7};
    imageTilesSrcPos[DIRT] = {3, 11};

    hotBar.base.color = {130, 130, 130, 230};

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

        (GetScreenWidth() / 2) - (410.0f / 2),
        GetScreenHeight() - 120.0f,
        410,
        90, 
    };

    draw();
}

void UI::draw() {

    DrawRectangleRounded(hotBar.base.object, 0.2, 4, {255, 209, 157, 255});

    GameMode preSelectedMode = Settings::gameMode;

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

        Vector2 buttonImageSrc = {0, 0};

        if(Mouse::isHovering(buttonObject)) {

            Settings::gameMode = GameMode::EXPLORE;
            buttonImageSrc.x = 1;
        }
    

        if(Mouse::isClickedL(buttonObject)) {

            selectedType = (TileType) i;
        }

        DrawTexturePro(
            buttonImage,
            ButtonImage::getImageSrc(buttonImageSrc), buttonObject,
            {0, 0}, 0, WHITE
        );

        DrawTexturePro(
            Tile::image, imageSrcRect, 
            slot.object, {0, 0},
            0, (buttonImageSrc.x == 0) ? WHITE : (Color) {255, 255, 255, 100}
        );
    }
    
    // gameMode = preSelectedMode;
}