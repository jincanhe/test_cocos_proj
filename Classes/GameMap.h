//
// Created by hejincan on 2023/12/3.
//

#ifndef GAMEMAP_H
#define GAMEMAP_H
#include "cocos2d.h"

USING_NS_CC;

class GameMap : public Layer{

enum class BlockType : uint8_t {
    MAP_VOID,
    MAP_POS,
};

struct MAPBLOCK {
    uint8_t inpassable : 1;
    BlockType blockType : 6;
    uint8_t lock : 1;
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
    MAPBLOCK* getMapBlock(int x, int y);


    CREATE_FUNC(GameMap);

private:
    std::vector<std::string> plistList;
    std::vector<std::string> imageList;
    int width;
    int height;
    MAPBLOCK* mapBlocks;


};

#endif //GAMEMAP_H
