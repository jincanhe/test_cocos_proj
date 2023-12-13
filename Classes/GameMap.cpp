//
// Created by hejincan on 2023/12/3.
//

#include "GameMap.h"

void GameMap::setBlocks() {
    width = 30;
    height = 20;

    auto dataSize = width * height * sizeof(MAPBLOCK);
    mapBlocks = (MAPBLOCK*)malloc(dataSize);
    mapBlocks = new MAPBLOCK[ width * height]();

    auto size = sizeof(MAPBLOCK);
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

bool GameMap::init() {
    setBlocks();
    drawMap();

    // auto spr = Sprite::createWithSpriteFrameName("image/eggdog/yyh_1.png");
    // spr->setAnchorPoint(Vec2(0,1));
    // spr->setScale(0.3f);
    // spr->setPosition(Vec2( 2 * 32.f,2 * -32.f));
    //
    // auto eg = Sprite::createWithSpriteFrameName("image/eggdog/egg_1.png");
    // eg->setAnchorPoint(Vec2(0,1));
    // eg->setPosition(Vec2( 10 * 32.f,2 * -32.f));
    //
    // this->addChild(spr,65555);
    // this->addChild(eg,65555);
    return true;

}

GameMap::MAPBLOCK* GameMap::getMapBlock(int x, int y) {
    if (x < 0 || x >= width || y < 0 || y >= height)
        return nullptr;

    return &mapBlocks[y * width + x];
}

void GameMap::drawMap() {
    DrawNode* tileIndicator = DrawNode::create();
    addChild(tileIndicator, 65532);


    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            Color4F iColor;
            Vec2 pt1(x * 32.0f, y * 32.0f * -1.0f);
            Vec2 pt2(pt1.x + 32.0f, pt1.y - 32.0f);

            MAPBLOCK* block = getMapBlock(x, y);
            tileIndicator->drawRect(pt1, pt2, Color4F(.0f, 0.2f, 0.5f, 0.6f));

            if(getMapBlock(x,y)->blockType == BlockType::MAP_POS) {
                tileIndicator->drawLine(Vec2(pt1.x,pt1.y - 16.f), Vec2(pt2.x,pt2.y + 16.f), Color4F(1.0f, 0.2f, 0.5f, 0.6f));
            }
        }
    }
}
