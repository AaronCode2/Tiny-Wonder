#pragma once
#include <raylib.h>
#include "../Utils.hpp"
#include "../settings.hpp"
#include <map>
#include <utils.h>

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

static std::map<Item, Vector2> itemSrcPos;

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

struct Element3 {

    Texture2D image = {};
    Rectangle src = {0, 0, (float) image.width, (float) image.height};

    void setFrame(const Vector2 frame) {

        src.width = image.width / frame.x;
        src.height = image.height / frame.y;
    }

    Vector2 setSrcXY(const Vector2 frame) {

        src.x = src.width * frame.x;
        src.y = src.width * frame.y;

        return {src.x, src.y};
    }
};

struct Inventory {

    public:
    
        void update();
        void init();

        Texture2D buttonImage;
        Element3 itemSrcImage;

        bool openInventory;
        Vector2 slotStartingPos;
        bool dragged = false;
    
    private:

        slot slots[6][5];

        static Rectangle draggedItem;
        static Vector2 itemID;

        void draw();

};

struct Slotbar {

    Rectangle object = EMPTY_RECT;
    Color color = Utils::testColor;
};

struct HotBar {

    Element base;
    Slotbar slots[5];
};