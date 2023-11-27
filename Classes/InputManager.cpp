//
// Created by 59822 on 2023/11/27.
//

#include "InputManager.h"
#include "AppDelegate.h"
InputManager* InputManager::inst = nullptr;

InputManager *InputManager::getInstance() {
    if(inst == nullptr)
    {
        inst = new InputManager();

        inst->keyboradListener = EventListenerKeyboard::create();
        inst->keyboradListener->onKeyPressed = CC_CALLBACK_2(InputManager::onKeyPressed,inst);
        inst->keyboradListener->onKeyReleased = CC_CALLBACK_2(InputManager::onKeyReleased,inst);
        Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(inst->keyboradListener,1);

    }
    return inst;
}

void InputManager::init()
{

}

void InputManager::schedule()
{
    Director::getInstance()->getScheduler()->schedule(CC_CALLBACK_1(InputManager::update, this), this, 1.0f / 60, false, "key");
}


void InputManager::update(float dt) {
    memcpy(keyboardlastFrame, keyboardThisframe, 256);
}

void InputManager::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, Event *event) {
    keyboardThisframe[(uint8_t)keyCode] = 1;
}

void InputManager::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, Event *event) {
    keyboardThisframe[(uint8_t)keyCode] = 0;
}

bool InputManager::getKeyDown(cocos2d::EventKeyboard::KeyCode keyCode) {
    return false;
}

bool InputManager::getKeyPress(cocos2d::EventKeyboard::KeyCode keyCode) {
    if(keyboardThisframe[(uint8_t)keyCode] == 1 && keyboardlastFrame[(uint8_t)keyCode] == 0)
    {
        return true;
    }
    return false;
}

bool InputManager::getKeyHold(cocos2d::EventKeyboard::KeyCode keyCode) {
    return false;
}

bool InputManager::getKeyRelease(cocos2d::EventKeyboard::KeyCode keyCode) {
    return false;
}
