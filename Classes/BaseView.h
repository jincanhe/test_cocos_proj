//
// Created by 59822 on 2023/12/4.
//

#ifndef BASEVIEW_H
#define BASEVIEW_H

#include "cocos2d.h"

USING_NS_CC;

class BaseView : public Node {

public:
    void serializeChild(Node* node);

    bool init() override;

    BaseView();
    virtual ~BaseView();

    CREATE_FUNC(BaseView);

};

#endif //BASEVIEW_H
