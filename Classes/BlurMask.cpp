#include "BlurMask.h"
#include <2d/CCRenderTexture.h>
#include "2d/CCCamera.h"
#include "2d/CCSprite.h"
#include "base/CCDirector.h"
#include "renderer/backend/Device.h"
USING_NS_CC;

RenderTexture* _target;
Camera* camera;
Sprite* sprite;

extern int blurA;
bool BlurMask::init()
{
    // 截图图像是翻转的，所以y轴镜像
    setScaleY(-1);

    _target = RenderTexture::create(680, 400, backend::PixelFormat::RGBA8888);



    static int counter = 0;
    char png[20];
    sprintf(png, "image-pma-%d.png", counter);

    auto callback = [&](RenderTexture* rt, const std::string& path)
    {
        auto sprite = Sprite::create(path);
        addChild(sprite);
        sprite->setScale(0.3f);
        sprite->setPosition(Vec2(40.0f, 40.0f));
        sprite->setRotation(counter * 3);
        _target->release();
    };

    _target->retain();
    _target->saveToFile(png, Image::Format::PNG, true, callback);
    CCLOG("Image saved %s", png);

    // 更新完截图后，增加计数器
    return true;
}

void BlurMask::cull(Node* node)
{
    if (node)
    {
        node->setCameraMask(1 << 31);
        for (auto child : node->getChildren())
        {
            cull(child);
        }
    }
}


void BlurMask::saveImageWithPremultipliedAlpha()
{


    auto s = Director::getInstance()->getWinSize();

    // begin drawing to the render texture
    _target->begin();

    auto sprite = Sprite::create("image/maingame/main_bg.png");
    sprite->setPosition(sprite->getContentSize().width + CCRANDOM_0_1() * (s.width - sprite->getContentSize().width), sprite->getContentSize().height + CCRANDOM_0_1() * (s.height - sprite->getContentSize().height));
    sprite->visit();

    // finish drawing and return context back to the screen
    _target->end();


    static int counter = 0;

    char png[20];
    sprintf(png, "image-pma-%d.png", counter);

    auto callback = [&](RenderTexture* rt, const std::string& path)
    {
        auto sprite = Sprite::create(path);
        addChild(sprite);
        sprite->setScale(0.3f);
        sprite->setPosition(Vec2(40.0f, 40.0f));
        sprite->setRotation(counter * 3);
        _target->release();
    };

    _target->retain();
    _target->saveToFile(png, Image::Format::PNG, true, callback);
    //Add this function to avoid crash if we switch to a new scene.
    Director::getInstance()->getRenderer()->render();
    CCLOG("Image saved %s", png);

    counter++;
}


void BlurMask::snapshot(float dt)
{
    // // 手动渲染摄影机，保存截图
    // auto director = Director::getInstance();
    // director->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION);
    // director->loadIdentityMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION);
    // director->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    // director->loadIdentityMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    // director->setCullingEnabled(false);
    // director->setDepthTest(true);
    // camera->render();
    // director->setDepthTest(false);
    // director->setCullingEnabled(true);
    // director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    // director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION);
    //
    // // 应用刚刚截图的贴图到sprite身上进行渲染
    // sprite->setTexture(texture);
    // sprite->setTextureRect(Rect(Vec2::ZERO, getContentSize()));
}

void BlurMask::setBrightness(float brightness)
{
    // this->brightness = brightness;
    // sprite->getBlendFunc().src = backend::BlendFactor::SRC_ALPHA;
    // sprite->getBlendFunc().dst = backend::BlendFactor::ONE_MINUS_SRC_ALPHA;
    // sprite->setOpacity(brightness * 255);
}

void BlurMask::setBlurAmount(float blurAmount)
{
    // this->blurAmount = blurAmount;
    // sprite->getBlendFunc().src = backend::BlendFactor::ONE;
    // sprite->getBlendFunc().dst = backend::BlendFactor::ONE;
    // sprite->setOpacity(blurAmount * 255);
}