#include "Player.hpp"

Player::Player(Rectangle object, std::vector<Tile> &tiles):
    Sprite(object, frame), tiles(tiles)  
{   

    animationMap["IdleLeft"] = {0, 0, 2};
    animationMap["IdleRight"] = {0, 2, 4};
    animationMap["RunLeft"] = {1, 0, 8};
    animationMap["RunRight"] = {2, 0, 8};

    image = LoadTexture("../Assets/Player/Player.png");

    frame = {8, 3};

    srcRect.width = image.width / frame.x;
    srcRect.height = image.height / frame.y;

    rangeBoxSides[(int) RangeSiders::LEFT] = {

        400,
        200,
        10,
        GetScreenHeight() - 400.0f
    };

    rangeBoxSides[(int) RangeSiders::RIGHT] = {

        GetScreenWidth() - 400.0f,
        200,
        10,
        GetScreenHeight() - 400.0f
    };

    rangeBoxSides[(int) RangeSiders::TOP] = {

        400,
        200,
        GetScreenWidth() - 800.0f,
        10
    };

    rangeBoxSides[(int) RangeSiders::BOTTOM] = {

        400,
        GetScreenHeight() - 200.0f,
        GetScreenWidth() - 800.0f,
        10
    };
}

Player::~Player() {

    UnloadTexture(image);
}

void Player::update() {

    velocity = {0, 0};

    const int speed = 500;

    if(getInput().up) velocity.y = -speed * GetFrameTime();
    if(getInput().down) velocity.y = speed * GetFrameTime();
    if(getInput().right) velocity.x = speed * GetFrameTime();
    if(getInput().left) velocity.x = -speed * GetFrameTime();

    if(IsKeyDown(KEY_R)) {

        object.x = GetScreenWidth() / 2;
        object.y = GetScreenHeight() / 2;
    }

    animationLogic();
    move();
    animate(frameEnd, frameStart, frameBuffer);
    draw(image);

    DrawRectangleRec(hitBox, Utils::testColor);
}

void Player::move() {
    
    moveScreenX();
    moveScreenY();
    updateHitBox();
}

void Player::updateHitBox() {

    hitBox = {

        object.x + 40,
        object.y + 80,
        object.width - 70,
        object.height - 85
    };
}

void Player::moveScreenX() {

    object.x += velocity.x;
    updateHitBox();

    for(auto &tile : tiles) {

        if(!tile.getIsSolid()) continue;

        for(const auto tileHitBox : tile.getHitBoxes()) {

            Utils::collisionActionX(object, hitBox, tileHitBox, velocity);
            tile.updateHitBox();
        }
    }

    for(const auto rangeBoxSide : rangeBoxSides) {

        DrawRectangleRec(rangeBoxSide, Utils::testColor);

        if(CheckCollisionRecs(rangeBoxSide, hitBox)) {
            
            for(auto &tile : tiles) {

                if(!tile.getIsSolid()) continue;

                for(const auto tileHitBox : tile.getHitBoxes()) {

                    Utils::collisionActionX(object, hitBox, tileHitBox, velocity);
                    tile.updateHitBox();
                }
            }

            Utils::collisionActionX(object, hitBox, rangeBoxSide, velocity);
        }
    }
}

void Player::moveScreenY() {

    object.y += velocity.y;
    updateHitBox();
    
    for(const auto rangeBoxSide : rangeBoxSides) {
        
        if(CheckCollisionRecs(rangeBoxSide, hitBox)) {
            
            for(auto &tile : tiles)
            tile.setVelocity({0.0f, -velocity.y});
            
            Utils::collisionActionY(object, hitBox, rangeBoxSide, velocity);
        }
    }

    for(auto &tile : tiles) {
    
        for(const auto tileHitBox : tile.getHitBoxes()) {

            Utils::collisionActionY(object, hitBox, tileHitBox, velocity);
            tile.updateHitBox();
        }
    }
}

void Player::animationLogic() {

    srcRect.x = srcRect.width * currentFrame;
    
    if(velocity.x != 0 || velocity.y != 0) frameBuffer = 0.1f;
    else frameBuffer = 0.5f;

    if(getInput().left) {

        direction = LEFT;
        switchAnimation("RunLeft");
    } else if(getInput().right) {

        direction = RIGHT;
        switchAnimation("RunRight");
    } else {

        const std::string animation = (velocity.y != 0) ? "Run" : "Idle";

        direction == LEFT ? switchAnimation(animation + "Left") : 
            switchAnimation(animation + "Right");
    }     
}

void Player::switchAnimation(std::string animation) {

    srcRect.y = srcRect.height * animationMap[animation][AnimationMapIndexY];

    if(frameEnd == animationMap[animation][AnimationMapEndingIndex]) 
        return;    
    
    frameStart = animationMap[animation][AnimationMapStartingIndex];
    frameEnd = animationMap[animation][AnimationMapEndingIndex];

    currentFrame = frameStart;
}
