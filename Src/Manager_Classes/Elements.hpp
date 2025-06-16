#pragma once
#include <raylib.h>
#include "../Utils.hpp"

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

struct Slot {

    Rectangle object = EMPTY_RECT;
    Color color = Utils::testColor;
};

struct HotBar {

    Element base;
    Slot slots[5];
};