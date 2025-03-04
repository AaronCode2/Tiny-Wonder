#pragma once
#include "Sprite.hpp"

// TODO: Make The Tile

class Tile : public Sprite {

    public:

        Tile();
        ~Tile();
        
        void update();
    private:

        void draw();
};