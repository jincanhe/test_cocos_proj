//
// Created by hejincan on 2023/11/26.
//
#include "MainGame.h"
#include "InputManager.h"
#include "AppDelegate.h"

bool MainGame::init() {

    initUI();
    generatePlabelSpr();
    scheduleUpdate();
    return true;
}

void MainGame::update(float dt) {
    if(InputManager::getInstance()->getKeyPress(EventKeyboard::KeyCode::KEY_SPACE))
    {
        std::vector<std::string> plistList {"plist/farmT.plist"};

        for (auto& plistName : plistList) {
            SpriteFrameCache::getInstance()->removeSpriteFramesFromFile(plistName);
        }
        CCLOG("key_space");
    }
    InputManager::getInstance()->update(dt);   //要注意与getKeyPress的顺序
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


//    ((AppDelegate*)cocos2d::Application::getInstance())->setResolutionSize(1280,720);
//    auto nvisibleSize = Director::getInstance()->getVisibleSize();
//    mainSpr->setPosition(Vec2(nvisibleSize.width / 2, nvisibleSize.height / 2));

    std::vector<std::string> plistList {"plist/farmT.plist"};

    for (auto& plistName : plistList) {
        SpriteFrameCache::getInstance()->addSpriteFramesWithFile(plistName);
    }

    auto farmSpr = Sprite::createWithSpriteFrameName("farmT_1.png");
    farmSpr->setAnchorPoint(Vec2(0.5,0.5));
    farmSpr->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    this->addChild(farmSpr);


    addTextureCache("texture/maingame/maingame_1.png");


    auto cloudSpr = Sprite::createWithSpriteFrameName("texture/maingame/maingame_1.png");
    cloudSpr->setAnchorPoint(Vec2(0.5,0.5));
    cloudSpr->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    this->addChild(cloudSpr);


    //    std::vector<std::string> listFonts = FileUtils::getInstance()->listFiles("spine");
    // todo 加载整个文件夹的文件
}

void MainGame::generatePlabelSpr() {

    auto visibleSize = Director::getInstance()->getVisibleSize();

    auto spr = PLabel::getTestSprite();
    spr->setAnchorPoint(Vec2(0.,1.f));
    spr->setPositionY(visibleSize.height);
    this->addChild(spr);
}

void MainGame::addTextureCache(std::string path) {

    if (FileUtils::getInstance()->isFileExist(path))
    {
        SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(path);
        if (frame == nullptr)
        {
            Texture2D* texture = Director::getInstance()->getTextureCache()->addImage(path);
            Rect rect = Rect::ZERO;
            rect.size = texture->getContentSize();
            frame = SpriteFrame::createWithTexture(texture, rect);
            frame->setAnchorPoint(Vec2(0.5, 0.5));
            SpriteFrameCache::getInstance()->addSpriteFrame(frame, path);
            CCLOG("addTexture : %s", path.c_str());
        }
    }else{
        CCLOG("not find :%s", path.c_str());
    }

}

void MainGame::addTexturCache(std::vector<std::string> pathList) {
    for (auto& path: pathList) {
        addTextureCache(path);
    }
}

void MainGame::removeTextureCache(std::string path) {

    if (FileUtils::getInstance()->isFileExist(path))
    {
        SpriteFrameCache::getInstance()->removeSpriteFrameByName(path);
        Director::getInstance()->getTextureCache()->removeTextureForKey(path);
        CCLOG("removeTexture : %s", path.c_str());
    }

}

void MainGame::removeTextureCache(std::vector<std::string> pathList) {
    for(auto& path : pathList)
    {
        removeTextureCache(path);
    }
}

