//
// Created by hejincan on 2023/11/26.
//

#ifndef SZJ_MAINGAME_H
#define SZJ_MAINGAME_H
#define WINDOW
#include "cocos2d.h"
#include "ui/UIImageView.h"


USING_NS_CC;

class MainGame : public Node
{

public:
    virtual bool init();

    void animStateUpdate(float dt);

    virtual void update(float dt);

    void loadAnim();

    void initUI();

    void generateDebugInfo();
    void updateDebugInfo();
    void clear();
    //---

    //--common
    CREATE_FUNC(MainGame);

    //--debug
    void test();

    void loadOffsetTxt();

private:
    std::vector<std::string> plistList;
    std::vector<std::string> imageList;

    Node* node;

    //--debug
    Sprite* plableSpr = nullptr;
    PLabel* debugLable = nullptr;

    int currentAnimFrame = 0;
    float animDt = 0;

    SpriteFrame* idleFrame[12];
    SpriteFrame* idleFrame_1[12];
    SpriteFrame* guangquan[12];
    std::vector<std::string> idleFrameName;
    Sprite* playerSpr;
    Sprite* playerSpr_1;

};




#endif //hjctest_MAINGAME_H
