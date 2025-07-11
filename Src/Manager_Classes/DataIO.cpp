#include "DataIO.hpp"

DataIO::DataIO(std::vector<Tile> &tiles, Vector2 &worldPos, Rectangle &playerObject):
    tiles(tiles), worldPos(worldPos), playerObject(playerObject) 
{   
    readTileData();
    readPosData();
}

DataIO::~DataIO(){

    writeTileData();
    writePosData();
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
            << tile.getObject().width << ", " << tile.getObject().height << ", "
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
                (float) numbers[WIDTH],
                (float) numbers[HEIGHT]
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