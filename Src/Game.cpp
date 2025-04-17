#include "Game.hpp"

GameMode gameMode = GameMode::BUILD;

void Game::gameLoop() {

    while(!WindowShouldClose()) {

        BeginDrawing();
        ClearBackground(GRAY);
        updateGame();
        updateMode();
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

void Game::updateMode(){

    for(int key = 49; key <= 51; key++) {

        if(IsKeyDown(key))
            gameMode = (GameMode) (key - 49);
    }
}
