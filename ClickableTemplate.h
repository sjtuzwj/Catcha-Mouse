#pragma once
#include "cocos2d.h"
#include <memory>
class Graph;
class ClickableTemplate
{
public:
    //点击控制行动的模板方法
    bool click( std::shared_ptr<Graph>& graph,cocos2d::EventMouse *event);
protected:
    virtual bool clickIndexIllegal(std::shared_ptr<Graph>& graph, int) = 0;
    virtual void doWithClickIndex(std::shared_ptr<Graph>& graph, int) = 0;
};