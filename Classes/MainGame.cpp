//
// Created by hejincan on 2023/11/26.
//
#include "MainGame.h"

bool MainGame::init() {

    initUI();

    generatePlabelSpr();
    scheduleUpdate();
    return true;
}

void MainGame::update(float dt) {

    int i =1;
}

void MainGame::initUI() {



    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    visibleSize.width += origin.x;
    visibleSize.height += origin.y;


    auto mainSpr = Sprite::create("res/bg/main_bg.png");
    mainSpr->setAnchorPoint(Vec2(0.5,0.5));
    mainSpr->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    this->addChild(mainSpr);



    auto pLabel_1 = PLabel::createWithTTF("PLabel测试test", "fonts/SiYuanSongTi.otf", 20);
    pLabel_1->setPositionY(visibleSize.height / 2);
    pLabel_1->setPositionX(visibleSize.width / 2);
    pLabel_1->setTextColor(Color4B::BLACK);

    auto label_1 = PLabel::createWithTTF("PLabel26测试test", "fonts/SiYuanSongTi.otf", 26);
    label_1->setPositionY(visibleSize.height / 2 + 20);
    label_1->setPositionX(visibleSize.width / 2);
    label_1->setTextColor(Color4B::BLACK);
    label_1->setVisible(false);
    pLabel_1->setVisible(false);
    this->addChild(label_1);
    this->addChild(pLabel_1);

}

void MainGame::generatePlabelSpr() {

    auto visibleSize = Director::getInstance()->getVisibleSize();

    auto spr = PLabel::getTestSprite();
    spr->setAnchorPoint(Vec2(0.,1.f));
    spr->setPositionY(visibleSize.height);
    this->addChild(spr);

}

