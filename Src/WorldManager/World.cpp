#include "World.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

World::World() {

    Tile::image = LoadTexture("../Assets/Tiles/Tile.png");
}

World::~World() {

    UnloadTexture(Tile::image);
}

void World::init() {

    readData();
}

void World::update() {

    for(auto tile : tiles) {

        tile.update();
    }
}


void World::readData() {

    std::ifstream file(FILE_NAME);

    if(!file.is_open()) {

        std::cerr << "\033[31mError: Could not read Data in TileMap.txt\n\033[0m";
        exit(EXIT_FAILURE);
    }

    std::string line;

    while(std::getline(file, line)) {

        int numbers[NUM_SIZE]; 
        int count = 0;        
        bool insideBraces = false;
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

        while (std::getline(ss, token, ',') && count < NUM_SIZE) {

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
}

void World::writeData() {

    std::ofstream file(FILE_NAME);

    if(!file.is_open()) {

        std::cerr << "\033[31mError: Could not write Data in TileMap.txt\n\033[0m";
        exit(EXIT_FAILURE);
    }

    for(auto tile : tiles) {  

       file << "{"

                << tile.getObject().x << ", " << tile.getObject().y << ", "
                << tile.getObject().width << ", " << tile.getObject().height << ", "
                << tile.getFrame().x << ", " << tile.getFrame().y << ", "
                << tile.getType()   

            << "}\n";  
    }
}
