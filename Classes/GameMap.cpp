//
// Created by hejincan on 2023/12/3.
//

#include "GameMap.h"

bool GameMap::init() {


    auto size = sizeof(MAPBLOCK);



    auto size1 = sizeof(MAPBLOCK1);

    setBlocks();

    return true;

}

void GameMap::setBlocks() {
    width = 20;
    height = 5;

    auto dataSize = width * height * sizeof(MAPBLOCK);
    mapBlocks = (MAPBLOCK*)malloc(dataSize);
    for (size_t i = 0; i < dataSize / sizeof(MAPBLOCK); i++) {
        mapBlocks[i].inpassable = 1;
        mapBlocks[i].blockType = BlockType::MAP_VOID;
        mapBlocks[i].lock = 1;

        if(i == 5) {
                mapBlocks[i].blockType = BlockType::MAP_POS;
                mapBlocks[i].lock = 0;
        }
        if(i == 99) {
            mapBlocks[i].blockType = BlockType::MAP_POS;
            mapBlocks[i].lock = 0;
        }
    }

}

GameMap::MAPBLOCK* GameMap::getMapBlock(int x, int y) {
    if (x < 0 || x >= width || y < 0 || y >= height)
        return nullptr;

    return &mapBlocks[y * width + x];
}
