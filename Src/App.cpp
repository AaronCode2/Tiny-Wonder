#include "App.hpp"

void App::run() {

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    
    
    InitWindow(1440, 730, "Tiny Wonder");
    
    Image favicon = LoadImage("../Assets/UI/favicon.png");
    SetWindowIcon(favicon); // Sometimes it doesn't work don't know why?
    
    
    SetWindowState(FLAG_WINDOW_MAXIMIZED);
    
    SetTargetFPS(60);
    HideCursor();
    logInfo();
    InitAudioDevice();

    Game game;
    game.run();

    UnloadImage(favicon);
}

void App::logInfo() {

#if DEBUG_ENABLED

    std::cout 
        << "\033[31mDo not close this window instead please close the other window which has the Game Context\n"
        << "If you find a bug or have a issue with the game please go to https://github.com/AaronCode2/Tiny-Wonder and report an Issue\n"
        << "If you find that this game has contains malware you can send a report on gitHub\n"
        << "As from the Developer of this game: The game uses no information needed for the user\n"
        << "It is safe to say that the autosaving system will not use any personal data and is needed to run the game\n"
        << "Thank you for playing my game if you want to the 'how to play' go itch.io or gitHub :) \n\033[0m";
#endif

}
