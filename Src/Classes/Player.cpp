#include "Player.hpp"

Player::Player(Rectangle object, World &world):
    Sprite(object, frame), world(world)  
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

    const float speed = 500;

    velocity = {0, 0};

    if(getInput().up) velocity.y = -speed;
    if(getInput().down) velocity.y = speed;
    if(getInput().right) velocity.x = speed;
    if(getInput().left) velocity.x = -speed; 
    
    // object.x += velocity.x * GetFrameTime();
    // object.y += velocity.y * GetFrameTime();

    for(auto &tile : world.tiles) {

        tile.setVelocity({-velocity.x, -velocity.y});        
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
