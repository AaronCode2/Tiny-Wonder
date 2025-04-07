#pragma once
#include <raylib.h>
#include "Entity_Classes/Sprite.hpp"
#include "Entity_Classes/Player.hpp"
#include "Manager_Classes/World.hpp"
#include "Manager_Classes/DataIO.hpp"

class Game {

    public:

        void run() { gameLoop(); };

    private:

        World world;
        DataIO dataIO = DataIO(world.tileManager.tiles, world.worldPos);

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
};