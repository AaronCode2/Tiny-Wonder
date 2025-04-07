#pragma once
#include "../Entity_Classes/Sprite.hpp"
#include "../Utils.hpp"

#define TILE_SIZE 60.0f

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
        Vector2 getVeclocity() const { return velocity; };

    private:

        TileType tileType;

        void move();
};