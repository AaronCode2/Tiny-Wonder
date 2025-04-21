#pragma once
#include "../Entity_Classes/Sprite.hpp"
#include "../Utils.hpp"

#define TILE_SIZE 60

// Imagine not having a low taper fade 👀

enum TileType {

    GROUND = 0,
    LIGHT_GRASS,
    DARK_GRASS,
    SMALL_GRASS,
    SEA_DECORATIONS, // THE ROCK =) 
    DIRT
};

class Tile : public Sprite {

    public:

        Tile(Rectangle object, Vector2 frame, TileType tileType);
        
        static Texture2D image;

        void update();
        void setFrame(Vector2 newFrame) { frame = newFrame; };

        TileType getType() const { return tileType; };

        void setVelocity(Vector2 newVeclocity) { velocity = newVeclocity; };
        Vector2 getVeclocity() const { return velocity; };

    private:

        TileType tileType;

        void move();
};