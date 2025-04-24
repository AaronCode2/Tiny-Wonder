#pragma once
#include <raylib.h>
#include <iostream>
#include <map>
#include "../Utils.hpp"
#include "../Entity_Classes/Tile.hpp"

#define MAX_SLOTS 5


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

class UI {

    public:

        UI();

        void update();

    private:

        void draw();

        std::map<TileType, Vector2> imageTilesSrcPos;
        std::map<int, Vector2> imageBasesSrcPos;
        Rectangle basesSrc;

        Texture2D basesImage = LoadTexture("../Assets/UI/BackBases.png");
        Texture2D buttonImage = LoadTexture("../Assets/UI/Buttons.png");

        HotBar hotBar;
};