#pragma once
#include <raylib.h>
#include "Entity_Classes/Sprite.hpp"
#include "Entity_Classes/Player.hpp"
#include "World_Manager/World.hpp"

class Game {

    public:

        Game();
        ~Game();

        void run() { gameLoop(); };

    private:

        World world;
        Player player = Player(
            {
                (float) (GetScreenWidth() / 2) - 100, 
                (float) (GetScreenHeight() / 2) - 100, 
                100, 100
            }, 
            world.tiles
        );
    
        void gameLoop();
        void updateGame();
};