#include "Game.hpp"

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

    std::string fps = std::to_string(GetFPS()) + " FPS";

    DrawText(fps.c_str(), 10, 10, 40, BLACK);
}
