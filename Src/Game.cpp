#include "Game.hpp"

Game::Game() {

    Utils::font = LoadFont("../Assets/fonts/Daydreamer.otf");
    PlayMusicStream(music);
    SetExitKey(KEY_NULL);
}

void Game::gameLoop() {

    SetTargetFPS(60);

    while(!WindowShouldClose()) {

        if(GlobalVars::saveAndExit)
            break;

        BeginDrawing();

            ClearBackground(clearer);

            if(!startGame)
                startMenu();
            else {    
                updateMode();
                updateGame();
            }

            DrawTextureV(mouseImage, GetMousePosition(), MOUSE_BROWN);

        EndDrawing();
    }

    CloseWindow();
}

void Game::startMenu() {

    UpdateMusicStream(music);

    DrawTexture(
        startScreenImage, 
        (GetScreenWidth() /  5.559998f), (GetScreenHeight() / 9.340026f), WHITE
    );

    Color playButtonColor = WHITE;

    Vector2 playButtonObject = {

        ((GetScreenWidth() / 2.080001f) - (403.0f / 2) + 30) + (1 * 80.0f) - 98,
        (GetScreenHeight() / 1.440002f),
    };

    const Rectangle playButtonSrc = {

        0, 0,
        (float) playButtonImage.width,
        (float) playButtonImage.height,
    };

    const Rectangle mouseCheckerRectButtonPlay = {

        playButtonObject.x,
        playButtonObject.y,
        playButtonSrc.width,
        playButtonSrc.height,
    };

    if(Mouse::isHovering(mouseCheckerRectButtonPlay))
        playButtonColor.a = 200;
    
    if(Mouse::isClickedOnceL(mouseCheckerRectButtonPlay))
        startGame = true;

    DrawTextureRec(
        playButtonImage, 
        playButtonSrc,
        playButtonObject, 
        playButtonColor
    );
}

// Resloution: W:1920 H:1009, For my window, it could be different for anyone, Resize is a bit choppy ¬_¬ 

void Game::updateGame() {

    if(!IsWindowFocused() && !inactive) {

        SetTargetFPS(30);
        inactive = true;

    } else if(IsWindowFocused() && inactive) {

        SetTargetFPS(ui.getFpsSelected());
        inactive = false;
    }

    UpdateMusicStream(music);
    Utils::deltaTimeIt += GetFrameTime();
    Utils::fontSize = (GetScreenHeight() / 97.63) + (GetScreenWidth() / 97.63);

    world.update();
    player.update();
    ui.update();

// Saves the game for 2 mins each time

    if(GetTime() - dataSaverTimer >= 120) {

        dataIO.saveData();
        dataSaverTimer = GetTime();

#if DEBUG_ENABLED    
        print("Saving!!!");
#endif

    }

    std::string fps = std::to_string(GetFPS()) + "FPS";

    DrawFPS(GetScreenHeight() - 40.0f, 40);
}

void Game::updateMode(){

    for(int key = 49; key <= 51; key++) {

        if(IsKeyDown(key))
            GlobalVars::gameMode = (GameMode) (key - 49);
    }
}