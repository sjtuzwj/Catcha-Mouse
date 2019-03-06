#include "cocos2d.h"
#include "RandomableTemplate.h"
#include "AutosetableTemplate.h"
#include "ClickableTemplate.h"
#include "Judge.h"

void AutosetableTemplate::autoset(std::shared_ptr<Graph>& graph)
{
    int next = Judge::getInstance().judgeClosestPos(graph);//最短路径
    if (nextIndexIllegal(graph, next))//检测合法性
        next = doWithIllegalNextIndex(graph);//处理异常
    doWithNextIndex(graph, next);//根据最短路径索引做出行为
}

bool ClickableTemplate::click(std::shared_ptr<Graph>& graph, cocos2d::EventMouse *event)
{
    auto index = Judge::getInstance().judgeClickPos(event, graph);//点击索引
    if (clickIndexIllegal(graph, index))return false;//检测合法性
    doWithClickIndex(graph, index);//根据点击做出行为
    return true;
}

void RandomableTemplate::random(std::shared_ptr<Graph>& graph) {
    int index = getRandomIndex(graph);//获取随机索引
    doWithRandomIndex(graph, index);//根据随即索引进行行动
}