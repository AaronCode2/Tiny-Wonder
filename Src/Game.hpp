#pragma once
#include <raylib.h>
#include "Entity_Classes/Sprite.hpp"
#include "Entity_Classes/Player.hpp"
#include "Manager_Classes/UI.hpp"
#include "Manager_Classes/World.hpp"
#include "Manager_Classes/DataIO.hpp"
#include "Settings.hpp"

class Game {

    public:

        void run() { gameLoop(); };

    private:

        Color backgroundColor = {130, 235, 207, 255};

        World world;
        DataIO dataIO = DataIO(world.tileManager.tiles, world.worldPos);
        UI ui = UI(world.tileManager.selectedType);
        
        Player player = Player(
            {
                (float) (GetScreenWidth() / 2) - 100, 
                (float) (GetScreenHeight() / 2) - 100, 
                100, 100
            }, 
            world.tileManager.tiles
        );

        
        void gameLoop();
        void updateGame();
        void updateMode();
};