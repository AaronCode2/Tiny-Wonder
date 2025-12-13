#include "Elements.hpp"


Rectangle BasesImage::getImageSrc(const Vector2 srcPos) {

    imageSrc.x = imageSrc.width * srcPos.x;
    imageSrc.y = imageSrc.height * srcPos.y;

    return imageSrc;
}

void Inventory::update() {

    if(Settings::gameMode == GameMode::EXPLORE) {
        draw();

        if(IsKeyPressed(KEY_E)) {

            Settings::HoveringOverMenu = true;
            openInventory = !openInventory;
        }

    } else openInventory = false;
}

void Inventory::init() {

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

    slotStartingPos = {740, 300};
    openInventory = false;
    itemSrcImage.image = LoadTexture("../Assets/Items/Items.png");
    itemSrcImage.setFrame({5, 3});

    // bool __ast = false;

    // if(__ast) {
    //     for(int y = 0; y < 5; y++) {
    //         for(int x = 0; x < 5; x++) {

    //             slots[y][x].item = (Item) GetRandomValue(1, 10);
    //             slots[y][x].amount = GetRandomValue(1, 10);
    //         }
    //     }
    // }
}

Rectangle Inventory::draggedItem = EMPTY_RECT;
Vector2 Inventory::itemID = {-1, -1};

