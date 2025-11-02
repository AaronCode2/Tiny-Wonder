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

#if DEBUG_ACTIVE

    DrawRectangleRec(hitBox, Utils::testColor);
    DrawRectangleRec(cameraBox, Utils::testColor);

#endif

}

void Player::move() {
    
    moveScreenX();
    moveScreenY();
    updateHitBox();
    updateCamera();
}

void Player::updateCamera() {

    cameraBox = {

        object.x - 350,
        object.y - 300,
        800,
        700
    };
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

    if(cameraBox.x <= 0 && velocity.x < 0 || cameraBox.x + cameraBox.width >= GetScreenWidth() && velocity.x > 0) {
        
        for(auto &tile : tiles) {
            
            tile.setVelocity({-velocity.x, 0});
            tile.updateHitBox();
        }
        
        object.x -= velocity.x;
    }

    for(auto &tile : tiles) {
        
        if(!tile.getIsSolid()) continue;
        
        for(const auto tileHitBox : tile.getHitBoxes()) {
            
            Utils::collisionActionX(object, hitBox, tileHitBox, velocity);
            tile.updateHitBox();
        }
    }

}

void Player::moveScreenY() {

    object.y += velocity.y;
    updateHitBox();

    if(cameraBox.y <= 0 && velocity.y < 0 || cameraBox.y + cameraBox.height >= GetScreenHeight() && velocity.y > 0) {
        
        for(auto &tile : tiles) {
            
            tile.setVelocity({0, -velocity.y});
            tile.updateHitBox();
        }
        
        object.y -= velocity.y;
    }

    for(auto &tile : tiles) {
        
        if(!tile.getIsSolid()) continue;

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
