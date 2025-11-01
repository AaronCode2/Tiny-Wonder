#include "Game.hpp"

Game::Game(){

    
}

void Game::gameLoop() {

    while(!WindowShouldClose()) {

        BeginDrawing();
        ClearBackground(backgroundColor);
        updateMode();
        updateGame();
        EndDrawing();
    }

    CloseWindow();
}

void Game::updateGame() {

    world.update();
    player.update();
    ui.update();

    std::string fps = std::to_string(GetFPS()) + "FPS";

    DrawText(fps.c_str(), 10, GetScreenHeight() - 40.0f, 40, BLACK);
}

void Game::updateMode(){

    for(int key = 49; key <= 51; key++) {

        if(IsKeyDown(key))
            Settings::gameMode = (GameMode) (key - 49);
    }
}
