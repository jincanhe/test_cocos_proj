//
// Created by hejincan on 2023/11/26.
//
#include "MainGame.h"
#include "TestClass.h"
#include <iostream>

#include "InputManager.h"
#include "ResManager.h"
#include "GameMap.h"
#include "BaseView.h"
#include <bitset>
#include "WsManager.h"


#include <fstream>
#include <sstream>
#include <vector>
#include "cocos2d.h"
#include "Common.h"

union n1 {
    int x;
    uint8_t y;
};

union n2 {
    struct n2_struct {
        uint16_t x;
        uint8_t y;
        uint16_t z;
        uint8_t y1;
        int x2 ;
        uint8_t z1;
        uint8_t z22;

    };

    int g;
};

union testunion {
    unsigned char bits[4];
    int num;
    uint8_t u8t[4];
}t;


struct S{
    std::string s_;
    S(std::string s) :s_(s) {}

    S(const S& rhs) :s_(rhs.s_) {}
    S& operator=(const S& rhs) { s_ = rhs.s_; return *this; }
};


int index = 1;

int framesize = 12;
bool MainGame::init() {
    plistList = {
        "plist/farmT.plist",
        "plist/laohu.plist",
        "plist/magic.plist",
    };
    imageList = {
        "image/maingame.txt",
    };

    ResManager::getInstance()->loadres(plistList, imageList);
    initUI();
    generateDebugInfo();
    scheduleUpdate();
    return true;
}

void MainGame::animStateUpdate(float dt) {
    animDt += dt;
    currentAnimFrame = (int)(animDt * framesize) % framesize;

    if(!playerSpr_1)
    {


        std::vector<Vec2> offsetposMap2 = { Vec2(93 ,129),
            Vec2(98,129),
            Vec2(101,129),
            Vec2(101,128),
            Vec2(98,129),
            Vec2(92,129),
            Vec2(86,130),
            Vec2(82,130),
            Vec2(79,130),
            Vec2(81,130),
            Vec2(85,130),
            Vec2(89,130),
        };

        auto visibleSize = Director::getInstance()->getVisibleSize();
        playerSpr = Sprite::createWithSpriteFrame(idleFrame[0]);
        playerSpr->setAnchorPoint(Vec2(0, 1));

        playerSpr->setPositionX(offsetposMap2[0].x);
        playerSpr->setPositionY(400 - offsetposMap2[0].y);


        playerSpr_1 = Sprite::create();
        playerSpr_1->setAnchorPoint(Vec2(0,1));

        this->addChild(playerSpr_1);
        this->addChild(playerSpr);


    }

    //
    std::vector<Vec2> offsetposMap = { Vec2(162,135),
        Vec2(165,135),
        Vec2(165,134),
        Vec2(163,134),
        Vec2(162,134),
        Vec2(161,134),
        Vec2(161,134),
        Vec2(162,135),
        Vec2(163,135),
        Vec2(161,135),
        Vec2(160,136),
        Vec2(161,135),
    };


    std::vector<Vec2> offsetposMap2_1 = { Vec2(162,126),
        Vec2(165,126),
        Vec2(166,126),
        Vec2(164,126),
        Vec2(162,125),
        Vec2(163,125),
        Vec2(166,126),
        Vec2(166,126),
        Vec2(164,127),
        Vec2(161,127),
        Vec2(160,127),
        Vec2(161,127),
    };


    std::vector<Vec2> offsetposMap2_2 = {
        Vec2(93,123),
    Vec2(98,122),
    Vec2(101,122),
    Vec2(101,122),
    Vec2(98,122),
    Vec2(101,122),
    Vec2(101,122),
    Vec2(98,122),
    Vec2(92,122),
    Vec2(86,122),
    Vec2(82,123),
    Vec2(80,123),
    Vec2(81,123),
    Vec2(85,123),
    Vec2(89,123),

};


    std::vector<Vec2> offsetposMap2 = { Vec2(93 ,129),
        Vec2(98,129),
        Vec2(101,129),
        Vec2(101,128),
        Vec2(98,129),
        Vec2(92,129),
        Vec2(86,130),
        Vec2(82,130),
        Vec2(79,130),
        Vec2(81,130),
        Vec2(85,130),
        Vec2(89,130),
    };


    auto framec = idleFrame[currentAnimFrame];
    playerSpr_1->setSpriteFrame(framec);
    playerSpr_1->setPositionX(offsetposMap2[currentAnimFrame].x );
    playerSpr_1->setAnchorPoint(Vec2(0,1));
    playerSpr_1->setPositionY(400 - offsetposMap2[currentAnimFrame].y);


    playerSpr->setSpriteFrame(guangquan[currentAnimFrame > 7 ? 7 : currentAnimFrame]);
    playerSpr->setPositionX(HXoffsetMap[564][currentAnimFrame > 7 ? 7 : currentAnimFrame].x );
    playerSpr->setAnchorPoint(Vec2(0,1));
    playerSpr->setPositionY(400 -HXoffsetMap[564][currentAnimFrame > 7 ? 7 : currentAnimFrame].y );


}