void Inventory::draw() {

    // Hotbar

    for(float i = 0; i < 5; i++) {

        Rectangle buttonHitBoxRect = {

            (i + 0.35f) * 80 + slotStartingPos.x,
            900,
            65,
            65
        };

        Rectangle buttonRect = {

            i * 80 + slotStartingPos.x,
            874,
            120, 120,
        };

        const bool mouseHover = Mouse::isHovering(buttonHitBoxRect);

        Rectangle itemRect;

        if(!mouseHover) {

            itemRect = {

                i * 80 + slotStartingPos.x + 28,
                902,
                60, 60,
            };
        } else {

            itemRect = {

                i * 80 + slotStartingPos.x + 30,
                904,
                58, 58,
            };
        }

        Vector2 textPos = {

            i * 80 + slotStartingPos.x + 30,
            940
        };

        if(
            Mouse::isClickedL(itemRect) && Utils::isSameXY(itemID, {-1, -1}) 
            && slots[5][(int) i].item != Item::NOTHING && openInventory
        ) {

            itemID = {i, 5};
            draggedItem = itemRect;
        }  else if(
                Mouse::isClickedOnceR(itemRect) && slots[5][(int) i].amount > 1
        ) {

            int half = slots[5][(int) i].amount / 2;
            bool stop = false;
            for(int y2 = 0; y2 < 6; y2++) {
                for(int x2 = 0; x2 < 5; x2++) {

                    if(slots[y2][x2].item == Item::NOTHING && stop == false) {

                        slots[5][(int) i].amount -= half;
                        slots[y2][x2].amount += half;
                        slots[y2][x2].item = slots[5][(int) i].item;
                        stop = true;
                        break;
                    }
                }
            }
        }

        DrawTexturePro(
            buttonImage,
            ButtonImage::getImageSrc({(mouseHover ? 1.0f : 0.0f), 0}), 
            buttonRect,
            {0, 0}, 0, WHITE
        );

        if(slots[5][(int) i].item == Item::NOTHING || Utils::isSameXY(itemID, {i, 5}))
            continue;

        DrawTexturePro(
            itemSrcImage.image,
            {
                itemSrcImage.setSrcXY(itemSrcPos[slots[5][(int) i].item]).x,
                itemSrcImage.setSrcXY(itemSrcPos[slots[5][(int) i].item]).y,
                (float) itemSrcImage.image.width / 5,
                (float) itemSrcImage.image.height / 3,
            },
            itemRect,
            {0, 0}, 0, mouseHover ? (Color) {255, 255, 255, 200} : WHITE
        );

        DrawTextEx(
            Utils::font, 
            ('x' + std::to_string(slots[5][(int) i].amount)).c_str(), 
            textPos, FONT_SIZE,
            FONT_SPACING,
            BLACK 
        );
    }

    // Inventory

    if(!openInventory)
        return;

    DrawRectangleRounded({750, 310, 430, 430}, 0.1f, 1, SAVY_YELLOW);

    for(float y = 0; y < 5; y++) {
        for(float x = 0; x < 5; x++) {

            Rectangle buttonHitBoxRect = {

                (x + 0.25f) * 80 + slotStartingPos.x,
                (y + 0.25f) * 80 + slotStartingPos.y,
                65,
                65
            };

            Rectangle buttonRect = {

                x * 80 + slotStartingPos.x,
                y * 80 + slotStartingPos.y,
                120, 120,
            };

            const bool mouseHover = Mouse::isHovering(buttonHitBoxRect);

            Rectangle itemRect;

            if(!mouseHover) {

                itemRect = {

                    x * 80 + slotStartingPos.x + 28,
                    y * 80 + slotStartingPos.y + 28,
                    60, 60,
                };
            } else {

                itemRect = {

                    x * 80 + slotStartingPos.x + 30,
                    y * 80 + slotStartingPos.y + 30,
                    58, 58,
                };
            }
            
            if(
                Mouse::isClickedL(itemRect) && Utils::isSameXY(itemID, {-1, -1}) 
                && slots[(int) y][(int) x].item != Item::NOTHING
            ) {

                itemID = {x, y};
                draggedItem = itemRect;
            } else if(
                Mouse::isClickedOnceR(itemRect) && slots[(int) y][(int) x].amount > 1
            ) {

                int half = slots[(int) y][(int) x].amount / 2;
                bool stop = false;

                for(int y2 = 0; y2 < 6; y2++) {
                    for(int x2 = 0; x2 < 5; x2++) {

                        if(slots[y2][x2].item == Item::NOTHING && stop == false) {

                            slots[(int) y][(int) x].amount -= half; 
                            slots[y2][x2].amount += half;
                            slots[y2][x2].item = slots[(int) y][(int) x].item;
                            stop = true;
                            break;
                        }
                    }
                }
            }

            

            DrawTexturePro(

                buttonImage,
                ButtonImage::getImageSrc({(mouseHover ? 1.0f : 0.0f), 0}), 
                buttonRect,
                {0, 0}, 0, WHITE
            );

            if(slots[(int) y][(int) x].item == Item::NOTHING || Utils::isSameXY(itemID, {x, y}))
                continue;
            
            Vector2 textPos = {

                x * 80 + slotStartingPos.x + 30,
                y * 80 + slotStartingPos.y + 60
            };

            DrawTexturePro(
                itemSrcImage.image,
                {
                    itemSrcImage.setSrcXY(itemSrcPos[slots[(int) y][(int) x].item]).x,
                    itemSrcImage.setSrcXY(itemSrcPos[slots[(int) y][(int) x].item]).y,
                    (float) itemSrcImage.image.width / 5,
                    (float) itemSrcImage.image.height / 3,
                },
                itemRect,
                {0, 0}, 0, mouseHover ? (Color) {255, 255, 255, 200} : WHITE
            );

            DrawTextEx(
                Utils::font, 
                ('x' + std::to_string(slots[(int) y][(int) x].amount)).c_str(), 
                textPos, FONT_SIZE,
                FONT_SPACING,
                BLACK 
            );

        }
    }

    if(Utils::isSameXY(itemID, {-1, -1})) 
        return;

    if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {

        const int offset = 30;

        draggedItem.x = GetMouseX() - offset;
        draggedItem.y = GetMouseY() - offset;

        Vector2 textPos = {
            draggedItem.x,
            draggedItem.y + 30
        };

        DrawTexturePro(
            itemSrcImage.image,
            {
                itemSrcImage.setSrcXY(itemSrcPos[slots[(int) itemID.y][(int) itemID.x].item]).x,
                itemSrcImage.setSrcXY(itemSrcPos[slots[(int) itemID.y][(int) itemID.x].item]).y,
                (float) itemSrcImage.image.width / 5,
                (float) itemSrcImage.image.height / 3,
            },
            draggedItem,
            {0, 0}, 0, (Color) {255, 255, 255, 200}
        );

        DrawTextEx(
            Utils::font, 
            ('x' + std::to_string(slots[(int) itemID.y][(int) itemID.x].amount)).c_str(), 
            textPos, FONT_SIZE,
            FONT_SPACING,
            BLACK 
        );

    } else {

        for(float y = 0; y < 6; y++) {
            for(float x = 0; x < 5; x++) {

                Rectangle buttonHitBoxRect;

                if(y != 5) {

                    buttonHitBoxRect = {

                        (x + 0.25f) * 80 + slotStartingPos.x,
                        (y + 0.25f) * 80 + slotStartingPos.y,
                        65,
                        65
                    };
                } else {

                    buttonHitBoxRect = {

                        (x + 0.35f) * 80 + slotStartingPos.x,
                        900,
                        65,
                        65
                    };
                }

                if(!CheckCollisionPointRec(GetMousePosition(), buttonHitBoxRect) || Utils::isSameXY({x, y}, itemID))
                    continue;

                if(slots[(int) y][(int) x].item == slots[(int) itemID.y][(int) itemID.x].item) {
                    
                    slots[(int) y][(int) x].amount += slots[(int) itemID.y][(int) itemID.x].amount;

                    slots[(int) itemID.y][(int) itemID.x].item = Item::NOTHING;
                    slots[(int) itemID.y][(int) itemID.x].amount = 0;

                    break;
                } else std::swap(slots[(int) y][(int) x], slots[(int) itemID.y][(int) itemID.x]);       
            }
        }
        
        draggedItem = EMPTY_RECT;
        itemID = {-1, -1};
    }
}

void BasesImage::setImage(const Texture2D &image) {

    imageSrc.width = (image.width / 2.0f);
    imageSrc.height = (image.height / 3.0f);
}

Rectangle BasesImage::imageSrc;

Rectangle ButtonImage::getImageSrc(const Vector2 srcPos) {

    imageSrc.x = imageSrc.width * srcPos.x;
    imageSrc.y = imageSrc.height * srcPos.y;

    return imageSrc;
}

void ButtonImage::setImage(const Texture2D &image) {

    imageSrc.width = (image.width / 3.0f);
    imageSrc.height = (image.height / 3.0f);
}

Rectangle ButtonImage::imageSrc;