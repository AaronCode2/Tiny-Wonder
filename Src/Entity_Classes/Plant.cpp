#include "Plant.hpp"

Texture2D Plant::plantImage;
std::map<PlantPosIt, Vector2> Plant::plantFrame;

Plant::Plant(Rectangle object, PLANTS plantType): 
    Sprite(object, {0, 0})
{

    this->plantType = plantType;
    
    mapPlants();

    frame = plantFrame[{plantType, plantState}];
}

void Plant::update() {

    draw(plantImage);

    DrawRectangleRec(object, Utils::testColor);
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

    plantFrame[{PLANTS::CHILY, PLANT_STAGE::Seed}] = {0, 4};
    plantFrame[{PLANTS::CHILY, PLANT_STAGE::TINY_CUTE_BABY}] = {1, 4};
    plantFrame[{PLANTS::CHILY, PLANT_STAGE::LITTLE_BABY}] = {2, 4};
    plantFrame[{PLANTS::CHILY, PLANT_STAGE::GROWN_KID}] = {3, 4};
    plantFrame[{PLANTS::CHILY, PLANT_STAGE::HARVESTABLE_ADULT}] = {4, 4};
}
