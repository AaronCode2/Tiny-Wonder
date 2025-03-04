#include "Utils.hpp"

Input getInput() {

    return {

        IsKeyDown(KEY_W),
        IsKeyDown(KEY_S),
        IsKeyDown(KEY_A),
        IsKeyDown(KEY_D),
    };
}