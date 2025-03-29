#include "DataIO.hpp"

DataIO::DataIO(std::vector<Tile> &tiles, Vector2 &worldPos):
    tiles(tiles), worldPos(worldPos) 
{   
    readTileData();
}

void DataIO::writeTileData() {

    std::ofstream file(TILE_MAP_PATH);

    if(!file.is_open()) {

        std::cerr << "\033[31mError: Could not write Data in TileMap.txt\n\033[0m";
        exit(EXIT_FAILURE);
    }

    for(auto tile : tiles) {  

       file 
       << "{"

            << tile.getObject().x << ", " << tile.getObject().y << ", "
            << tile.getObject().width << ", " << tile.getObject().height << ", "
            << tile.getFrame().x << ", " << tile.getFrame().y << ", "
            << (int) tile.getType()   

        << "}\n";  
    }

    file.close();
}

void DataIO::readTileData() {

    std::ifstream file(TILE_MAP_PATH);

    if(!file.is_open()) {

        std::cerr << "\033[31mError: Could not read Data in TileMap.txt\n\033[0m";
        exit(EXIT_FAILURE);
    }

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

        while (std::getline(ss, token, ',') && count < NUM_SIZE - 1) {

            try{

                int num = std::stoi(token);
                numbers[count++] = num;

            } catch (...) {}
        }

        tiles.push_back(Tile(
            {
                (float) numbers[X],
                (float) numbers[Y],
                (float) numbers[WIDTH],
                (float) numbers[HEIGHT]
            },
            {(float) numbers[FRAME_X], (float) numbers[FRAME_Y]}
        ));
    }

    file.close();
}

void DataIO::readWorldPosData() {

    std::ifstream file(WORLD_POS_PATH);

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

        while (std::getline(ss, token, ',') && count < 2) {

            try{

                int num = std::stoi(token);
                if(count == 0)
                    worldPos.x = num;
                else worldPos.y = num;

            } catch (...) {}
        }
    }

}

void DataIO::writeWorldPosData() {

    std::ofstream file(WORLD_POS_PATH);

    if(!file.is_open()) {

        std::cerr << "/033[31mCould not write Data to WorldPosData\n\033[31m";
        exit(EXIT_FAILURE);
    }

    file 
    << "{"

        << worldPos.x << ", "
        << worldPos.y << ", "
    << "}\n";
}