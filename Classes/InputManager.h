//
// Created by 59822 on 2023/11/27.
//

#ifndef SZJ_INPUTMANAGER_H
#define SZJ_INPUTMANAGER_H

#include "cocos2d.h"
USING_NS_CC;

class InputManager
{
public:
    static InputManager* inst;
    static InputManager* getInstance();
    void init();
    void update(float dt);
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, Event* event);
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, Event* event);
    void schedule();

    bool getKeyDown(cocos2d::EventKeyboard::KeyCode keyCode);
    bool getKeyPress(cocos2d::EventKeyboard::KeyCode keyCode);
    bool getKeyHold(cocos2d::EventKeyboard::KeyCode keyCode);
    bool getKeyRelease(cocos2d::EventKeyboard::KeyCode keyCode);

    EventListenerKeyboard* keyboradListener;
    uint8_t keyboardThisframe[256];
    uint8_t keyboardlastFrame[256];

};

#endif //SZJ_INPUTMANAGER_H
