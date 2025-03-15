#pragma once
#include <raylib.h>
#include <map>
#include <string>
#include <vector>
#include <array>
#include "Sprite.hpp"
#include "../WorldManager/Tile.hpp"
#include "../WorldManager/World.hpp"
#include "../Utils.hpp"

#define AnimationMapIndexY 0
#define AnimationMapStartingIndex 1
#define AnimationMapEndingIndex 2

enum Direction {

    LEFT = 0,
    RIGHT
};


class Player : public Sprite {

    public:

        Player(Rectangle object, std::vector<Tile> &tiles);

        void update();
        Vector2 getVeclocity() { return velocity; };

        Texture2D image;

    private:

        int frameEnd = 2;
        int frameStart = 0;
        float frameBuffer = 0.1f;

        Direction direction = RIGHT;

        std::vector<Tile> &tiles;
        std::map<std::string, std::array<int, 3>> animationMap;

        void move();
        void moveScreenX();
        void moveScreenY();
        void animationLogic();
        void switchAnimation(std::string animation);
};