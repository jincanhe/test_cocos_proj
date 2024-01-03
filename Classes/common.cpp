//
// Created by hejincan on 2023/12/1.
//

#include "common.h"
#include "WinSock2.h"
#include "winsock.h"
#include <Windows.h>
#include <Psapi.h>
#include <cocostudio/CCProcessBase.h>
#include "minwindef.h"
#include <stdbool.h>

std::vector<std::string> splitStringByDelimiter(const std::string& inputString, const std::string& delimiter) {
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
    outputVector.push_back(s);
    return outputVector;
}

size_t getCurrentMemoryUsage() {
    PROCESS_MEMORY_COUNTERS ppsmemCounters;
    ppsmemCounters.cb = sizeof(PROCESS_MEMORY_COUNTERS);

    GetProcessMemoryInfo(GetCurrentProcess(), &ppsmemCounters, ppsmemCounters.cb);

    return ppsmemCounters.WorkingSetSize;
}
