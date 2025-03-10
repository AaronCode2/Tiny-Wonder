#pragma once
#include "../Classes/Sprite.hpp"

// TODO: Make The Tile

enum TileType {

    GRASS = 0,
    DIRT
};

class Tile : public Sprite {

    public:

        Tile(Rectangle object, Vector2 frame);
        ~Tile();
        
        static Texture2D image;

        void update();
        void setFrame(Vector2 newFrame) { frame = newFrame; };

        TileType getType() { return tileType; };

    private:

        TileType tileType;
};