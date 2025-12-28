#pragma once
#include <raylib.h>
#include <iostream>
#include <map>
#include <cmath>
#include "../Utils.hpp"
#include "Elements.hpp"
#include "../Entity_Classes/Tile.hpp"
#include "../Manager_Classes/TileManager.hpp"
#include "../Entity_Classes/Sprite.hpp"
#include "World.hpp"
#include "../GlobalVars.hpp"

#define MAX_SLOTS 5

class UI {

    public:

        UI(TileType &selectedType);
        ~UI();

        void update();

        Inventory inventory;
        std::array<std::array<Slot, 5>, 6>& getSlotData() { return inventory.slots; }

    private:
    
    void draw();
    
        std::map<TileType, Vector2> imageTilesSrcPos;
        std::map<GameMode, Vector2> gameModeSrc;
        std::map<GameMode, std::string> gameModeStrings;
        std::map<int, Vector2> imageBasesSrcPos;
        
        Rectangle basesSrc;
        Rectangle moneyBase;
        TileType &selectedType;
        
        Texture2D buttonImage = LoadTexture("../Assets/UI/Buttons.png");
        Texture2D mouseImage = LoadTexture("../Assets/UI/Pointer Mouse.png");
        Sprite coin = Sprite(EMPTY_RECT, {12, 1});

        Element2 gameModeLog = {LoadTexture("../Assets/UI/Emoji.png"), {20, 140, 50, 50}};
    
        Element2 playerPhoto = {LoadTexture("../Assets/UI/PlayerPhoto.png"), {20, 20, 100, 100}};
        Element2 playerInfo = {LoadTexture("../Assets/UI/PlayerInfo.png"), {5, 5, 250, 200}};

        HotBar hotBar;
};