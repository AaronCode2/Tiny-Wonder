#include <raylib.h>
#include "../Utils.hpp"
#include <iostream>

class UI {

    public:

        void update();

    private:

        void draw();

        Rectangle inventoryRec;
        Rectangle inventoryBoxes[5];
};