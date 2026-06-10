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
    iconMenu.setSrcXY({2, 2});
    iconMenu.clickAbleIndicator = true;

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

    gameModeLog.object = {

        GetScreenWidth() / 78.0f,
        GetScreenHeight() / 6.8f,
        50, 50
    };

    gameModeLog.object.y += std::sin(Utils::deltaTimeIt * 7.5) * 25 * GetFrameTime();

    gameModeLog.setSrcXY(gameModeSrc[GlobalVars::gameMode]);

    draw();

    if(IsKeyPressed(KEY_ESCAPE))
        escapKeyPressed = !escapKeyPressed;
    else if(!IsWindowFocused())
        escapKeyPressed = false;

    if(escapKeyPressed)
        drawEscapeMenu();

    
}

int UI::getFpsSelected() {

    return std::stoi(fps_explanation_type);
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

        if(rand == 0) rand = GetRandomValue(10000000, 999999999);

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

        std::string line = "https/dealership.com/LatestDeals!/request?" + std::to_string(rand);

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

        if(Mouse::isClickedOnceL(iconMenu.object)) {

            rand = 0;

            for(auto &dealer : dealers)
                dealer.refresh();
        }

        iconMenu.draw();

        for(int y = 0; y < 3; y++) {
            for(int x = 0; x < 3; x++) {

                int i = y + x;

                Color rectRoundedColor = SAVY_BROWN;

                Rectangle BackBase = {

                    (((x + 1) * 30) + (GetScreenWidth() / 5.5f) * (x + 1)),
                    ((GetScreenHeight() / 4.2f) + (y + 1) * ((GetScreenHeight() / 8.6f) + 30.0f)),   
                    (GetScreenWidth() / 5.48f),
                    (GetScreenHeight() / 8.6f),
                };

                if(Mouse::isHovering(BackBase)) 
                    rectRoundedColor.a = 100;

                DrawRectangleRounded(BackBase, 0.3, 4, rectRoundedColor);

                DrawTextEx(
                    Utils::font, Dealer::dealerNames[dealers[i].iName].c_str(),
                    {
                        (((x + 1) * 30) + (GetScreenWidth() / 5.4f) * (x + 1)),
                        ((GetScreenHeight() / 4.2f) + (y + 1) * ((GetScreenHeight() / 8.5f) + 30.0f)),   
                    },
                    Utils::fontSize, FONT_SPACING, BLACK
                );

// For the dealer giving Stuff (the Dealer gaining money, the player is losing money!)

                if(dealers[i].gettingMoney) {

                    if(Mouse::isClickedOnceL(BackBase)) {

                        PLANTS dealerSelPlant = dealers[i].plantRequired;
                        int dealerSelAmount = dealers[i].itemsToGiveOrNeeded;

                        if(GlobalVars::money < dealers[i].cost)
                            return;

                        for(int i2 = 0; i2 < 5; i2++) {
                            for(int l = 0; l < 5; l++) {

                                if(
                                    (
                                        inventory.slots[i2][l].item == Item::NOTHING || 
                                        inventory.slots[i2][l].item == (Item) (int) dealerSelPlant
                                    ) &&
                                    inventory.slots[i2][l].amount + dealerSelAmount <= STACK_SIZE
                                ) {
                                
                                    inventory.slots[i2][l].amount += dealerSelAmount;
                                    inventory.slots[i2][l].item = (Item) (int) dealerSelPlant;
                                    GlobalVars::money -= dealers[i].cost;

                                    return;
                            }
                        }
                    }           
                }

                    DrawTexturePro(
                        Inventory::itemSrcImage.image,
                        {
                            inventory.itemSrcImage.setSrcXY(itemSrcPos[(Item) (int) dealers[i].plantRequired]).x,
                            inventory.itemSrcImage.setSrcXY(itemSrcPos[(Item) (int) dealers[i].plantRequired]).y,
                            (float) Inventory::itemSrcImage.image.width / 5,
                            (float) Inventory::itemSrcImage.image.height / 3,
                        }, 
                        { 
                            (x * 2 +(GetScreenWidth() / 4.9f) + x * (GetScreenWidth() / 5.1f)), 
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

// For the Player giving Stuff (the player gaining money, the dealer is losing money!)

                } else {

                    if(Mouse::isClickedOnceL(BackBase)) {

                        PLANTS dealerSelPlant = dealers[i].plantRequired;
                        int dealerSelAmount = dealers[i].itemsToGiveOrNeeded;

                            for(int i2 = 0; i2 < 5; i2++) {
                                for(int l = 0; l < 5; l++) {

                                    if(
                                        inventory.slots[i2][l].item == (Item) (5 + (int) dealerSelPlant) &&
                                        inventory.slots[i2][l].amount >= dealerSelAmount
                                    ) {

                                        GlobalVars::money += dealers[i].cost;
                                        inventory.slots[i2][l].amount -= dealerSelAmount;
                                        return;
                                    }
                            }
                        }           
                    }

                    DrawTexturePro(
                        coin.image,
                        coin.getSrcRect(),
                        { 
                            (x * 3.0f + (GetScreenWidth() / 4.9f) + x * (GetScreenWidth() / 5.1f)), 
                            ((GetScreenHeight() / 2.35f) + y * ((GetScreenHeight() / 6.6f))), 
                            (GetScreenWidth() / 40.0f),  
                            (GetScreenHeight() / 20.0f) 
                        }, 
                        {0, 0}, 0, WHITE
                    );

                    DrawTextEx(
                        Utils::font,
                        ("x" + std::to_string(dealers[i].cost) + " for").c_str(),
                        {
                            (x * 2 + (GetScreenWidth() / 4.3f) + x * (GetScreenWidth() / 5.1f)), 
                            ((GetScreenHeight() / 2.28f) + y * ((GetScreenHeight() / 6.6f)))
                        },
                        Utils::fontSize, FONT_SPACING, BLACK
                    );


                    DrawTexturePro(
                        Inventory::itemSrcImage.image,
                        {
                            inventory.itemSrcImage.setSrcXY(itemSrcPos[(Item) ((int) 5 + (int) dealers[i].plantRequired)]).x,
                            inventory.itemSrcImage.setSrcXY(itemSrcPos[(Item) ((int) 5 + (int) dealers[i].plantRequired)]).y,
                            (float) Inventory::itemSrcImage.image.width / 5,
                            (float) Inventory::itemSrcImage.image.height / 3,
                        },
                        { 
                            (x * 3.2f + (GetScreenWidth() / 3.28f) + x * (GetScreenWidth() / 5.1f)), 
                            ((GetScreenHeight() / 2.35f) + y * ((GetScreenHeight() / 6.6f))), 
                            (GetScreenWidth() / 40.0f),  
                            (GetScreenHeight() / 20.0f) 
                        }, 
                        {0, 0}, 0, WHITE
                    );
                    
                    DrawTextEx(
                        Utils::font,
                        ("x" + std::to_string(dealers[i].itemsToGiveOrNeeded)).c_str(),
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

        hotBar.slots[i] = {
            {
                ((GetScreenWidth() / 2) - (450.0f / 2) + 30) + (i * 80.0f), 
                GetScreenHeight() - 110.0f, 
                70, 70
            },
        };

        Slotbar slot = hotBar.slots[i];
        Rectangle imageSrcRect = {

            (Tile::image.width / 9) * imageTilesSrcPos[(TileType) i].x,
            (Tile::image.height / 19) * imageTilesSrcPos[(TileType) i].y,
            (Tile::image.width / 9.0f), 
            (Tile::image.height / 19.0f)
        };

// the - 25 is to prevent the texture from going offset

        Rectangle buttonObject = {

            ((GetScreenWidth() / 2) - (450.0f / 2) + 30) + (i * 80.0f) - 25, 
            GetScreenHeight() - 110.0f - 25, 
            SLOT_SIZE, SLOT_SIZE
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

void UI::drawEscapeMenu() {

    DrawRectangleRounded(
        {
            ((GetScreenWidth() / 2) - (450.0f / 2) + 30) + (1 * 80.0f) - 98,
            (GetScreenHeight() / 3.5f),
            (GetScreenWidth() / 4.6f),
            (GetScreenHeight() / 2.1f),
        }, 0.1, 8, SAVY_BROWN);
    
    Vector2 ExitbuttonSrc = {0, 1};

    Rectangle fpsButtonObject = {

        ((GetScreenWidth() / 2) - (403.0f / 2) + 30) + (1 * 80.0f) - 98,
        (GetScreenHeight() / 2.5f),
        (GetScreenWidth() / 5.2f),
        (GetScreenHeight() / 11.0f),
    };

    Rectangle saveAndExitObject = {

        ((GetScreenWidth() / 2) - (403.0f / 2) + 30) + (1 * 80.0f) - 98,
        (GetScreenHeight() / 1.56f),
        (GetScreenWidth() / 5.2f),
        (GetScreenHeight() / 11.0f),
    };
    

    Rectangle tutorialObject = {

        ((GetScreenWidth() / 2) - (403.0f / 2) + 30) + (1 * 80.0f) - 98,
        (GetScreenHeight() / 1.92f),
        (GetScreenWidth() / 5.2f),
        (GetScreenHeight() / 11.0f),
    };

    Color fpsColor = SAVY_YELLOW;
    Color saveAndExitColor = SAVY_YELLOW;
    Color tutorialColor = SAVY_YELLOW;

    if(Mouse::isHovering(fpsButtonObject))
        fpsColor.a = 200;
    
    if(Mouse::isHovering(saveAndExitObject))
        saveAndExitColor.a = 200;

    
    if(Mouse::isHovering(tutorialObject))
        tutorialColor.a = 200;

    if(Mouse::isClickedL(tutorialObject))
        OpenURL("https://exmaple.com/");

    if(Mouse::isClickedL(saveAndExitObject))
        GlobalVars::saveAndExit = true;

    DrawRectangleRounded(
        fpsButtonObject,
        0.3, 4, fpsColor
    );

    DrawRectangleRounded(
        saveAndExitObject,
        0.3, 4, saveAndExitColor
    );  

    DrawRectangleRounded(
        tutorialObject,
        0.3, 4, tutorialColor
    );  

    if(Mouse::isClickedOnceL(fpsButtonObject)) {

        if(fpsType != FPS_TYPE::MAXFPS)
            fpsType = (FPS_TYPE) (1 + (int) fpsType);
        else fpsType = FPS_TYPE::THIRTY_FPS;

        switch(fpsType) {

            case FPS_TYPE::THIRTY_FPS:

                SetTargetFPS(30);
                fps_explanation_type = "30";
                break;
                
            case FPS_TYPE::SIXTY_FPS:

                SetTargetFPS(60);
                fps_explanation_type = "60";
                break;


            case FPS_TYPE::HUNDRED_AND_TWENTY_FPS:

                SetTargetFPS(120);
                fps_explanation_type = "120";
                break;


            case FPS_TYPE::MAXFPS:

                SetTargetFPS(0xfffff); // hex for max
                fps_explanation_type = "MAXIUM";
                break;

        }
    }
    
    DrawTextEx(
        Utils::font,  ("FPS: " + fps_explanation_type).c_str(), 
        {(GetScreenWidth() / 2.18f), (GetScreenHeight() / 2.3f)}, Utils::fontSize + 10, FONT_SPACING, BLACK
    );

    DrawTextEx(
        Utils::font,  "Menu", 
        {(GetScreenWidth() / 2.16f), (GetScreenHeight() / 3.1f)}, Utils::fontSize + 15, FONT_SPACING, BLACK
    );

    DrawTextEx(
        Utils::font,  "Tutorial", 
        {(GetScreenWidth() / 2.26f), (GetScreenHeight() / 1.82f)}, Utils::fontSize + 10, FONT_SPACING, BLACK
    );

    DrawTextEx(
        Utils::font,  "Save 'n' Exit", 
        {(GetScreenWidth() / 2.34f), (GetScreenHeight() / 1.50f)}, Utils::fontSize + 10, FONT_SPACING, BLACK
    );

}