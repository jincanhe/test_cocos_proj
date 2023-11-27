//
// Created by hejincan on 2023/11/26.
//

#ifndef SZJ_MAINGAME_H
#define SZJ_MAINGAME_H

#include "cocos2d.h"

USING_NS_CC;

class MainGame : public Node
{

public:
    virtual bool init();

    virtual void update(float dt);
    void initUI();
    void generatePlabelSpr();
    CREATE_FUNC(MainGame); //加了这玩意才会跑init
};

#endif //hjctest_MAINGAME_H
