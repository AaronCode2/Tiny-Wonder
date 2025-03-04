#include "Player.hpp"

Player::Player(Rectangle object):
    Sprite(object, frame)  
{   

    animationMap["IdleLeft"] = {0, 0, 2};
    animationMap["IdleRight"] = {0, 2, 4};
    animationMap["RunLeft"] = {1, 0, 8};
    animationMap["RunRight"] = {2, 0, 8};

    image = LoadTexture("../Assets/Player/Player.png");

    srcRect.width = image.width / frame.x;
    srcRect.height = image.height / frame.y;
}

void Player::update() {
    
    velocity = {0, 0};
    
    srcRect.x = srcRect.width * currentFrame;

    move();
    animationLogic();
    animate(frameEnd, frameStart);
    draw(image);
}

void Player::move() {

    float speed = 500;

    if(IsKeyDown(KEY_W)) velocity.y = -speed;
    if(IsKeyDown(KEY_S)) velocity.y = speed;
    if(IsKeyDown(KEY_A)) velocity.x = -speed; 
    if(IsKeyDown(KEY_D)) velocity.x = speed;
    
    object.x += velocity.x * GetFrameTime();
    object.y += velocity.y * GetFrameTime();
}

void Player::animationLogic() {



    if(IsKeyDown(KEY_A)) {

        direction = LEFT;
        switchAnimation("RunLeft");
    }
    else if(IsKeyDown(KEY_D)) {

        direction = RIGHT;
        switchAnimation("RunRight");
    }
    else {

        if(velocity.y != 0) {

            direction == LEFT ? switchAnimation("RunLeft") : 
                switchAnimation("RunRight");
        } else {

            direction == LEFT ? switchAnimation("IdleLeft") : 
                switchAnimation("IdleRight");
        }
    }     
}

void Player::switchAnimation(std::string animation) {

    srcRect.y = srcRect.height * animationMap[animation][AnimationMapIndexY];

    if(frameEnd != animationMap[animation][AnimationMapEndingIndex]) {
        
        if(animation.find("Idle") != std::string::npos) {
            
            frameStart = animationMap[animation][AnimationMapStartingIndex] + 1;
            frameEnd = animationMap[animation][AnimationMapEndingIndex];
        } else {
            
            frameStart = animationMap[animation][AnimationMapStartingIndex] + 1;
            frameEnd = animationMap[animation][AnimationMapEndingIndex];
        }

        currentFrame = frameStart - 1;
    }

    print(currentFrame);
}
