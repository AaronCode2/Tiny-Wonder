#pragma once
#include <raylib.h>
#include <map>
#include <string>
#include <array>
#include "Sprite.hpp"
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

        Player(Rectangle object);

        void update();

        Texture2D image;

    private:

        int frameEnd = 2;
        int frameStart = 0;

        Direction direction = LEFT;

        std::map<std::string, std::array<int, 3>> animationMap;
        Vector2 velocity;

        void move();
        void animationLogic();
        void switchAnimation(std::string animation);
};