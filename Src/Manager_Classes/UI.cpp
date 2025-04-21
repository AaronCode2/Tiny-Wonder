#include "UI.hpp"

void UI::update() {

    draw();
}

void UI::draw() {

    DrawRectangleRec({100, 100, 100, 100}, RED);
    DrawText("Click Me!", 150, 150, 10, WHITE);

    if(Mouse::isClickedL({100, 100, 100, 100})) 
        std::cout << "Yeah! Thank YOU!!!!!!!!!\n";
    
}