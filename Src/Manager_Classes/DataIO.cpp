#include "DataIO.hpp"

DataIO::DataIO(
    std::vector<Tile> &tiles, Vector2 &worldPos, Rectangle &playerObject, 
    std::array<std::array<Slot, 5>, 6> &slots, std::vector<Plant> &plants
):
    tiles(tiles), worldPos(worldPos), playerObject(playerObject), slots(slots), plants(plants)
{   
    readTileData();
    readPosData();
    readInventoryData();
    readPlantData();
}

DataIO::~DataIO(){

    writeTileData();
    writePosData();
    writeInventoryData();
    writePlantData();
}

void DataIO::writeTileData() {

    std::ofstream file(TILE_MAP_PATH);

    if(!file.is_open())
        Utils::exitApp("Error: Could not write Data in TileMap.txt");

    for(auto tile : tiles) {  

       file 
       << "{"
            << std::fixed << std::setprecision(FLOAT_PRECISION)

            << tile.getObject().x << ", " << tile.getObject().y << ", "
            << tile.getFrame().x << ", " << tile.getFrame().y << ", "
            << (int) tile.getType() << ", " << tile.decorationType   

        << "}\n";  
    }

    file.close();
}

void DataIO::readTileData() {

    std::ifstream file(TILE_MAP_PATH);

    if(!file.is_open()) 
        Utils::exitApp("Error: Could not read Data in TileMap.txt");

    std::string line;

    while(std::getline(file, line)) {

        int numbers[NUM_SIZE]; 
        int count = 0;        
        std::string temp;

        for(size_t i = 0; i < line.length(); i++) {

            if(line[i] == '{')
                continue;

            if(line[i] == '}')
                break;

            temp += line[i];  
        }

        std::stringstream ss(temp);
        std::string token;

        while(std::getline(ss, token, ',') && count < NUM_SIZE) 
            numbers[count++] = std::stoi(token);

        tiles.push_back(Tile(
            {
                (float) numbers[X],
                (float) numbers[Y],
                (float) 60,
                (float) 60
            },
            {(float) numbers[FRAME_X], (float) numbers[FRAME_Y]},
            (TileType) numbers[ID],
            (Decoration) numbers[DECORATION_ID]
        ));
    }

    file.close();
}

void DataIO::readPosData() {

    std::ifstream file(POS_PATH);

    std::string line;
    int count = 0;

    while(std::getline(file, line)) {

        std::string temp;
        for(size_t i = 0; i < line.length(); i++) {

            if(line[i] == '{')
                continue;

            if(line[i] == '}')
                break;

            temp += line[i];  
        }

        std::stringstream ss(temp);
        std::string token;

        while(std::getline(ss, token, ',') && count < POS_ELEMENTS) {

            int num = std::stof(token);

            switch(count++) {

                case WORLD_X:
                    worldPos.x = num;
                    break;
                
                case WORLD_Y:
                    worldPos.y = num;
                    break;

                case PLAYER_X:
                    playerObject.x = num;
                    break;

                case PLAYER_Y:
                    playerObject.y = num;
                    break;
            }
        }
    }

    file.close();
}

void DataIO::writePosData() {

    std::ofstream file(POS_PATH);

    if(!file.is_open())
        Utils::exitApp("Could not write Data to PosData");

    file
    << "{" << std::fixed << std::setprecision(FLOAT_PRECISION)
     
        << worldPos.x << ", " 
        << worldPos.y << ", "
        << playerObject.x << ", "
        << playerObject.y

    << "}\n";


    file.close();
}

void DataIO::readPlantData() {

    std::ifstream file(PLANT_DATA_PATH);

    std::string line;
    
    while(std::getline(file, line)) {
        
        int elements[PLANT_SIZE]; 
        int count = 0;
        std::string temp;

        for(size_t i = 0; i < line.length(); i++) {

            if(line[i] == '{')
                continue;

            if(line[i] == '}')
                break;

            temp += line[i];  
        }

        std::stringstream ss(temp);
        std::string token;

        while(std::getline(ss, token, ',') && count < PLANT_ELEMENTS) {

            elements[count++] = std::stof(token);
        }

        plants.push_back(Plant(
                {
                    (float) elements[0], 
                    (float) elements[1],
                    60, 60
                },
                (PLANTS) elements[2],
                (PLANT_STAGE) elements[3]
            )
        );
    }

    file.close();
}

void DataIO::writePlantData() {

    std::ofstream file(PLANT_DATA_PATH);

    if(!file.is_open())
        Utils::exitApp("Could not write Data to PlantData");

    for(auto plant : plants) {

        file 
        << "{" << std::fixed << std::setprecision(FLOAT_PRECISION)

            << plant.getObject().x << ", "
            << plant.getObject().y << ", "
            << (int) plant.getPlantType() << ", "
            << (int) plant.getPlantState()
        
        << "}\n";
    }

    file.close();
}

void DataIO::readInventoryData()
{

    std::ifstream file(INVENTORY_PATH);

    std::string line;
    int count = 0;
    int y = 0;
    int x = 0;

    while(std::getline(file, line)) {

        std::string temp;
        for(size_t i = 0; i < line.length(); i++) {

            if(line[i] == '{')
                continue;

            if(line[i] == '}')
                break;

            temp += line[i];  
        }

        std::stringstream ss(temp);
        std::string token;

        count = 0;

        while(std::getline(ss, token, ',') && count < INVENTORY_ELEMENTS) {

            int num = std::stof(token);

            if(count == 0)
                slots[y][x].item = (Item) num;
            else slots[y][x].amount = num;

            count++;
        }

        x++;
        if(x >= 5) {

            y++;
            x = 0;
        }
    }

    file.close();
}

void DataIO::writeInventoryData()
{

    std::ofstream file(INVENTORY_PATH);

    if(!file.is_open())
        Utils::exitApp("Could not write Data to InventoryData");

    for(int y = 0; y < 6; y++) {
        for(int x = 0; x < 5; x++) {

            file 
            << "{"

                << (int) slots[y][x].item << ", "
                << slots[y][x].amount

            << "}\n";
        }
    }

    file.close();
}
