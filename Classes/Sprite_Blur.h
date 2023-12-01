//
// Created by 59822 on 2023/11/30.
//

#ifndef CPP_TESTS_SPRITE_BLUR_H
#define CPP_TESTS_SPRITE_BLUR_H

#include "cocos2d.h"

USING_NS_CC;

class SpriteBlur : public Sprite
{
public:
    ~SpriteBlur();
    bool initWithTexture(Texture2D* texture, const Rect&  rect);
    void initProgram();

    static SpriteBlur* create(const char *pszFileName);
    void setBlurRadius(float radius);
    void setBlurSampleNum(float num);

protected:
    float _blurRadius = 0.7;
    float _blurSampleNum;
};



#endif //CPP_TESTS_SPRITE_BLUR_H
