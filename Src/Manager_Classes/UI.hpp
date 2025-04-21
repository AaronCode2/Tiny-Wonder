#include <raylib.h>
#include "../Utils.hpp"
#include <iostream>

#define MAX_SLOTS 5

struct Element {

    Rectangle object = {};
    Color color = Utils::testColor;
};

struct Inventory {

    Element base;
    Element slots[5];
};

class UI {

    public:

        UI();

        void update();

    private:

        void draw();

        Inventory inventory;
};