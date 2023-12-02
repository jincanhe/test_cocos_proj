//
// Created by hejincan on 2023/11/26.
//

#ifndef SZJ_MAINGAME_H
#define SZJ_MAINGAME_H
#define WINDOW
#include "cocos2d.h"
#include "common.h"

USING_NS_CC;

class MainGame : public Node
{

public:
    virtual bool init();

    virtual void update(float dt);
    void initUI();
    void generatePlabelSpr();

    void clear();
    //---

    //--common
    CREATE_FUNC(MainGame);

private:
    std::vector<std::string> plistList;
    std::vector<std::string> imageList;

    Label* sizeLabel;
    Node* node;
};




#endif //hjctest_MAINGAME_H
