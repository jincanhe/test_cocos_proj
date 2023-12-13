//
// Created by 59822 on 2023/12/13.
//

#include "WsManager.h"
WsManager* WsManager::instance = nullptr;

WsManager* WsManager::getInstance() {
    if(instance == nullptr) {
        instance = new WsManager();
    }
    return instance;
}

void WsManager::onOpen(network::WebSocket* ws) {

    CCLOG("onOpen");
}

void WsManager::onMessage(network::WebSocket* ws, const network::WebSocket::Data& data) {

    auto a = 1;
    auto b = 2;
    CCLOG("onMessage");
}

void WsManager::onClose(network::WebSocket* ws) {
    CCLOG("onClose");
}

void WsManager::onError(network::WebSocket* ws, const network::WebSocket::ErrorCode& error) {
    CCLOG("error");
}

void WsManager::connect() {
    if(ws == nullptr) {
        ws = new network::WebSocket();
    }

    // ws->init(*this, "ws://192.168.1.191:8080/api/ws", nullptr, "cacert.pem");  //3 特定协议  4 密钥
    ws->init(*this, "ws://www.10zho.com:2345/api/ws", nullptr, "cacert.pem");  //3 特定协议  4 密钥
}

void WsManager::disconnect() {
    ws->close();
}
