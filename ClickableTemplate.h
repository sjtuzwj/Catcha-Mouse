#pragma once
#include "cocos2d.h"
#include <memory>
class Graph;
class ClickableTemplate
{
public:
    //��������ж���ģ�巽��
    bool click( std::shared_ptr<Graph>& graph,cocos2d::EventMouse *event);
protected:
    virtual bool clickIndexIllegal(std::shared_ptr<Graph>& graph, int) = 0;
    virtual void doWithClickIndex(std::shared_ptr<Graph>& graph, int) = 0;
};