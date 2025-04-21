#include <raylib.h>
#include "../Utils.hpp"
#include <iostream>

struct Element {

    Rectangle object;
    Color color = Utils::testColor;
};

struct Inventory {

    Element base;
    Element inventorySlots[5];
};

class UI {

    public:

        void update();

    private:

        void draw();

        Inventory inventory;
};