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

    itemSrcPos[Item::NOTHING] = {3, 2};
    
    itemSrcPos[Item::PUMPKIN_SEED] = {0, 1};
    itemSrcPos[Item::CARROT_SEED] = {2, 1};
    itemSrcPos[Item::COCA_SEED] = {1, 1};
    itemSrcPos[Item::TOMATO_SEED] = {3, 1};
    itemSrcPos[Item::CHILLEY_SEED] = {4, 1};
    
    itemSrcPos[Item::PUMPKIN] = {0, 0};
    itemSrcPos[Item::CARROT] = {2, 0};
    itemSrcPos[Item::COCA] = {1, 0};
    itemSrcPos[Item::TOMATO] = {3, 0};
    itemSrcPos[Item::CHILLEY] = {4, 0};

    gameModeLog.setFrame({5, 19});

    hotBar.base.color = {130, 130, 130, 230};

    iconMenu.setFrame({3, 3});

    ButtonImage::setImage(buttonImage);

    inventory.buttonImage = buttonImage;
    inventory.selectedHotBarItem = {

        (float) GetScreenWidth(),
        (float) GetScreenHeight(),
        10, 10
    };
    inventory.init();
    inventory.itemSrcImage.setFrame({5, 3});

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

#if !__linux__

    UnloadTexture(buttonImage);
    
    UnloadTexture(inventory.buttonImage);
    UnloadTexture(inventory.itemSrcImage.image);
    UnloadTexture(playerPhoto.image);
    UnloadTexture(playerInfo.image);
    UnloadTexture(Sprite::image);

#endif
}

void UI::update() {

    hotBar.base.object = {

        (GetScreenWidth() / 2) - (410.0f / 2),
        GetScreenHeight() - 120.0f,
        410,
        90, 
    };

    gameModeLog.object.y += std::sin(Utils::deltaTimeIt * 7.5) * 25 * GetFrameTime();

    gameModeLog.setSrcXY(gameModeSrc[GlobalVars::gameMode]);

    draw();
    DrawTextureV(mouseImage, GetMousePosition(), MOUSE_BROWN);
}

