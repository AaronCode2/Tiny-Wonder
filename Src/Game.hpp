#pragma once
#include <raylib.h>
#include "Classes/Sprite.hpp"
#include "Classes/Player.hpp"
#include "WorldManager/World.hpp"

class Game {

    public:

        Game();
        ~Game();

        void run() { gameLoop(); };

    private:

        World world;
        Player player = Player({100, 100, 100, 100}, world.tiles);
    
        void gameLoop();
        void updateGame();
};