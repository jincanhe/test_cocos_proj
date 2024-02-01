//
// Created by hejincan on 2023/12/3.
//

#include "GameMap.h"

#include "ui/UIImageView.h"
// MAP_VOID,
// MAP_POS,
// MAP_ROAD,
// MAP_GLASS,
std::vector<int> costMap =
{
    10,
    255,
    12,
    15,
};

void GameMap::setBlocks() {
    width = 6; ///////
    height = 3;

    auto dataSize = width * height * sizeof(MAPBLOCK);
    // mapBlocks = (MAPBLOCK*)malloc(dataSize);
    mapBlocks = new MAPBLOCK[width * height]();

    auto size = sizeof(MAPBLOCK);
    for (size_t i = 0; i < dataSize / sizeof(MAPBLOCK); i++)
    {
        mapBlocks[i].inpassable = 0;
        mapBlocks[i].blockType = BlockType::MAP_VOID;
        mapBlocks[i].cost = 1;

        if (i == 2 || i == 4 || i == 13 || i == 25 || i == 45 || i == 55 || i == 47)
        {
            mapBlocks[i].blockType = BlockType::MAP_POS;
            mapBlocks[i].inpassable = 1;
            mapBlocks[i].cost = 0;
        }
        // else
        // {
        //     if(i % 3 == 2)
        //     {
        //         mapBlocks[i].blockType = BlockType::MAP_ROAD;
        //     }
        // }


        if (i % 3 == 1)
        {
            mapBlocks[i].blockType = BlockType::MAP_ROAD;
        }

        if( i == 11)
        {
            mapBlocks[i].blockType = BlockType::MAP_ROAD;

        }

        if( i == 16)
        {
            mapBlocks[i].blockType = BlockType::MAP_VOID;

        }
    }
}

void GameMap::bindEvents() {
    auto btn_1 = ui::ImageView::create();
    btn_1->loadTexture("image/maingame/btn_common_m1.png");
    addChild(btn_1);
    btn_1->setScale(0.5);
    btn_1->setPosition(Vec2(32 * (width + 2), -50));
    btn_1->setTouchEnabled(true);
    btn_1->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type) {
        if (type == ui::Widget::TouchEventType::ENDED)
        {
            clearHeatMap();
            generateHeatMap(2, 1);
            generateVectorMap(1);
            drawHeatMap();
        }
    });
}

void GameMap::initUI() {
    tileIndicator = DrawNode::create();
    addChild(tileIndicator, 65532);
    debugDrawNode = DrawNode::create();
    addChild(debugDrawNode, 65532);
    heatDebugNode = Node::create();
    addChild(heatDebugNode, 65535);
}

bool GameMap::init() {

    initUI();
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
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            Color4F iColor;
            Vec2 pt1(x * 32.0f, y * 32.0f * -1.0f);
            Vec2 pt2(pt1.x + 32.0f, pt1.y - 32.0f);

            MAPBLOCK* block = getMapBlock(x, y);
            tileIndicator->drawRect(pt1, pt2, Color4F(.0f, 0.2f, 0.5f, 0.3f));

            if (block->inpassable == 1)
            {
                tileIndicator->drawSolidRect(Vec2(pt1.x, pt1.y), Vec2(pt2.x, pt2.y), Color4F(0.5f, 0.2f, 0.5f, 0.3f));
            } else
            {
                if (block->blockType == BlockType::MAP_ROAD)
                {
                    auto btn_1 = ui::ImageView::create();
                    btn_1->loadTexture("image/maingame/road.png");
                    addChild(btn_1);
                    btn_1->setPosition(pt1 + Vec2(16.f, -16.f));
                    btn_1->setOpacity(128);
                    btn_1->setScale(0.7);
                }

                if (block->blockType == BlockType::MAP_GLASS)
                {
                    auto btn_1 = ui::ImageView::create();
                    btn_1->loadTexture("image/maingame/glass.png");
                    addChild(btn_1);
                    btn_1->setPosition(pt1 + Vec2(16.f, -16.f));
                    btn_1->setOpacity(128);
                    btn_1->setScale(0.7);
                }
            }
        }
    }
}

void GameMap::clearHeatMap() {
    if (!flowBlocks)
    {
        flowBlocks = new FlowBlock[width * height]();
    }
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            int pos = y * width + x;
            flowBlocks[pos].integration = 65535;
        }
    }
}

