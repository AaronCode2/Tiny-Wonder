#include "Game.hpp"

Game::Game() {

    
    Utils::font = LoadFont("../Assets/fonts/Daydreamer.otf");
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

// Resloution: W:1920 H:1009

void Game::updateGame() {

    if(!IsWindowFocused() && !inactive) {

        SetTargetFPS(10);
        inactive = true;
    } else if(IsWindowFocused() && inactive) {

        SetTargetFPS(60);
        inactive = false;
    }

    Utils::deltaTimeIt += GetFrameTime();
    Utils::fontSize = (GetScreenHeight() / 97.63) + (GetScreenWidth() / 97.63);

    world.update();
    player.update();
    ui.update();

    std::string fps = std::to_string(GetFPS()) + "FPS";

    DrawFPS(GetScreenHeight() - 40.0f, 40);
}

void Game::updateMode(){

    for(int key = 49; key <= 51; key++) {

        if(IsKeyDown(key))
            GlobalVars::gameMode = (GameMode) (key - 49);
    }
}
