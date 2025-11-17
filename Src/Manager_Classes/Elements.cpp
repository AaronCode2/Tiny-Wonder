#include "Elements.hpp"


Rectangle BasesImage::getImageSrc(const Vector2 srcPos) {

    imageSrc.x = imageSrc.width * srcPos.x;
    imageSrc.y = imageSrc.height * srcPos.y;

    return imageSrc;
}

void Inventory::update() {

    if(IsKeyPressed(KEY_E)) {

        // ! Fix Hovering

        Settings::HoveringOverMenu = true;
        openInventory = !openInventory;
    }

    if(openInventory)
        draw();
}

void Inventory::draw() {

    DrawRectangleRounded({750, 310, 430, 430}, 0.1f, 1, SAVY_YELLOW);

    for(float y = 0; y < 5; y++) {
        for(float x = 0; x < 5; x++) {

            Rectangle buttonHitBoxRect =     
            {
                (x + 0.25f) * 80 + slotStartingPos.x,
                (y + 0.25f) * 80 + slotStartingPos.y,
                65,
                65
            };

            DrawTexturePro()

            DrawTexturePro(
                buttonImage,
                ButtonImage::getImageSrc({(Mouse::isHovering(buttonHitBoxRect) ? 1.0f : 0.0f), 0}), 
                {
                    x * 80 + slotStartingPos.x,
                    y * 80 + slotStartingPos.y,
                    120, 120,
                },
                {0, 0}, 0, WHITE
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