void MainGame::update(float dt) {

	// animStateUpdate(dt);

    updateDebugInfo();

    if (InputManager::getInstance()->getKeyPress(EventKeyboard::KeyCode::KEY_SPACE)) {
        // CCLOG("key_space");
        // WsManager::getInstance()->disconnect();

            if(framesize == 12)
            {
                framesize= 4;
            }else
            {
                framesize++;
            }

        return;

        for(int i = 0 ; i <= 12; i++)
        {
            char buf[256];
            sprintf(buf,"%d_%d.png",index,i+1);
            idleFrame[i] = SpriteFrameCache::getInstance()->getSpriteFrameByName(buf);
            index++;
        }
    }

    if (InputManager::getInstance()->getKeyPress(EventKeyboard::KeyCode::KEY_B)) {
        plableSpr->setVisible(!plableSpr->isVisible());
        this->addChild(PLabel::create(std::to_string(index),28));
        index ++;
        CCLOG("key_B");
    }

    if (InputManager::getInstance()->getKeyPress(EventKeyboard::KeyCode::KEY_Z)) {
        ResManager::getInstance()->loadres(plistList, imageList);

    }

    if (InputManager::getInstance()->getKeyPress(EventKeyboard::KeyCode::KEY_X)) {
        node->removeAllChildrenWithCleanup(true);
    }

    InputManager::getInstance()->update(dt);
}

void MainGame::loadAnim() {
    for(int i = 0 ; i < 12; i++)
    {
        char buf[256];
        sprintf(buf,"2_%d.png",i+1);
        idleFrame[i] = SpriteFrameCache::getInstance()->getSpriteFrameByName(buf);

        sprintf(buf,"1_%d.png",i+1);
        idleFrame_1[i] = SpriteFrameCache::getInstance()->getSpriteFrameByName(buf);
        idleFrameName.push_back(buf);

        sprintf(buf,"564_%d.png",i+1);
        guangquan[i] = SpriteFrameCache::getInstance()->getSpriteFrameByName(buf);
    }
}

void MainGame::initUI() {

    // loadAnim();

    test();
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    visibleSize.width += origin.x;
    visibleSize.height += origin.y;

    auto mainSpr = Sprite::create("image/maingame/main_bg.png");
    mainSpr->setAnchorPoint(Vec2(0.5, 0.5));
    mainSpr->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    this->addChild(mainSpr);


    node = Node::create();
    this->addChild(node);

    auto label_1 = PLabel::createWithTTF("PLabel测试", "fonts/SiYuanSongTi.otf", 26);
    label_1->setPositionY(visibleSize.height / 2 + 20);
    label_1->setPositionX(visibleSize.width / 2);
    label_1->setTextColor(Color4B::BLACK);
    label_1->setVisible(false);
    this->addChild(label_1);

    auto gamemap = GameMap::create();
    gamemap->setPosition(Vec2(0, visibleSize.height));
    this->addChild(gamemap, 6666);


    // WsManager::getInstance()->connect();

}

void MainGame::generateDebugInfo() {
    auto visibleSize = Director::getInstance()->getVisibleSize();

    plableSpr = PLabel::getTestSprite();
    plableSpr->setAnchorPoint(Vec2(0.f,1.f));
    plableSpr->setPositionY(visibleSize.height);    plableSpr->setPositionX(visibleSize.width - 200.f);
    plableSpr->setVisible(false);
    this->addChild(plableSpr);


    debugLable = PLabel::createWithTTF("", "fonts/SiYuanSongTi.otf", 18);
    debugLable->setColor(Color3B(0,0,155));
    debugLable->setAnchorPoint(Vec2(1,1));
    debugLable->setPositionY(visibleSize.height);
    debugLable->setPositionX(visibleSize.width);

    debugLable->setTextColor(Color4B::WHITE);
    this->addChild(debugLable);
}

void MainGame::updateDebugInfo() {
    // char buf[256];
    // sprintf(buf,"%f mb",getCurrentMemoryUsage() * 0.000001f);
    // debugLable->setString(buf);
}


void MainGame::clear() {
    ResManager::getInstance()->unloadres(plistList, imageList);
}


void MainGame::test() {
    auto dog = new Dog();
    dog->jiao();

    delete dog;

    loadOffsetTxt();


}

void MainGame::loadOffsetTxt() {

   loadOffset();

}
