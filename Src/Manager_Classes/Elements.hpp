#pragma once
#include <raylib.h>
#include "../Utils.hpp"

enum class Item {

    NOTHING = 0,
    PUMPKIN_SEED,
    CARROT_SEED,
    COCA_SEED,
    TOMATO_SEED,
    CHILLEY_SEED,
    PUMPKIN,
    CARROT,
    COCA,
    TOMATO,
    CHILLEY,
}; 

struct slot {

    Item item = Item::NOTHING;
    int amount = 0;
};

struct Inventory {

    
    public:
    
        void update();

        Texture2D buttonImage;
        Texture2D image;
        bool openInventory = true;
        Vector2 slotStartingPos;
    
    private:

        slot slots[8];

        void draw();

};

namespace BasesImage {

    Rectangle getImageSrc(Vector2 srcPos);

    void setImage(const Texture2D &image);

    extern Rectangle imageSrc;  
};

namespace ButtonImage {

    Rectangle getImageSrc(Vector2 srcPos);

    void setImage(const Texture2D &image);

    extern Rectangle imageSrc;  
};

struct Element {

    Rectangle object = EMPTY_RECT;
    Color color = Utils::testColor;
};

struct Element2 {

    Texture2D image = {};
    Rectangle object = EMPTY_RECT;
    Rectangle src = {0, 0, (float) image.width, (float) image.height};

    void draw() {

        DrawTexturePro(
            image, 
            src, object,
            {0, 0}, 0, WHITE
        );
    }

    void setFrame(const Vector2 frame) {

        src.width = image.width / frame.x;
        src.height = image.height / frame.y;
    }

    void setSrcXY(const Vector2 frame) {

        src.x = src.width * frame.x;
        src.y = src.width * frame.y;
    }
};

struct Slotbar {

    Rectangle object = EMPTY_RECT;
    Color color = Utils::testColor;
};

struct HotBar {

    Element base;
    Slotbar slots[5];
};