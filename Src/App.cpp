#include "App.hpp"

void App::run() {

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(1000, 600, "Tiny Wonder");

    SetWindowState(FLAG_WINDOW_MAXIMIZED);

    Game game;
    game.run();
}