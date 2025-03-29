#pragma once
#include <raylib.h>
#include <map>
#include <string>
#include <vector>
#include <array>
#include "Sprite.hpp"
#include "../Entity_Classes/Tile.hpp"
#include "../Manager_Classes/World.hpp"
#include "../Utils.hpp"

#define AnimationMapIndexY 0
#define AnimationMapStartingIndex 1
#define AnimationMapEndingIndex 2

enum Direction {

    LEFT = 0,
    RIGHT
};

enum class RangeSiders {

    TOP = 0,
    BOTTOM,
    LEFT,
    RIGHT
};

class Player : public Sprite {

    public:

        Player(Rectangle object, std::vector<Tile> &tiles);

        void update();
        Vector2 getVeclocity() const { return velocity; };
        Vector2 getScreenVelocity() const { return screenVeclocity; };

        Texture2D image;

    private:

        const int speed = 500;
        int frameEnd = 2;
        int frameStart = 0;
        float frameBuffer = 0.1f;

        Direction direction = RIGHT;
        Vector2 screenVeclocity = {0, 0};

        std::vector<Tile> &tiles;
        std::map<std::string, std::array<int, 3>> animationMap;
        Rectangle movementRangeBox = {

            400, 200, 
            (float) GetScreenWidth() - 800, 
            (float) GetScreenHeight() - 400
        };

        Rectangle rangeBoxSides[4];
        Rectangle hitBox;

        void move();
        void updateHitBox();
        void moveScreenX();
        void moveScreenY();
        void animationLogic();
        void switchAnimation(std::string animation);
};