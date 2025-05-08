#pragma once
#include <raylib.h>
#include <iostream>
#include <map>
#include "../Utils.hpp"
#include "Elements.hpp"
#include "../Entity_Classes/Tile.hpp"

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