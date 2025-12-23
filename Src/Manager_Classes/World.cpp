#include "World.hpp"
#include "Elements.hpp"

Texture2D World::selectorImage = {0};
Slot* World::selectedSlot = nullptr;

World::World()
{
    selectorImage = LoadTexture("../Assets/UI/Selector.png");
}

World::~World() {

#if !__linux__

    UnloadTexture(selectorImage);
    
#endif
}

void World::update() {

    if(!tileManager.tiles.empty()) {
        
        worldPos.x += tileManager.tiles[0].getVeclocity().x;
        worldPos.y += tileManager.tiles[0].getVeclocity().y;
    }

    tileManager.update();
    checkMouseActions();
}

void World::getSelectedSlot(Slot *newSelectedSlot){ selectedSlot = newSelectedSlot; }

void World::checkMouseActions() {
    
    for(float y = -4000; y < 4000; y += TILE_SIZE) {
        for(float x = -4000; x < 4000; x += TILE_SIZE) {
            
            selectionObject = {x + worldPos.x, y + worldPos.y, TILE_SIZE, TILE_SIZE};
            
            if(!Mouse::isHovering(selectionObject))
                continue;

            Rectangle selectionHitBox = {

                selectionObject.x + 20,
                selectionObject.y + 20,
                selectionObject.width - 40,
                selectionObject.height - 40,
            };

            Rectangle selectorObject = {
            
                (selectionObject.x) + sin(Utils::deltaTimeIt * 7.5f) * 1.5f,
                (selectionObject.y) + sin(Utils::deltaTimeIt * 7.5f) * 1.5f,
                (selectionObject.width) - sin(Utils::deltaTimeIt * 7.6f) * 1.5f,
                (selectionObject.height) - sin(Utils::deltaTimeIt * 7.6f) * 1.5f
            };

            DrawTexturePro(

                selectorImage,
                {0, 0, (float) selectorImage.width, (float) selectorImage.height},
                selectorObject, {0, 0}, 0, WHITE
            );

#if DEBUG_ACTIVE

            DrawRectangleRec(selectionHitBox, Utils::testColor);
#endif

            if(selectedSlot) {

                if(selectedSlot->amount <= 0) {

                    selectedSlot->item = Item::NOTHING;
                    break;
                }

                switch(selectedSlot->item) {

                    case Item::CARROT_SEED:
                    case Item::PUMPKIN_SEED:
                    case Item::CHILLEY_SEED:
                    case Item::TOMATO_SEED:
                    case Item::COCA_SEED:

                        if(!IsMouseButtonDown(MOUSE_BUTTON_LEFT))
                            break; 

                        bool foundTile = false;
                        for(auto &tile : tileManager.tiles) {
                        
                            Rectangle tileBoxDetector = tile.getObject();
                            tileBoxDetector.x += 20;
                            tileBoxDetector.y += 20;
                            tileBoxDetector.width -= 40;
                            tileBoxDetector.height -= 40;
                        
                            if(CheckCollisionRecs(tileBoxDetector, selectionObject) && tile.getType() == DIRT) {
                            
                                foundTile = true;
                            
                                for(auto &plant : tileManager.plants) {
                                
                                    if(CheckCollisionRecs(plant.getHitbox(), selectionObject)) {
                                    
                                        foundTile = false;
                                        break;
                                    }
                                }
                                break;
                            }
                        }
                        
                        if(!foundTile) break;

#define PLANT_ADJUST 10

                        selectionObject.y -= PLANT_ADJUST;

                        tileManager.plants.push_back(Plant(
                        
                            selectionObject,
                            (PLANTS) (int) selectedSlot->item,
                            PLANT_STAGE::Seed
                        ));

                        selectedSlot->amount += 1;
                        break;
            };
        }

            if(GlobalVars::gameMode == GameMode::EXPLORE || GlobalVars::HoveringOverMenu)
                return;
            
            checkerArea = {selectionObject.x - 50, selectionObject.y - 50, 155, 155};
            deleteArea = {selectionObject.x + 10, selectionObject.y + 10, 30, 30};
            
            if(Mouse::isClickedR(selectionObject)) {

                for(auto it = tileManager.tiles.begin(); it < tileManager.tiles.end();) {

                    if(CheckCollisionRecs(it->getObject(), deleteArea)) {

                        tileManager.tiles.erase(it);
                        tileManager.updateFrameType(checkerArea);
                        return;
                    } it++;
                }
            }

            if(!Mouse::isClickedL(selectionObject)) return;

            for(auto &tile : tileManager.tiles) {

                if(Utils::isSameXY(tile.getObject(), selectionObject) && tile.getType() == tileManager.selectedType)
                    return;
            }

            tileManager.tiles.push_back(Tile(
                selectionObject,
                UNKNOWN_TILE,
                tileManager.selectedType
            ));

            tileManager.updateFrameType(checkerArea);
        }
    }
}