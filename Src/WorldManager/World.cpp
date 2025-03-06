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

    for(int i = 0; i < 10; i++) {

        tiles.push_back(Tile(
            {
                (float) i * 100,
                100,
                100, 100
            },
            {3, 0}
        ));
    }
}

void World::update() {

    for(auto tile : tiles) {

        tile.update();
    }
}


#define numSize 7

void World::readData() {

    std::ifstream file("../Data/TileMap.txt");

    if(!file.is_open()) {

        std::cerr << "\033[31mError: Could not load Data TileMap.txt\n\033[0m";
        exit(EXIT_FAILURE);
    }

    std::string line;

    while(std::getline(file, line)) {

        int numbers[numSize]; 
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

        while (std::getline(ss, token, ',') && count < numSize) {

            try{

                int num = std::stoi(token);
                numbers[count++] = num;

            } catch (...) {}
        }

        for(int i = 0; i < count; i++) {

            std::cout << numbers[i] << " ";
        }
    }
}
