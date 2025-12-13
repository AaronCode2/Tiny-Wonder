#pragma once
#include <raylib.h>
#include <map>
#include "Sprite.hpp"

enum class PLANTS {

    PUMPKIN = 0,
    CARROT,
    COCA,
    TOMATO,
    CHILY
};

enum class PLANT_STAGE {

    Seed = 0,
    TINY_CUTE_BABY,
    LITTLE_BABY,
    GROWN_KID,
    HARVESTABLE_ADULT // I read this so aliens unharvest our sun ::
};

struct PlantPosIt {

    PLANTS plantTypeIt;
    PLANT_STAGE plantStateIt;

    // Here to prevent an Error! :(

    bool operator<(const PlantPosIt& other) const {

        if (plantTypeIt != other.plantTypeIt)
            return plantTypeIt < other.plantTypeIt;

        return plantStateIt < other.plantStateIt;
    }
};

class Plant : public Sprite {


    public:

        Plant(Rectangle object, PLANTS plantType);

        static Texture2D plantImage;
        static std::map<PlantPosIt, Vector2> plantFrame;

        void update();

    private:

        void mapPlants();

        PLANTS plantType;
        PLANT_STAGE plantState = PLANT_STAGE::Seed;

};