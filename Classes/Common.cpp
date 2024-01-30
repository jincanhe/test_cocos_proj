//
// Created by hejincan on 2023/12/1.
//

#include "Common.h"
#include "WinSock2.h"
#include "winsock.h"
#include <Windows.h>
#include <Psapi.h>
#include "minwindef.h"


std::unordered_map<int,std::vector<cocos2d::Vec2>> HXoffsetMap;


std::vector<std::string> splitStringByDelimiter(const std::string& inputString, const std::string& delimiter, bool insertlastSpace) {
    std::string s = inputString;
    std::vector<std::string> outputVector;

    size_t pos = 0;
    std::string token;
    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        outputVector.push_back(token);
        s.erase(0, pos + delimiter.length());
    }

    //需要最后换行可以打开
    if(insertlastSpace)
    {
        outputVector.push_back(s);
    }

    return outputVector;
}


std::vector<std::string> splitStringByChar(const std::string& str, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(str);
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

size_t getCurrentMemoryUsage() {
    PROCESS_MEMORY_COUNTERS ppsmemCounters;
    ppsmemCounters.cb = sizeof(PROCESS_MEMORY_COUNTERS);

    GetProcessMemoryInfo(GetCurrentProcess(), &ppsmemCounters, ppsmemCounters.cb);

    return ppsmemCounters.WorkingSetSize;
}

void loadOffset() {

    auto imageList = cocos2d::FileUtils::getInstance()->getStringFromFile("HXoffset.txt");
    auto res = splitStringByDelimiter(imageList, "\r\n",false);

    for (auto& path : res)
    {
        auto step1 = splitStringByDelimiter(path, "/", true);
        auto step2 = splitStringByDelimiter(step1[1], "_", true);
        int id = atoi(step2[0].c_str());

        auto content = cocos2d::FileUtils::getInstance()->getStringFromFile(path);
        auto rescontent = splitStringByDelimiter(content, "\r\n", false);

        for (auto& pointData : rescontent)
        {
            auto pos = splitStringByChar(pointData,' ');

            HXoffsetMap[id].push_back(cocos2d::Vec2(atof(pos[0].c_str()),atof(pos[1].c_str())));
        }

    }
}

