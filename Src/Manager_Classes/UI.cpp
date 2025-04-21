#include "UI.hpp"

void UI::update() {

    draw();
}

void UI::draw() {

    if(GuiButton({100, 100, 200, 200}, "Click Me!")) {

        std::cout << "Yeah, Thank YOU!!!!!!!";
    }
}