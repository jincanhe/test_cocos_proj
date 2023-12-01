//
// Created by 59822 on 2023/11/30.
//

#include "Sprite_Blur.h"
#include "renderer/backend/Device.h"

#define SET_UNIFORM(ps, name, value)  do {   \
decltype(value) __v = value;                           \
auto __loc = (ps)->getUniformLocation(name);  \
(ps)->setUniform(__loc, &__v, sizeof(__v));  \
} while(false)

#define SET_TEXTURE(ps, name, idx, value)  do {   \
auto * __v = value;                           \
auto __loc = (ps)->getUniformLocation(name);  \
(ps)->setTexture(__loc, idx, __v);  \
} while(false)


SpriteBlur::~SpriteBlur()
{

}

SpriteBlur* SpriteBlur::create(const char *pszFileName)
{
    SpriteBlur* pRet = new (std::nothrow) SpriteBlur();
    if (pRet)
    {
        bool result = pRet->initWithFile("");
        log("Test call Sprite::initWithFile with bad file name result is : %s", result ? "true" : "false");
    }

    if (pRet && pRet->initWithFile(pszFileName))
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }

    return pRet;
}

bool SpriteBlur::initWithTexture(Texture2D* texture, const Rect& rect)
{
    _blurRadius = 1;
    if( Sprite::initWithTexture(texture, rect) )
    {
#if CC_ENABLE_CACHE_TEXTURE_DATA
        auto listener = EventListenerCustom::create(EVENT_RENDERER_RECREATED, [this](EventCustom* event){
                initProgram();
            });

        _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
#endif

        initProgram();

        return true;
    }

    return false;
}

void SpriteBlur::initProgram()
{
    std::string fragSource = FileUtils::getInstance()->getStringFromFile(
            FileUtils::getInstance()->fullPathForFilename("Shaders/example_Blur.fsh"));

    auto program = backend::Device::getInstance()->newProgram(positionTextureColor_vert, fragSource.data());
    auto programState = new backend::ProgramState(program);
    setProgramState(programState);
    CC_SAFE_RELEASE(programState);
    CC_SAFE_RELEASE(program);

    auto size = getTexture()->getContentSizeInPixels();

    SET_UNIFORM(_programState, "resolution", size);
    SET_UNIFORM(_programState, "blurRadius", _blurRadius);
    SET_UNIFORM(_programState, "sampleNum", 7.0f);
    SET_UNIFORM(_programState, "u_PMatrix", Director::getInstance()->getMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION));
}

void SpriteBlur::setBlurRadius(float radius)
{
    _blurRadius = radius;
    SET_UNIFORM(_programState, "blurRadius", _blurRadius);
}

void SpriteBlur::setBlurSampleNum(float num)
{
    _blurSampleNum = num;
    SET_UNIFORM(_programState, "sampleNum", _blurSampleNum);
}
