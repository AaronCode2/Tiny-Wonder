#pragma once
#include <raylib.h>
#include <iostream>
#include <map>
#include "../Utils.hpp"
#include "Elements.hpp"
#include "../Entity_Classes/Tile.hpp"
#include "../Manager_Classes/TileManager.hpp"
#include "../Settings.hpp"

#define MAX_SLOTS 5

class UI {

    public:

        UI(TileType &selectedType);

        void update();

    private:

        void draw();

        std::map<TileType, Vector2> imageTilesSrcPos;
        std::map<int, Vector2> imageBasesSrcPos;
        Rectangle basesSrc;

        TileType &selectedType;

        Texture2D buttonImage = LoadTexture("../Assets/UI/Buttons.png");

        HotBar hotBar;
};