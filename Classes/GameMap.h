//
// Created by hejincan on 2023/12/3.
//

#ifndef GAMEMAP_H
#define GAMEMAP_H
#include "cocos2d.h"

USING_NS_CC;

class GameMap : public Layer {
    enum class BlockType : uint8_t {
        MAP_VOID,
        MAP_POS,
        MAP_ROAD,
        MAP_GLASS,
    };


    union XYCheck {
        uint32_t value;

        struct {
            int16_t x;
            int16_t y;
        };

        // XYCheck() : value(0) {}
        // XYCheck(int xIn, int yIn) : x(xIn), y(yIn) {}
        // XYCheck(uint32_t valueIn) : value(valueIn) {}
        // XYCheck(XYCheck& valueIn) : value(valueIn.value) {}
        // operator uint32_t() const { return value; }
    };

    union HeatFront {
        uint64_t value;

        struct {
            uint32_t heat;
            XYCheck xy;
        };

        HeatFront() : value(0) {
        }

        HeatFront(uint64_t valueIn) : value(valueIn) {
        }

        HeatFront(HeatFront& valueIn) : value(valueIn.value) {
        }

        operator uint64_t() const { return value; }
    };


    struct FlowBlock {
        uint32_t integration: 24;
        uint32_t flow: 8;
    };


    struct MAPBLOCK {
        uint8_t inpassable: 1;
        BlockType blockType: 6;
        uint8_t cost;
        // MAPBLOCK(const uint8_t i) : inpassable(i){};
    };

    struct MAPBLOCK1 {
        std::string s;
        int a;
        int c;
        uint8_t d;
    };

public:
    virtual bool init();

    void setBlocks();

    void bindEvents();

    void initUI();

    MAPBLOCK* getMapBlock(int x, int y);

    void drawMap();

    void clearHeatMap();

    void drawHeatMap();

    void generateHeatMap(int startX, int startY);

    void generateVectorMap(int id);

    CREATE_FUNC(GameMap);

private:
    std::vector<std::string> plistList;
    std::vector<std::string> imageList;
    int width;
    int height;
    MAPBLOCK* mapBlocks;

    FlowBlock* flowBlocks;
    DrawNode* tileIndicator;
    DrawNode* debugDrawNode;
    Node* heatDebugNode;
};

#endif //GAMEMAP_H
