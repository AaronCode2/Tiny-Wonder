#pragma once
#include <raylib.h>
#include <iostream>

#define print(x) std::cout << x << '\n'

struct Input {

    bool up;
    bool down;
    bool left;
    bool right;
};

Input getInput();