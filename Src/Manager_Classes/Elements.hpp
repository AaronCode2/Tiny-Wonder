#pragma once
#include <raylib.h>
#include "../Utils.hpp"

#define MAX_SLOTS 5

namespace Bases {

    Rectangle getImageSrc(Vector2 srcPos);

    void setImage(const Texture2D &image);

    extern Rectangle imageSrc;  
};

struct Element {

    Rectangle object = {};
    Color color = Utils::testColor;
};

struct Slot {

    Rectangle object = {};
    Color color = Utils::testColor;
};

struct HotBar {

    Element base;
    Slot slots[5];
};