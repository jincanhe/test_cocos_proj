//
// Created by hejincan on 2023/12/3.
//

#include "GameMap.h"

#include "ui/UIImageView.h"

void GameMap::setBlocks() {
    width = 15;
    height = 500;

    auto dataSize = width * height * sizeof(MAPBLOCK);
    // mapBlocks = (MAPBLOCK*)malloc(dataSize);
    mapBlocks = new MAPBLOCK[ width * height]();

    auto size = sizeof(MAPBLOCK);
    for (size_t i = 0; i < dataSize / sizeof(MAPBLOCK); i++) {
        mapBlocks[i].inpassable = 0;
        mapBlocks[i].blockType = BlockType::MAP_VOID;
        mapBlocks[i].lock = 1;

        if(i == 2 || i == 4 || i == 13 || i == 25 || i == 45 || i == 55 || i == 47) {
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
            clearHeatMap();
            generateHeatMap(0,0);
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
    tileIndicator = DrawNode::create();
    addChild(tileIndicator, 65532);
    heatDebugNode = Node::create();
    addChild(heatDebugNode, 65533);


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

void GameMap::clearHeatMap() {
    if(!flowBlocks)
    {
        flowBlocks = new FlowBlock[width * height]();
    }
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int pos = y * width + x;
            flowBlocks[pos].integration = 65535;
        }
    }
}

/////////////////////////////////////////////////////////////////////////////
// 作用: 为终点 一次性生成所有格子的最短路径   todo: 多线程开启
/////////////////////////////////////////////////////////////////////////////
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

    frontQueue.push_back(checkPos);


    //--- temp
    int pos = startY * width + startX;
    flowBlocks[pos].integration = 0;
    MAPBLOCK* block;

    int count = 0;
    int whileCount = 0;
    while (!frontQueue.empty())
    {

        checkPos = frontQueue.front();
        frontQueue.pop_front();
        whileCount++;
        pos = checkPos.xy.y * width + checkPos.xy.x;
        block = &mapBlocks[pos];
        int now = flowBlocks[pos].integration;

        const bool checkBoolList[4] = { checkPos.xy.y > 0, checkPos.xy.y < height -1, checkPos.xy.x > 0, checkPos.xy.x < width - 1};
        const int blockPosOffsets[4] = { -width, width, -1 ,1};    //  下, 上, 左, 右
        int checkPosOffsets[4] = { -0x10000, 0x10000, -1, 1};

        for (int i = 0; i < 4; i++)
        {
            if(checkBoolList[i])
            {
                //--- 对应格子的各种信息
                int newPos = pos + blockPosOffsets[i];
                block = &mapBlocks[newPos];
                checkPosNew.xy.value = (uint32_t)((int)checkPos.xy.value + checkPosOffsets[i]);
                //

                int addVal = 10;

                if(block->inpassable == 1)
                {
                    addVal = 5;
                }

                int newVal = addVal + now;

                if(flowBlocks[newPos].integration == 65535)  //每一个格只处理一次
                {
                    flowBlocks[newPos].integration = newVal;  //真实存放值
                    count++;
                    checkPosNew.heat = newVal;
                    block = &mapBlocks[newPos];


                    auto itr = frontQueue.begin();


                    while (itr != frontQueue.end())
                    {
                        //-- 这里优化了 对于有 不同花费时的循环次数  todo理解
                          // auto insPos = *itr;
                          // if((int)insPos.heat > newVal)
                          // {
                          //     frontQueue.insert(itr, checkPosNew);
                          // }
                        itr++;
                    }


                    if(itr == frontQueue.end())
                    {
                        frontQueue.push_back(checkPosNew);
                    }

                }

            }
        }
    }


    heatDebugNode->removeAllChildrenWithCleanup(true);
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            Color4F iColor;
            Vec2 pt1(x * 32.0f, y * 32.0f * -1.0f);
            Vec2 pt2(pt1.x + 32.0f, pt1.y - 32.0f);


            int pos = y * width + x;
            char buf[256];
            sprintf(buf,"%s",flowBlocks[pos].integration > 60000 ? "x" : std::to_string(flowBlocks[pos].integration).c_str());
            auto label_1 = PLabel::createWithTTF(buf, "fonts/SiYuanSongTi.otf", 18);
            label_1->setPosition(pt1 + Vec2(16.f,-16.f));
            label_1->setTextColor(Color4B::BLACK);
            heatDebugNode->addChild(label_1);

        }
    }




}
