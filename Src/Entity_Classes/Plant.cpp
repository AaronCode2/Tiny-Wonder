#include "Plant.hpp"

Texture2D Plant::plantImage;
std::map<PlantPosIt, Vector2> Plant::plantFrame;

Plant::Plant(Rectangle object, PLANTS plantType, PLANT_STAGE plantState): 
    Sprite(object, {5, 6})
{

    this->plantType = plantType;
    this->plantState = plantState;
    
    srcRect.width = plantImage.width / frame.x;
    srcRect.height = plantImage.height / frame.y;
    
    srcRect.x = plantFrame[{plantType, plantState}].x * srcRect.width;
    srcRect.y = plantFrame[{plantType, plantState}].y * srcRect.height;

    itTime = (int) plantState;

    timeForNextState[0] = GetRandomValue(1, 4);
    timeForNextState[1] = GetRandomValue(10, 15);
    timeForNextState[2] = GetRandomValue(20, 30);
    timeForNextState[3] = GetRandomValue(22, 35);

    if(plantType != PLANTS::CHILY)
        return;
    
    srcRect2 = {

        srcRect.x,
        4 * srcRect.height,
        srcRect.width,
        srcRect.height
    };

    object2 = object;
}

void Plant::update() {

    draw(plantImage);

    if(plantType == PLANTS::CHILY && plantState >= PLANT_STAGE::LITTLE_BABY)
        drawExternalPlantImage();

    object.x += velocity.x;
    object.y += velocity.y;

    updateHitBox();
    
    velocity = {0, 0};
    grow();

#if DEBUG_ACTIVE

    DrawRectangleRec(hitBox, Utils::testColor);
#endif

}

void Plant::grow() {

    if(GetTime() - time >= timeForNextState[itTime] && plantState != PLANT_STAGE::HARVESTABLE_ADULT) {

        plantState = (PLANT_STAGE) ++itTime;
        srcRect.x = plantFrame[{plantType, plantState}].x * srcRect.width;

        if(plantType == PLANTS::CHILY && plantState >= PLANT_STAGE::LITTLE_BABY)
            srcRect2.x = srcRect.x;

        time = GetTime();
    }
}

void Plant::updateHitBox() {

    hitBox = {

        object.x + 20,
        object.y + 20,
        object.width - 40,
        object.height - 40,
    };
}

void Plant::drawExternalPlantImage() {

    object2 = object;
    object2.y -= object2.height;

    DrawTexturePro(
        plantImage,
        srcRect2, object2,
        {0, 0}, 0, WHITE
    );
}

void Plant::mapPlants() {
    
    plantFrame[{PLANTS::PUMPKIN, PLANT_STAGE::Seed}] = {0, 0};
    plantFrame[{PLANTS::PUMPKIN, PLANT_STAGE::TINY_CUTE_BABY}] = {1, 0};
    plantFrame[{PLANTS::PUMPKIN, PLANT_STAGE::LITTLE_BABY}] = {2, 0};
    plantFrame[{PLANTS::PUMPKIN, PLANT_STAGE::GROWN_KID}] = {3, 0};
    plantFrame[{PLANTS::PUMPKIN, PLANT_STAGE::HARVESTABLE_ADULT}] = {4, 0};

    plantFrame[{PLANTS::CARROT, PLANT_STAGE::Seed}] = {0, 1};
    plantFrame[{PLANTS::CARROT, PLANT_STAGE::TINY_CUTE_BABY}] = {1, 1};
    plantFrame[{PLANTS::CARROT, PLANT_STAGE::LITTLE_BABY}] = {2, 1};
    plantFrame[{PLANTS::CARROT, PLANT_STAGE::GROWN_KID}] = {3, 1};
    plantFrame[{PLANTS::CARROT, PLANT_STAGE::HARVESTABLE_ADULT}] = {4, 1};

    plantFrame[{PLANTS::COCA, PLANT_STAGE::Seed}] = {0, 2};
    plantFrame[{PLANTS::COCA, PLANT_STAGE::TINY_CUTE_BABY}] = {1, 2};
    plantFrame[{PLANTS::COCA, PLANT_STAGE::LITTLE_BABY}] = {2, 2};
    plantFrame[{PLANTS::COCA, PLANT_STAGE::GROWN_KID}] = {3, 2};
    plantFrame[{PLANTS::COCA, PLANT_STAGE::HARVESTABLE_ADULT}] = {4, 2};

    plantFrame[{PLANTS::TOMATO, PLANT_STAGE::Seed}] = {0, 3};
    plantFrame[{PLANTS::TOMATO, PLANT_STAGE::TINY_CUTE_BABY}] = {1, 3};
    plantFrame[{PLANTS::TOMATO, PLANT_STAGE::LITTLE_BABY}] = {2, 3};
    plantFrame[{PLANTS::TOMATO, PLANT_STAGE::GROWN_KID}] = {3, 3};
    plantFrame[{PLANTS::TOMATO, PLANT_STAGE::HARVESTABLE_ADULT}] = {4, 3};

    plantFrame[{PLANTS::CHILY, PLANT_STAGE::Seed}] = {0, 5};
    plantFrame[{PLANTS::CHILY, PLANT_STAGE::TINY_CUTE_BABY}] = {1, 5};
    plantFrame[{PLANTS::CHILY, PLANT_STAGE::LITTLE_BABY}] = {2, 5};
    plantFrame[{PLANTS::CHILY, PLANT_STAGE::GROWN_KID}] = {3, 5};
    plantFrame[{PLANTS::CHILY, PLANT_STAGE::HARVESTABLE_ADULT}] = {4, 5};
}