void UI::draw() {

    DrawRectangleRec({20, 20, 100, 90}, SAVY_YELLOW);
    playerPhoto.draw();
    playerInfo.draw();

    DrawTextEx(
        Utils::font, gameModeStrings[GlobalVars::gameMode].c_str(), 
        {75, 154}, Utils::fontSize, 
        FONT_SPACING, BLACK
    );

    gameModeLog.draw();

    if(GlobalVars::gameMode != GameMode::TRADE)
        DrawRectangleRounded(hotBar.base.object, 0.2, 4, SAVY_YELLOW);
    
    GlobalVars::HoveringOverMenu = false; 

    inventory.update();

    coin.object = {
        GetScreenWidth() - 190.0f,
        20,
        60,
        60
    };

    DrawRectangleRounded(
        {
            GetScreenWidth() - 185.0f,
            10,
            165,
            80
        }, 
        0.2, 4, SAVY_YELLOW
    );

    coin.update();

    DrawTextEx(
        Utils::font, Utils::formatZeros(GlobalVars::money, 5).c_str(),
        {GetScreenWidth() - 140.0f, 40}, Utils::fontSize, FONT_SPACING, BLACK 
    );

#define Adjust_selwh 28.0f
#define Adjust_selxy 15.0F



    if(GlobalVars::gameMode == GameMode::EXPLORE) {
        
        rand = 0;

        Rectangle selectorObject = {

            (inventory.selectedHotBarItem.x + Adjust_selxy) - sin(Utils::deltaTimeIt * 7.5f) * 1.5f,
            (inventory.selectedHotBarItem.y + Adjust_selxy) - sin(Utils::deltaTimeIt * 7.5f) * 1.5f,
            (inventory.selectedHotBarItem.width - Adjust_selwh) + sin(Utils::deltaTimeIt * 7.6f) * 1.5f,
            (inventory.selectedHotBarItem.height - Adjust_selwh) + sin(Utils::deltaTimeIt * 7.6f) * 1.5f
        };

        DrawTexturePro(
            World::selectorImage,
            {0, 0, (float) World::selectorImage.width, (float) World::selectorImage.height},
            selectorObject, {0, 0}, 0, WHITE
        );
        return;
    } else if(GlobalVars::gameMode == GameMode::TRADE) {

        if(rand == 0) rand = GetRandomValue(100000000, 999999999);

        DrawRectangleRounded(
            {
                (GetScreenWidth() / 8.0f),
                (GetScreenHeight() / 5.1f),
                (GetScreenWidth() / 1.35f),
                (GetScreenHeight() / 1.45f),
            }, 
            0.09f, 6, SAVY_YELLOW
        );

        DrawRectangleRounded(
            {
                (GetScreenWidth() / 5.5f),
                (GetScreenHeight() / 4.5f),
                (GetScreenWidth() / 1.48f),
                (GetScreenHeight() / 15.0f),
            },
            0.3, 4, SAVY_BROWN
        );

        // Can't use ':' or '=' as the Font doesn't include them

        std::string line = "https/dealership.com/LatestDeals/request?" + std::to_string(rand);

        DrawTextEx(
            Utils::font, line.c_str(),
            {
                (GetScreenWidth() / 5.4f),
                (GetScreenHeight() / 4.1f)
            },
            Utils::fontSize, FONT_SPACING,
            DARK_BROWN
        );

        iconMenu.object = {

            (GetScreenWidth() / 7.3f),
            (GetScreenHeight() / 4.5f),
            (GetScreenWidth() / 25.0f),
            (GetScreenHeight() / 15.0f)
        };
        
        iconMenu.setSrcXY({2, 2});
        iconMenu.draw();

        for(int y = 0; y < 3; y++) {
            for(int x = 0; x < 3; x++) {

                int i = y + x;

                DrawRectangleRounded(
                    {
                        (((x + 1) * 30) + (GetScreenWidth() / 5.5f) * (x + 1)),
                        ((GetScreenHeight() / 4.2f) + (y + 1) * ((GetScreenHeight() / 8.6f) + 30.0f)),   
                        (GetScreenWidth() / 5.48f),
                        (GetScreenHeight() / 8.6f),
                    },
                    0.3, 4, SAVY_BROWN
                );

                DrawTextEx(
                    Utils::font, Dealer::dealerNames[dealers[i].iName].c_str(),
                    {
                        (((x + 1) * 30) + (GetScreenWidth() / 5.4f) * (x + 1)),
                        ((GetScreenHeight() / 4.2f) + (y + 1) * ((GetScreenHeight() / 8.5f) + 30.0f)),   
                    },
                    Utils::fontSize, FONT_SPACING, BLACK
                );

// For the required Stuff

                if(dealers[i].gettingMoney) {

                    DrawTexturePro(
                        Inventory::itemSrcImage.image,
                        {
                            inventory.itemSrcImage.setSrcXY(itemSrcPos[(Item) (int) dealers[i].plantRequired]).x,
                            inventory.itemSrcImage.setSrcXY(itemSrcPos[(Item) (int) dealers[i].plantRequired]).y,
                            (float) Inventory::itemSrcImage.image.width / 5,
                            (float) Inventory::itemSrcImage.image.height / 3,
                        }, 
                        { 
                            ((GetScreenWidth() / 4.9f) + x * (GetScreenWidth() / 5.1f)), 
                            ((GetScreenHeight() / 2.35f) + y * ((GetScreenHeight() / 6.6f))), 
                            (GetScreenWidth() / 40.0f),  
                            (GetScreenHeight() / 20.0f) 
                        }, 
                        {0, 0}, 0, WHITE
                    );

                    DrawTextEx(
                        Utils::font,
                        ("x" + std::to_string(dealers[i].itemsToGiveOrNeeded) + " for").c_str(),
                        {
                            ((GetScreenWidth() / 4.3f) + x * (GetScreenWidth() / 5.1f)), 
                            ((GetScreenHeight() / 2.28f) + y * ((GetScreenHeight() / 6.6f)))
                        },
                        Utils::fontSize, FONT_SPACING, BLACK
                    );

    // The giveaway stuff
        
                    DrawTexturePro(
                        Sprite::image,
                        coin.getSrcRect(), 
                        { 
                            ((GetScreenWidth() / 3.28f) + x * (GetScreenWidth() / 5.1f)), 
                            ((GetScreenHeight() / 2.35f) + y * ((GetScreenHeight() / 6.6f))), 
                            (GetScreenWidth() / 40.0f),  
                            (GetScreenHeight() / 20.0f) 
                        }, 
                        {0, 0}, 0, WHITE
                    );
                    
                    DrawTextEx(
                        Utils::font,
                        ("x" + std::to_string(dealers[i].cost)).c_str(),
                        {
                            ((GetScreenWidth() / 3.0f) + x * (GetScreenWidth() / 5.1f)), 
                            ((GetScreenHeight() / 2.28f) + y * ((GetScreenHeight() / 6.6f)))
                        },
                        Utils::fontSize, FONT_SPACING, BLACK
                    );
                } else {

                    DrawTexturePro(
                        coin.image,
                        coin.getSrcRect(),
                        { 
                            ((GetScreenWidth() / 4.9f) + x * (GetScreenWidth() / 5.1f)), 
                            ((GetScreenHeight() / 2.35f) + y * ((GetScreenHeight() / 6.6f))), 
                            (GetScreenWidth() / 40.0f),  
                            (GetScreenHeight() / 20.0f) 
                        }, 
                        {0, 0}, 0, WHITE
                    );

                    DrawTextEx(
                        Utils::font,
                        ("x" + std::to_string(dealers[i].itemsToGiveOrNeeded) + " for").c_str(),
                        {
                            ((GetScreenWidth() / 4.3f) + x * (GetScreenWidth() / 5.1f)), 
                            ((GetScreenHeight() / 2.28f) + y * ((GetScreenHeight() / 6.6f)))
                        },
                        Utils::fontSize, FONT_SPACING, BLACK
                    );

    // The giveaway stuff
        
                    DrawTexturePro(
                        Inventory::itemSrcImage.image,
                        {
                            inventory.itemSrcImage.setSrcXY(itemSrcPos[(Item) ((int) 5 + (int) dealers[i].plantRequired)]).x,
                            inventory.itemSrcImage.setSrcXY(itemSrcPos[(Item) ((int) 5 + (int) dealers[i].plantRequired)]).y,
                            (float) Inventory::itemSrcImage.image.width / 5,
                            (float) Inventory::itemSrcImage.image.height / 3,
                        },
                        { 
                            ((GetScreenWidth() / 3.28f) + x * (GetScreenWidth() / 5.1f)), 
                            ((GetScreenHeight() / 2.35f) + y * ((GetScreenHeight() / 6.6f))), 
                            (GetScreenWidth() / 40.0f),  
                            (GetScreenHeight() / 20.0f) 
                        }, 
                        {0, 0}, 0, WHITE
                    );
                    
                    DrawTextEx(
                        Utils::font,
                        ("x" + std::to_string(dealers[i].cost)).c_str(),
                        {
                            ((GetScreenWidth() / 3.0f) + x * (GetScreenWidth() / 5.1f)), 
                            ((GetScreenHeight() / 2.28f) + y * ((GetScreenHeight() / 6.6f)))
                        },
                        Utils::fontSize, FONT_SPACING, BLACK
                    );
                }
            }   
        }

        return;
    }

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

            GlobalVars::HoveringOverMenu = true;
            buttonImageSrc.x = 1;
        }

        if(Mouse::isClickedL(buttonObject))
            selectedType = (TileType) i;

        if(i == (int) selectedType) {

            Rectangle selectorObject = {

                (buttonObject.x + Adjust_selxy) - sin(Utils::deltaTimeIt * 7.5f) * 1.5f,
                (buttonObject.y + Adjust_selxy) - sin(Utils::deltaTimeIt * 7.5f) * 1.5f,
                (buttonObject.width - Adjust_selwh) + sin(Utils::deltaTimeIt * 7.6f) * 1.5f,
                (buttonObject.height - Adjust_selwh) + sin(Utils::deltaTimeIt * 7.6f) * 1.5f
            };

            DrawTexturePro(
                World::selectorImage,
                {0, 0, (float) World::selectorImage.width, (float) World::selectorImage.height},
                selectorObject, {0, 0}, 0, WHITE
            );
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
}