#pragma once
#include "../Classes/Sprite.hpp"
#include "../Utils.hpp"

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

        void setVelocity(Vector2 newVeclocity) { velocity = newVeclocity; };

    private:

        TileType tileType;

        void move();
};