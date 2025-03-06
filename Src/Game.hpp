#pragma once
#include <raylib.h>
#include "Classes/Sprite.hpp"
#include "Classes/Player.hpp"
#include "WorldManager/World.hpp"

class Game {

    public:

        Game();
        // ~Game();

        void run() { gameLoop(); };

    private:

        Player player = Player({100, 100, 100, 100});

        World world;

        void gameLoop();
        void updateGame();
};