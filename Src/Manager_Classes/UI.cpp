#include "UI.hpp"

UI::UI(TileType &selectedType):
    selectedType(selectedType), inventory(inventory)
{

    imageTilesSrcPos[GROUND] = {6, 7};
    imageTilesSrcPos[DARK_GRASS] = {5, 2};
    imageTilesSrcPos[LIGHT_GRASS] = {5, 4};
    imageTilesSrcPos[DECORATIONS] = {0, 0};
    imageTilesSrcPos[DIRT] = {3, 16};

    gameModeSrc[GameMode::EXPLORE] = {0, 17};
    gameModeSrc[GameMode::BUILD] = {0, 16};
    gameModeSrc[GameMode::TRADE] = {2, 12};

    gameModeStrings[GameMode::EXPLORE] = "GO";
    gameModeStrings[GameMode::BUILD] = "BUILD";
    gameModeStrings[GameMode::TRADE] = "TRADE";

    gameModeLog.setFrame({5, 19});

    hotBar.base.color = {130, 130, 130, 230};

    ButtonImage::setImage(buttonImage);

    inventory.buttonImage = buttonImage;
    inventory.init();


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

UI::~UI() {

    UnloadTexture(buttonImage);
    UnloadTexture(inventory.buttonImage);
    UnloadTexture(inventory.itemSrcImage.image);
    UnloadTexture(playerPhoto.image);
    UnloadTexture(playerInfo.image);
}

void UI::update() {

    hotBar.base.object = {

        (GetScreenWidth() / 2) - (410.0f / 2),
        GetScreenHeight() - 120.0f,
        410,
        90, 
    };

    gameModeLog.object.y += std::sin(Utils::deltaTimeIt * 7.5) * 0.05;

    gameModeLog.setSrcXY(gameModeSrc[Settings::gameMode]);

    draw();
}

void UI::draw() {

    DrawRectangleRec({20, 20, 100, 90}, SAVY_YELLOW);
    playerPhoto.draw();
    playerInfo.draw();

    DrawTextEx(
        Utils::font, gameModeStrings[Settings::gameMode].c_str(), 
        {75, 154}, FONT_SIZE, 
        FONT_SPACING, BLACK
    );

    gameModeLog.draw();

    DrawRectangleRounded(hotBar.base.object, 0.2, 4, SAVY_YELLOW);
    
    Settings::HoveringOverMenu = false; 

    inventory.update();

    if(Settings::gameMode == GameMode::EXPLORE) 
        return;

    for(int i = 0 ; i < MAX_SLOTS; i++) {

        Slotbar slot = hotBar.slots[i];
        Rectangle imageSrcRect = {

            (Tile::image.width / 9) * imageTilesSrcPos[(TileType) i].x,
            (Tile::image.height / 19) * imageTilesSrcPos[(TileType) i].y,
            (Tile::image.width / 9.0f), 
            (Tile::image.height / 19.0f)
        };

        Rectangle buttonObject = {
            slot.object.x - 25,
            slot.object.y - 25,
            120, 120
        };

        Vector2 buttonImageSrc = {0, 0};

        if(Mouse::isHovering(slot.object)) {

            Settings::HoveringOverMenu = true;
            buttonImageSrc.x = 1;
        }

        if(Mouse::isClickedL(buttonObject))
            selectedType = (TileType) i;

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
}