//
// Created by hejincan on 2023/11/26.
//
#include "MainGame.h"
#include "InputManager.h"
#include "Sprite_Blur.h"
#include "ResManager.h"
#include "GameMap.h"

bool MainGame::init() {


    plistList =  {
        "plist/farmT.plist",
    };
    imageList = {
        "image/maingame.txt",
    };

    ResManager::getInstance()->loadres(plistList, imageList);
    initUI();
    generatePlabelSpr();
    scheduleUpdate();
    return true;
}

void MainGame::update(float dt) {
    sizeLabel->setString(std::to_string(getCurrentMemoryUsage() * 0.000001f) + " mb");

    if(InputManager::getInstance()->getKeyPress(EventKeyboard::KeyCode::KEY_SPACE)) {
        clear();
        CCLOG("key_space");
    }

    if(InputManager::getInstance()->getKeyPress(EventKeyboard::KeyCode::KEY_B))
    {
        ResManager::getInstance()->loadres(plistList, imageList);


        CCLOG("key_B");
    }

    if(InputManager::getInstance()->getKeyPress(EventKeyboard::KeyCode::KEY_Z))
    {
        node->addChild(Sprite::createWithSpriteFrameName("chr1_axe_d1"));
        node->addChild(Sprite::createWithSpriteFrameName("chr1_axe_d1"));
        node->addChild(Sprite::createWithSpriteFrameName("chr1_axe_d1"));
        node->addChild(Sprite::createWithSpriteFrameName("chr1_axe_d1"));
        node->addChild(Sprite::createWithSpriteFrameName("chr1_axe_d1"));
        node->addChild(Sprite::createWithSpriteFrameName("chr1_axe_d1"));
        node->addChild(Sprite::createWithSpriteFrameName("chr1_axe_d1"));
        node->addChild(Sprite::createWithSpriteFrameName("chr1_axe_d1"));
    }

    if(InputManager::getInstance()->getKeyPress(EventKeyboard::KeyCode::KEY_X))
    {
        node->removeAllChildrenWithCleanup(true);
    }

    InputManager::getInstance()->update(dt);   //ss �?
}

void MainGame::initUI() {

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    visibleSize.width += origin.x;
    visibleSize.height += origin.y;

    auto mainSpr = Sprite::create("image/maingame/main_bg.png");
    mainSpr->setAnchorPoint(Vec2(0.5,0.5));
    mainSpr->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    this->addChild(mainSpr);

    node = Node::create();
    this->addChild(node);
    sizeLabel = Label::createWithTTF("", "fonts/SiYuanSongTi.otf", 20);
    sizeLabel->setPositionY(visibleSize.height - 30.f);
    sizeLabel->setPositionX(visibleSize.width / 2);
    sizeLabel->setTextColor(Color4B::WHITE);
    this->addChild(sizeLabel);

    //auto label_1 = PLabel::createWithTTF("PLabel26娴嬭瘯test", "fonts/SiYuanSongTi.otf", 26);
    //label_1->setPositionY(visibleSize.height / 2 + 20);
    //label_1->setPositionX(visibleSize.width / 2);
    //label_1->setTextColor(Color4B::BLACK);
    //label_1->setVisible(false);
    //pLabel_1->setVisible(false);
    //this->addChild(pLabel_1);



    // auto farmSpr = Sprite::createWithSpriteFrameName("farmT_1.png");
    // farmSpr->setAnchorPoint(Vec2(0.5,0.5));
    // farmSpr->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    // this->addChild(farmSpr);


    auto gamemap = GameMap::create();
    this->addChild(gamemap);

}

void MainGame::generatePlabelSpr() {

    auto visibleSize = Director::getInstance()->getVisibleSize();

    //auto spr = PLabel::getTestSprite();
    //spr->setAnchorPoint(Vec2(0.,1.f));
    //spr->setPositionY(visibleSize.height);
    //this->addChild(spr);
}

void MainGame::clear() {
     ResManager::getInstance()->unloadres(plistList,imageList);
}
