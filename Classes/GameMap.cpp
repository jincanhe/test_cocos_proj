//
// Created by hejincan on 2023/12/3.
//

#include "GameMap.h"

#include "ui/UIImageView.h"

void GameMap::setBlocks() {
    width = 15;
    height = 10;

    auto dataSize = width * height * sizeof(MAPBLOCK);
    // mapBlocks = (MAPBLOCK*)malloc(dataSize);
    mapBlocks = new MAPBLOCK[ width * height]();

    auto size = sizeof(MAPBLOCK);
    for (size_t i = 0; i < dataSize / sizeof(MAPBLOCK); i++) {
        mapBlocks[i].inpassable = 0;
        mapBlocks[i].blockType = BlockType::MAP_VOID;
        mapBlocks[i].lock = 1;

        if(i == 2 || i == 13 || i == 25 || i == 45 || i == 55 || i == 47) {
            mapBlocks[i].blockType = BlockType::MAP_POS;
            mapBlocks[i].inpassable = 1;
            mapBlocks[i].lock = 0;
        }
    }

}

void GameMap::bindEvents() {
    auto btn_1 = ui::ImageView::create();
    btn_1->loadTexture("image/maingame/btn_common_m1.png");
    addChild(btn_1);
    btn_1->setScale(0.5);
    btn_1->setPosition(Vec2(32 * (width+2),-50));
    btn_1->setTouchEnabled(true);
    btn_1->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type)
    {
        if (type == ui::Widget::TouchEventType::ENDED)
        {
            generateHeatMap(5,5);
        }
    });
}

bool GameMap::init() {
    setBlocks();
    drawMap();
    bindEvents();

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

            if(getMapBlock(x,y)->inpassable == 1) {
                tileIndicator->drawSolidRect(Vec2(pt1.x,pt1.y), Vec2(pt2.x,pt2.y), Color4F(1.0f, 0.2f, 0.5f, 0.6f));
            }
        }
    }
}

//------- 为终点 一次性生成所有格子的最短路径
void GameMap::generateHeatMap(int startX, int startY) {

    if(!flowBlocks)
    {
        flowBlocks = new FlowBlock[width * height]();
    }

    //-----  初始化终点
    std::list<HeatFront> frontQueue;

    HeatFront checkPos, checkPosNew, checkPosLeft, checkPosRight, checkPosTop, checkPosDown;
    checkPos.xy.x = startX;
    checkPos.xy.y = startY;
    checkPos.heat = 0;

    checkPos.xy.x = 16;
    checkPos.xy.y = 33;

    checkPosNew.xy.x = 17;
    checkPosNew.xy.y = 64;

    checkPosLeft.xy.x = 3;
    checkPosLeft.xy.y = 5;

    checkPosRight.xy.x = 6;
    checkPosRight.xy.y = 5;

    checkPosTop.xy.x = 5;
    checkPosTop.xy.y = 6;


    checkPosDown.xy.x = 5;
    checkPosDown.xy.y = 4;
    return;
    frontQueue.push_back(checkPos);


    //--- temp
    int pos = startY * width + startX;
    flowBlocks[pos].integration = 0;
    MAPBLOCK* block;

    while (!frontQueue.empty())
    {

        checkPos = frontQueue.front();
        frontQueue.pop_front();

        pos = checkPos.xy.y * width + checkPos.xy.x;
        block = &mapBlocks[pos];
        int now = flowBlocks[pos].integration;

        const bool checkBoolList[4] = { checkPos.xy.y > 0, checkPos.xy.y < height -1, checkPos.xy.x > 0, checkPos.xy.x < width - 1};
        const int blockPosOffsets[4] = { -width, width, -1 ,1};    //  上, 下, 左, 右
        int checkPosOffsets[4] = { -0x10000, 0x10000, -1, 1};

        for (int i = 0; i < 4; i++)
        {
            if(checkBoolList[i])
            {
                int newPos = pos + blockPosOffsets[i];
                block = &mapBlocks[newPos];

            }
        }
    }




}
