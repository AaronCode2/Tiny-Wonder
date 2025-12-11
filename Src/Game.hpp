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

        Game();

        void run() { gameLoop(); };

    private:

        Color backgroundColor = {130, 235, 207, 255};

        World world;

        Player player = Player(
            {
                (float) (GetScreenWidth() / 2) - 100, 
                (float) (GetScreenHeight() / 2) - 100, 
                100, 100
            }, 
            world.tileManager.tiles
        );

        UI ui = UI(world.tileManager.selectedType);
        DataIO dataIO = DataIO(world.tileManager.tiles, world.worldPos, player.object, ui.getSlotData());

        
        void gameLoop();
        void updateGame();
        void updateMode();
};