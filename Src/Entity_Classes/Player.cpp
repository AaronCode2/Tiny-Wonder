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

void Player::update() {

    velocity = {0, 0};

    const int speed = 500 * GetFrameTime();

    if(getInput().up) velocity.y = -speed;
    if(getInput().down) velocity.y = speed;
    if(getInput().right) velocity.x = speed;
    if(getInput().left) velocity.x = -speed;

    animationLogic();
    move();
    animate(frameEnd, frameStart, frameBuffer);
    draw(image);
}

void Player::move() {
    
    moveScreenX();
    moveScreenY();
    updateHitBox();
}

void Player::updateHitBox() {

    hitBox = object; 
}

void Player::moveScreenX() {

    object.x += velocity.x;
    updateHitBox();

    for(auto rangeBoxSide : rangeBoxSides) {

        if(CheckCollisionRecs(rangeBoxSide, object)) {
            
            for(auto &tile : tiles) 
                tile.setVelocity({-velocity.x, 0.0f});

            if(velocity.x > 0) {
                
                const float offset = hitBox.x - object.x + hitBox.width;

                object.x = rangeBoxSide.x - offset;
            }
        
            if(velocity.x < 0) {
                
                const float offset = hitBox.x - object.x;

                object.x = rangeBoxSide.x + rangeBoxSide.width - offset;
            }

            velocity.x = 0;
        }
    }
}

void Player::moveScreenY() {

    object.y += velocity.y;
    updateHitBox();

    for(auto rangeBoxSide : rangeBoxSides) {

        if(CheckCollisionRecs(rangeBoxSide, object)) {

            for(auto &tile : tiles) 
                tile.setVelocity({0.0f, -velocity.y});

            if(velocity.y > 0) {
                
                const float offset = hitBox.y - object.y + hitBox.height;
        
                object.y = rangeBoxSide.y - offset;
            }
            
            if(velocity.y < 0) {
                    
                const float offset = hitBox.y - object.y;
        
                object.y = rangeBoxSide.y + rangeBoxSide.height - offset;
            }

            velocity.y = 0;
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
