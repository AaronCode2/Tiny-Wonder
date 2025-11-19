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
    openInventory = true;
    itemSrcImage.image = LoadTexture("../Assets/Items/Items.png");
    itemSrcImage.setFrame({5, 3});

    for(auto &slot : slots) {

        slot.amount = 1;
        slot.item = Item::CHILLEY;
    } 
}

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


        DrawTexturePro(
            buttonImage,
            ButtonImage::getImageSrc({(mouseHover ? 1.0f : 0.0f), 0}), 
            buttonRect,
            {0, 0}, 0, WHITE
        );

        if(slots[(int) (10 + i)].amount == 0)
            continue;

        DrawTexturePro(
            itemSrcImage.image,
            {
                itemSrcImage.setSrcXY(itemSrcPos[slots[(int) (i)].item]).x,
                itemSrcImage.setSrcXY(itemSrcPos[slots[(int) (i)].item]).y,
                (float) itemSrcImage.image.width / 5,
                (float) itemSrcImage.image.height / 3,
            },
            itemRect,
            {0, 0}, 0, mouseHover ? (Color) {255, 255, 255, 200} : WHITE
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
            
            DrawTexturePro(

                buttonImage,
                ButtonImage::getImageSrc({(mouseHover ? 1.0f : 0.0f), 0}), 
                buttonRect,
                {0, 0}, 0, WHITE
            );

            if(slots[(int) (x + y)].amount == 0)
                continue;

            DrawTexturePro(
                itemSrcImage.image,
                {
                    itemSrcImage.setSrcXY(itemSrcPos[slots[(int) (x + y)].item]).x,
                    itemSrcImage.setSrcXY(itemSrcPos[slots[(int) (x + y)].item]).y,
                    (float) itemSrcImage.image.width / 5,
                    (float) itemSrcImage.image.height / 3,
                },
                itemRect,
                {0, 0}, 0, mouseHover ? (Color) {255, 255, 255, 200} : WHITE
            );
        }
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