void GameMap::drawHeatMap() {


    std::vector<Vec2> flowIndex = {
        Vec2(0.0f, 0.0f),
        Vec2(-1.0f, -1.0f).getNormalized(),
        Vec2(0.0f, -1.0f),
        Vec2(1.0f, -1.0f).getNormalized(),
        Vec2(1.0f, 0.0f),
        Vec2(1.0f, 1.0f).getNormalized(),
        Vec2(0.0f, 1.0f),
        Vec2(-1.0f, 1.0f).getNormalized(),
        Vec2(-1.0f, 0.0f),
    };


    heatDebugNode->removeAllChildrenWithCleanup(true);
    debugDrawNode->removeAllChildrenWithCleanup(true);
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            Color4F iColor;
            Vec2 pt1(x * 32.0f, y * 32.0f * -1.0f);
            Vec2 pt2(pt1.x + 32.0f, pt1.y - 32.0f);


            int pos = y * width + x;
            char buf[256];
            sprintf(buf, "%s,%d", flowBlocks[pos].integration > 60000
                                      ? "x"
                                      : std::to_string(flowBlocks[pos].integration).c_str(),  flowBlocks[pos].flow);
            auto label_1 = PLabel::createWithTTF(buf, "fonts/SiYuanSongTi.otf", 14);
            label_1->setPosition(pt1 + Vec2(16.f, -16.f));
            label_1->setTextColor(Color4B::BLACK);
            heatDebugNode->addChild(label_1);

            Vec2 origin(pt1 + Vec2(16.f, 16.f));
            Vec2 dest = origin + flowIndex[flowBlocks[pos].flow] * 16.0f;
            origin.y *= -1.0f;
            dest.y *= -1.0f;
            debugDrawNode->drawLine(origin, dest, Color4F::YELLOW);

        }
    }
}

/////////////////////////////////////////////////////////////////////////////
// 作用: 为终点 一次性生成所有格子的最短路径   todo: 多线程开启
/////////////////////////////////////////////////////////////////////////////
void GameMap::generateHeatMap(int startX, int startY) {
    if (!flowBlocks)
    {
        flowBlocks = new FlowBlock[width * height]();
    }

    //-----  初始化终点  内存视图中为16进制
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

        const bool checkBoolList[4] = {
            checkPos.xy.y > 0, checkPos.xy.y < height - 1, checkPos.xy.x > 0, checkPos.xy.x < width - 1
        };
        const int blockPosOffsets[4] = {-width, width, -1, 1}; //  下, 上, 左, 右
        int checkPosOffsets[4] = {-0x10000, 0x10000, -1, 1};

        for (int i = 0; i < 4; i++)
        {
            if (checkBoolList[i])
            {
                //--- 对应格子的各种信息
                int newPos = pos + blockPosOffsets[i];
                block = &mapBlocks[newPos];
                checkPosNew.xy.value = (uint32_t) ((int) checkPos.xy.value + checkPosOffsets[i]);
                //

                int addVal = 10;

                if (block->inpassable == 1)
                {
                    continue;
                }

                int newVal = now + costMap[static_cast<int>(block->blockType)];

                if (flowBlocks[newPos].integration > newVal)
                {
                    flowBlocks[newPos].integration = newVal; //真实存放值
                    count++;
                    checkPosNew.heat = newVal;

                    auto itr = frontQueue.begin();
                    while (itr != frontQueue.end())
                    {
                        //-- 这里优化了 对于有 不同花费时的循环次数:  对热力值进行排序  优先处理热力值小的
                        auto insPos = *itr;
                        if ((int) insPos.heat > newVal)
                        {
                            frontQueue.insert(itr, checkPosNew);
                            break;
                        }
                        itr++;
                    }


                    if (itr == frontQueue.end())
                    {
                        frontQueue.push_back(checkPosNew);
                    }
                }
            }
        }
    }

    flowBlocks[16].integration = 34;
    auto countP = PLabel::createWithTTF(std::to_string(count), "fonts/SiYuanSongTi.otf", 18);
    countP->setPosition(Vec2(32 * (width + 2), -50));
    countP->setTextColor(Color4B::BLACK);
    heatDebugNode->addChild(countP);

    auto wcountP = PLabel::createWithTTF(std::to_string(whileCount), "fonts/SiYuanSongTi.otf", 18);
    wcountP->setPosition(Vec2(32 * (width + 2), -50 - 32));
    wcountP->setTextColor(Color4B::BLACK);
    heatDebugNode->addChild(wcountP);
}

void GameMap::generateVectorMap(int id) {
    std::unordered_map<int,std::string> arrowMap =
    {
        {2,u8"上"},
        {6,u8"下"},
        {4,u8"右"},
        {8,u8"左"},
    };
    int posList[] = {0, 0, -width, 0, 1, 0, width, 0, -1, 0};
    const char noDiagCheckAll[] = {2, 4, 6, 8, 0};
    const char* noDiagcheckPattern[] = {noDiagCheckAll};


    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            int pos = y * width + x;
            int heatVal = flowBlocks[pos].integration;


            if(heatVal == 65535)
            {
                continue;
            }

            int checkIndex = 0;
            const char* checkList = noDiagcheckPattern[checkIndex];

            int i = 0;

            int tempCost = 100;  //越低越优先
            while(checkList[i] != 0)
            {
                int newPos = pos + posList[checkList[i]];

                //--- 防越界
                if(newPos < 0 || newPos >= width * height)
                {
                    i++;
                    continue;
                }
                //

                //---
                int newHeatVal = flowBlocks[pos + posList[checkList[i]]].integration;
                auto newBlock = &mapBlocks[newPos];
                int newBlockCost = costMap[static_cast<int>(newBlock->blockType)];
                //

                // 新的热力值 < 旧的热力值 ||  热力值 同等时 优先走 格子花销低的
                if(newHeatVal < heatVal || (newHeatVal == heatVal && newBlockCost <= tempCost))
                {
                    flowBlocks[pos].flow = checkList[i];
                    heatVal = newHeatVal;
                    tempCost = newBlockCost;
                }
                i++;
            }

        }
    }
}






























