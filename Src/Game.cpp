#include "Game.hpp"

Game::Game() {
    
    world.init();
}

Game::~Game() {

    world.writeData();
}

void Game::gameLoop() {

    while(!WindowShouldClose()) {

        BeginDrawing();
        ClearBackground(GRAY);
        updateGame();
        EndDrawing();
    }

    CloseWindow();
}

void Game::updateGame() {

    world.update();
    player.update();
}
