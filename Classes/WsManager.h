//
// Created by 59822 on 2023/12/13.
//

#ifndef WSMANAGER_H
#define WSMANAGER_H
#include <mutex>
#include <queue>
#include "network/WebSocket.h"
#include "cocos2d.h"
#include "zlib.h"

USING_NS_CC;

class WsManager : public network::WebSocket::Delegate {
    network::WebSocket* ws = nullptr;
public:
    static WsManager* instance;
    static WsManager* getInstance();

    void onOpen(network::WebSocket* ws) override;

    void onMessage(network::WebSocket* ws, const network::WebSocket::Data& data) override;

    void onClose(network::WebSocket* ws) override;

    void onError(network::WebSocket* ws, const network::WebSocket::ErrorCode& error) override;

    void connect();
    void disconnect();
};

#endif //WSMANAGER_H
