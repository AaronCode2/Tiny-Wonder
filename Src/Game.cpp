#include "Game.hpp"

Game::Game(){

    
}

void Game::gameLoop() {

    SetTargetFPS(60);

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

    Utils::deltaTimeIt += GetFrameTime();

    world.update();
    player.update();
    ui.update();

    std::string fps = std::to_string(GetFPS()) + "FPS";

    DrawFPS(GetScreenHeight() - 40.0f, 40);
}

void Game::updateMode(){

    for(int key = 49; key <= 51; key++) {

        if(IsKeyDown(key))
            Settings::gameMode = (GameMode) (key - 49);
    }
}
