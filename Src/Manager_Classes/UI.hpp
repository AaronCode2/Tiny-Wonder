#pragma once
#include <raylib.h>
#include <iostream>
#include <map>
#include <math.h>
#include "../Utils.hpp"
#include "Elements.hpp"
#include "../Entity_Classes/Tile.hpp"
#include "../Manager_Classes/TileManager.hpp"
#include "../Settings.hpp"

#define MAX_SLOTS 5
#define SAVY_YELLOW (Color) {255, 209, 157, 255}

class UI {

    public:

        UI(TileType &selectedType);
        ~UI();

        void update();

    private:

        void draw();

        std::map<TileType, Vector2> imageTilesSrcPos;
        std::map<GameMode, Vector2> gameModeSrc;
        std::map<GameMode, std::string> gameModeStrings;
        std::map<int, Vector2> imageBasesSrcPos;
        std::map<Item, Vector2> itemSrcPos;

        Rectangle basesSrc;
        TileType &selectedType;

        Texture2D buttonImage = LoadTexture("../Assets/UI/Buttons.png");
        Element2 gameModeLog = {LoadTexture("../Assets/UI/Emoji.png"), {20, 140, 50, 50}};

        Element2 playerPhoto = {LoadTexture("../Assets/UI/PlayerPhoto.png"), {20, 20, 100, 100}};
        Element2 playerInfo = {LoadTexture("../Assets/UI/PlayerInfo.png"), {5, 5, 250, 200}};

        Inventory inventory;
        HotBar hotBar;
};