//
// Created by 59822 on 2023/12/4.
//

#include "BaseView.h"
#include "cocos/editor-support/cocostudio/ActionTimeline/CSLoader.h"

bool BaseView::init() {
    std::string csbName = "csb/NewNewTaskView.csd";
    if (csbName != "") {
        auto root = CSLoader::createNode(csbName);
        if (root) {
            root->setPosition(0, 0);
        }

       auto node =  Node::create();
        node->addChild(root);
        this->serializeChild(node);

    }
    return true;
}

BaseView::BaseView() {
}

BaseView::~BaseView() {
}

void BaseView::serializeChild(Node* node) {

    auto root = node;
    auto root_name = node->getName();
    auto root_type = node->getDescription();
}