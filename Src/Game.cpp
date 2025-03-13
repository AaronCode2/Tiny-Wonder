#include "Game.hpp"

Game::Game() {
    
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

    world.update(player.getVeclocity());
    player.update();

    std::string fps = std::to_string(GetFPS()) + "FPS";

    DrawText(fps.c_str(), 10, 10, 40, BLACK);
}
