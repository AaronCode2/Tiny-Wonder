#pragma once
#include "Sprite.hpp"
#include "../Manager_Classes/NeighborTypes.hpp"
#include "../Utils.hpp"
#include <array>

#define TILE_SIZE 60

// Imagine not having a low taper fade 👀

enum TileType {

    GROUND = 0,
    LIGHT_GRASS,
    DARK_GRASS,
    DECORATIONS, // THE ROCK =) 
    DIRT,
};

class Tile : public Sprite {

    public:

        Tile(Rectangle object, Vector2 frame, TileType tileType, Decoration decorationType = NOT_SET);
        
        static Texture2D image;

        void update();
        void setFrame(Vector2 newFrame) { frame = newFrame; };

        TileType getType() const { return tileType; };

        void setVelocity(Vector2 newVeclocity) { velocity = newVeclocity; };
        Vector2 getVeclocity() const { return velocity; };

        std::array<Rectangle, 2> getHitBoxes() { return {hitBoxes[0], hitBoxes[1]}; };

        Decoration decorationType = NOT_SET;

        bool getIsSolid() { return isSolid; };

    private:

        TileType tileType;

        Rectangle hitBoxAjusters[2];
        Rectangle hitBoxes[2] = {WH_EMPTY_RECT, WH_EMPTY_RECT};

        bool isSolid = false;
        bool __ta = false;

        void move();
        void updateHitBox();
        void getHitBoxData();
};