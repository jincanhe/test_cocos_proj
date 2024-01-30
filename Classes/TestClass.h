#include "cocos2d.h"
#include "ui/UIWidget.h"
// Created by 59822 on 2024/1/2.
//

#ifndef TESTCLASS_H
#define TESTCLASS_H


class View1 : public cocos2d::ui::Widget{

public:
    int view1_num;
};

class View2 : public cocos2d::ui::Widget {
public:
    int view2_num;
};


class Animal {
public:
    Animal(){CCLOG("Animal");};
    virtual ~Animal(){ CCLOG("~Animal");};
    virtual void jiao(){ CCLOG("animal: jiao");};
};

class Dog : Animal {
public:
    Dog(){CCLOG("dog");};
    ~Dog() override { CCLOG("~dog");};
    void jiao() override { CCLOG("dog: jiao");};
};

#endif //TESTCLASS_H
