#include "World.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

void World::update(Vector2 playerVeclocity) {

    tileManager.update();
    placeTiles();
}

void World::placeTiles() {
    Vector2 mousePos = GetMousePosition();

    // Find the nearest tile to align with
    float closestX = 0, closestY = 0;
    float minDistance = 10000.0f; // Arbitrary large number

    for (auto &tile : tileManager.tiles) {

        Vector2 tilePos = { tile.getObject().x, tile.getObject().y };
        float dist = sqrtf((mousePos.x - tilePos.x) * (mousePos.x - tilePos.x) + (mousePos.y - tilePos.y) * (mousePos.y - tilePos.y));

        if (dist < minDistance) {
            
            minDistance = dist;
            closestX = tile.getObject().x;
            closestY = tile.getObject().y;
        }
    }

    // Snap new tile relative to the closest tile
    float snappedX = closestX + ((int)(mousePos.x - closestX) / 60) * 60;
    float snappedY = closestY + ((int)(mousePos.y - closestY) / 60) * 60;

    Rectangle object = {snappedX, snappedY, 60, 60};
    Rectangle checkerArea = {object.x, object.y, 60, 60};

    if (Mouse::isHovering(object))
        DrawRectangleRec(object, Utils::testColor);
    else return;

    if (Mouse::isClickedR(object)) {
        for (auto it = tileManager.tiles.begin(); it < tileManager.tiles.end();) {
            if (CheckCollisionRecs(it->getObject(), object)) {
                tileManager.tiles.erase(it);
                tileManager.updateFrameType(checkerArea);
                return;
            } else it++;
        }
    }

    if (!Mouse::isClickedL(object)) return;

    // Prevent duplicate tiles
    for (auto &tile : tileManager.tiles) {
        if (Utils::isSameRect(tile.getObject(), object))
            return;
    }

    tileManager.tiles.push_back(Tile(object, {2, 2}));
    tileManager.updateFrameType(checkerArea);
}
