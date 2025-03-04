#include "Game.hpp"

Game::Game() {
    

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

    player.update();
}
