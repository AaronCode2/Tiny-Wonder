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
}

void Player::update() {

    move();
    animationLogic();
    animate(frameEnd, frameStart, frameBuffer);
    draw(image);
}

void Player::move() {

    const float speed = 600;

    Rectangle movementRangeBox = {

        400, 200, 
        (float) GetScreenWidth() - 800, 
        (float) GetScreenHeight() - 400
    };

    leftSide = {

        400,
        200,
        10,
        10
    };

    velocity = {0, 0};

    if(getInput().up) velocity.y = -speed;
    if(getInput().down) velocity.y = speed;
    if(getInput().right) velocity.x = speed;
    if(getInput().left) velocity.x = -speed; 
    
    moveScreenX();
    // moveScreenY();

    DrawRectangleRec(leftSide, Utils::testColor);
}

void Player::moveScreenX() {

    object.x += velocity.x * GetFrameTime();

    if(!CheckCollisionRecs(leftSide, object)) {
            
        if(velocity.x > 0) {

            velocity.x = 0;
    
            object.x = leftSide.x - object.x + object.width;
        }
    
        if(velocity.x < 0) {
    
            velocity.x = 0;
    
            object.x = leftSide.x + leftSide.width - object.x;
        }

        for(auto &tile : tiles) 
            tile.setVelocity({-velocity.x, 0});
    }
}

void Player::moveScreenY() {

    object.y += velocity.y * GetFrameTime();

    if(!CheckCollisionRecs(movementRangeBox, object)) {

        for(auto &tile : tiles) 
            tile.setVelocity({0, -velocity.y});

        if(velocity.y > 0) {

            velocity.y = 0;

            object.y = movementRangeBox.y - object.y + object.height;
        }

        if(velocity.y < 0) {

            velocity.y = 0;

            object.y = movementRangeBox.y + movementRangeBox.height - object.y;
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
