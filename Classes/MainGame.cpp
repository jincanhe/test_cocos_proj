//
// Created by hejincan on 2023/11/26.
//
#include "MainGame.h"
#include "InputManager.h"
#include "Sprite_Blur.h"
#include "ResManager.h"
#include "GameMap.h"

bool MainGame::init() {
    plistList = {
        "plist/farmT.plist",
    };
    imageList = {
        "image/maingame.txt",
        "image/licheng.txt",
        "image/eggdog.txt",
    };

    ResManager::getInstance()->loadres(plistList, imageList);
    initUI();
    generateDebugInfo();
    scheduleUpdate();
    return true;
}

void MainGame::update(float dt) {
    updateDebugInfo();

    if (InputManager::getInstance()->getKeyPress(EventKeyboard::KeyCode::KEY_SPACE)) {
        clear();
        CCLOG("key_space");
    }

    if (InputManager::getInstance()->getKeyPress(EventKeyboard::KeyCode::KEY_B)) {
        plableSpr->setVisible(!plableSpr->isVisible());
        CCLOG("key_B");
    }

    if (InputManager::getInstance()->getKeyPress(EventKeyboard::KeyCode::KEY_Z)) {

    }

    if (InputManager::getInstance()->getKeyPress(EventKeyboard::KeyCode::KEY_X)) {
        node->removeAllChildrenWithCleanup(true);
    }

    InputManager::getInstance()->update(dt);
}

void MainGame::initUI() {
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
}

void MainGame::generateDebugInfo() {
    auto visibleSize = Director::getInstance()->getVisibleSize();

    plableSpr = PLabel::getTestSprite();
    plableSpr->setAnchorPoint(Vec2(0.f,1.f));
    plableSpr->setPositionY(visibleSize.height);
    plableSpr->setPositionX(visibleSize.width - 200.f);
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
    char buf[256];
    sprintf(buf,"%f mb",getCurrentMemoryUsage() * 0.000001f);
    debugLable->setString(buf);
}


void MainGame::clear() {
    ResManager::getInstance()->unloadres(plistList, imageList);
}
