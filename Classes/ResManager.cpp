#include "ResManager.h"
#include "common.h"

ResManager* ResManager::inst = nullptr;

ResManager* ResManager::getInstance() {
        if(inst == nullptr)
        {
            inst = new ResManager();
        }
        return inst;
}

void ResManager::addTextureCache(const std::vector<std::string>& pathList) {
        for (auto& path: pathList) {
            if(path == "")
            {
                continue;
            }
        if (FileUtils::getInstance()->isFileExist(path))
        {
            if (!SpriteFrameCache::getInstance()->checksfCache(path))
            {
                Texture2D* texture = Director::getInstance()->getTextureCache()->addImage(path);
                Rect rect = Rect::ZERO;
                rect.size = texture->getContentSize();
                SpriteFrame* frame = SpriteFrame::createWithTexture(texture, rect);
                frame->setAnchorPoint(Vec2(0.5, 0.5));
                SpriteFrameCache::getInstance()->addSpriteFrame(frame, path);
                CCLOG("--resManager addTexture: %s", path.c_str());

            }
        }else{
            CCLOG("--resManager not find: %s", path.c_str());
        }
    }
}

void ResManager::removeTextureCache(const std::vector<std::string>& pathList) {
    for(auto& path : pathList)
    {
        if (FileUtils::getInstance()->isFileExist(path))
        {
            SpriteFrameCache::getInstance()->removeSpriteFrameByName(path);
            Director::getInstance()->getTextureCache()->removeTextureForKey(path);
            CCLOG("--resManager removeTexture: %s", path.c_str());
        }
    }
}

void ResManager::loadplist(const std::string& path) {
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile(path);
    CCLOG("--resManager loadplist: %s", path.c_str());
}

void ResManager::unloadplist(const std::string& path) {
    SpriteFrameCache::getInstance()->removeSpriteFramesFromFile(path);
    CCLOG("--resManager unloadplist: %s", path.c_str());


    auto pngName = splitStringByDelimiter(path,".")[0];
    char buf[256];
    sprintf(buf, "%s.png", pngName.c_str());
     removeTextureCache(std::vector<std::string>{buf} );
}

void ResManager::loadres(const std::vector<std::string>& plistList, const std::vector<std::string>& imageList) {
    for (auto &plist_name: plistList) {
        loadplist(plist_name);
    }

    for (auto &image_fileName: imageList) {
        auto imageList = FileUtils::getInstance()->getStringFromFile(image_fileName);
        auto res = splitStringByDelimiter(imageList, "\r\n");
        addTextureCache(res);
    }

}

void ResManager::unloadres(const std::vector<std::string>& plistList, const std::vector<std::string>& imageList) {


    for (auto &image_fileName: imageList) {
        auto imageList = FileUtils::getInstance()->getStringFromFile(image_fileName);
        auto res = splitStringByDelimiter(imageList, "\r\n");
        removeTextureCache(res);
    }

    for (auto &plist_name: plistList) {
        unloadplist(plist_name);

    }
 }
