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

DrawNode* drawNode;
bool MainGame::init() {
    plistList = {
        "plist/farmT.plist",
//        "plist/laohu.plist",
//        "plist/magic.plist",
    };
    imageList = {
        "image/maingame.txt",
    };

    ResManager::getInstance()->loadres(plistList, imageList);
    initUI();
    generateDebugInfo();
    scheduleUpdate();


    EventListenerKeyboard* keyboradListener;
    keyboradListener = EventListenerKeyboard::create();
    keyboradListener->onKeyReleased = CC_CALLBACK_2(MainGame::onKeyReleased,this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(keyboradListener,1);



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


//    if (InputManager::getInstance()->getKeyPress(EventKeyboard::KeyCode::KEY_B)) {
//        plableSpr->setVisible(!plableSpr->isVisible());
//        this->addChild(PLabel::create(std::to_string(index),28));
//        index ++;
//        CCLOG("key_B");
//    }
//
//    if (InputManager::getInstance()->getKeyPress(EventKeyboard::KeyCode::KEY_Z)) {
//        ResManager::getInstance()->loadres(plistList, imageList);
//
//    }
//
//    if (InputManager::getInstance()->getKeyPress(EventKeyboard::KeyCode::KEY_X)) {
//        node->removeAllChildrenWithCleanup(true);
//    }

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

    return;

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

void MainGame::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, Event *event) {
    if (keyCode == EventKeyboard::KeyCode::KEY_SPACE) {
        if(!drawNode)
        {
            drawNode = DrawNode::create();
            this->addChild(drawNode);
        }else{
              drawNode->removeFromParentAndCleanup(true);
            drawNode = nullptr;
        }


    }

    if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE) {


        Vec2 vertices[] = {
                Vec2(0, 0),
                Vec2(0, 100),
                Vec2(100, 100),
                Vec2(100, 0)
        };

        Tex2F texCoords[] = {
                Tex2F(0, 0),
                Tex2F(0, 1),
                Tex2F(1, 1),
                Tex2F(1, 0)
        };

        unsigned short indices[] = {0, 1, 2, 3};


        //1、先生成quads
        PolygonInfo tempInf;
        std::unordered_map<int, V3F_C4B_T2F_Quad> quads;
        V3F_C4B_T2F_Quad target;
        char buf[256];
        sprintf(buf, "farmT_%d.png", 1);


        for (int i = 0; i < 1; i++){
            float x = 0;
            float y = i;
            auto sprFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(buf);
            auto texRect = sprFrame->getRectInPixels();
            auto texWidth = sprFrame->getTexture()->getPixelsWide();
            auto texHeight = sprFrame->getTexture()->getPixelsHigh();

            target.tl.vertices = Vec3(x * 32.0f, y * -32.0f, 0.0f);
            target.tr.vertices = Vec3((x + 1) * 32.0f + 1.0f, y * -32.0f, 0.0f);
            target.bl.vertices = Vec3(x * 32.0f, (y + 1) * -32.0f - 1.0f, 0.0f);
            target.br.vertices = Vec3((x + 1) * 32.0f + 1.0f, (y + 1) * -32.0f - 1.0f, 0.0f);

            target.tl.texCoords = Tex2F((texRect.getMinX() + 1.0f) / texWidth, (texRect.getMinY() + 1.0f) / texHeight);
            target.tr.texCoords = Tex2F((texRect.getMaxX() - 1.0f) / texWidth, (texRect.getMinY() + 1.0f) / texHeight);
            target.bl.texCoords = Tex2F((texRect.getMinX() + 1.0f) / texWidth, (texRect.getMaxY() - 1.0f) / texHeight);
            target.br.texCoords = Tex2F((texRect.getMaxX() - 1.0f) / texWidth, (texRect.getMaxY() - 1.0f) / texHeight);

            target.tl.colors = Color4B::WHITE;
            target.tr.colors = Color4B::WHITE;
            target.bl.colors = Color4B::WHITE;
            target.br.colors = Color4B::WHITE;
            quads[i] = target;

            Texture2D* texture = sprFrame->getTexture();
            tempInf.setFilename(texture->getPath());
        }
        //2、通过quads generateSprite
        tempInf.triangles.vertCount = quads.size() * 4;
        tempInf.triangles.indexCount = quads.size() * 6;
        tempInf.triangles.verts = new V3F_C4B_T2F[tempInf.triangles.vertCount]; //每个顶点的数据
        tempInf.triangles.indices = new unsigned short[tempInf.triangles.indexCount]; //索引


        int currentVert = 0;
        int currentIndex = 0;

        for (auto& vert4: quads){
            int x = vert4.first % 100;
            int y = vert4.first / 100;

            memcpy(&tempInf.triangles.verts[currentVert], &vert4.second, sizeof(V3F_C4B_T2F_Quad));

            tempInf.triangles.indices[currentIndex + 0] = currentVert + 0;
            tempInf.triangles.indices[currentIndex + 1] = currentVert + 1;
            tempInf.triangles.indices[currentIndex + 2] = currentVert + 2;
            tempInf.triangles.indices[currentIndex + 3] = currentVert + 3;
            tempInf.triangles.indices[currentIndex + 4] = currentVert + 2;
            tempInf.triangles.indices[currentIndex + 5] = currentVert + 1;

            currentVert += 3;
            currentIndex += 6;
        }

        //quad -> vbo
        //indices -> ebo
        auto spr = Sprite::create(tempInf);
        spr->setPositionX(228.f);
        spr->setPositionY(228.f);
        this->addChild(spr);


    }

    if (keyCode == EventKeyboard::KeyCode::KEY_B) {
        for (int i = 0; i < 5; ++i) {
//            drawNode->drawTriangle(Vec2(228.f, 128.f), Vec2(260.f,128.f),Vec2(300.f,200.f), Color4F::YELLOW);
            drawNode->drawLine(Vec2(228.f + i * 10, 128.f + i * 10), Vec2(260.f + i * 10,128.f + i * 10), Color4F::YELLOW);
        }
    }

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
