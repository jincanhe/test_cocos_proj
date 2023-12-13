//
// Created by 59822 on 2023/12/4.
//

#ifndef BLURMASK_H
#define BLURMASK_H
#include <CCPlatformMacros.h>
#include <2d/CCNode.h>
#include "cocos2d.h"

USING_NS_CC;

class BlurMask : public Sprite{

public:
    virtual bool init();
    void cull(cocos2d::Node* node);

    void saveImageWithPremultipliedAlpha();

    void snapshot(float dt);
    void setBrightness(float brightness);
    void setBlurAmount(float blurAmount);;
    CREATE_FUNC(BlurMask);


    float blurAmount;
    float brightness;

};

#endif //BLURMASK_H
