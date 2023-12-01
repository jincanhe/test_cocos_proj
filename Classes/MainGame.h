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

    //---
    void addTextureCache(std::string path);
    void addTextureCache(std::vector<std::string> pathList);

    void removeTextureCache(std::string path);
    void removeTextureCache(std::vector<std::string> pathList);

    void loadplist(std::vector<std::string>);
    void unloadplist(std::vector<std::string>);


    //--common
    std::vector<std::string> splitStringByDelimiter(const std::string& inputString, const std::string& delimiter);
    CREATE_FUNC(MainGame); //加了这玩意才会跑init
};



#endif //hjctest_MAINGAME_H
