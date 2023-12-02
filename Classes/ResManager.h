//
// Created by hejincan on 2023/12/1.
//

#ifndef RESMANAGER_H
#define RESMANAGER_H

#include "cocos2d.h"

USING_NS_CC;

class ResManager {

public:
    static ResManager* inst;
    static ResManager* getInstance();

    //---
    void addTextureCache(const std::vector<std::string>& pathList);
    void removeTextureCache(const std::vector<std::string>& pathList);

    void loadplist(const std::string &path);
    void unloadplist(const std::string &path);

    void loadres(const std::vector<std::string> &plistList, const std::vector<std::string> &imageList);
    void unloadres(const std::vector<std::string> &plistList, const std::vector<std::string> &imageList);




};
#endif //RESMANAGER_H
