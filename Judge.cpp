#include "GameFacade.h"
#include "Mouse.h"
#include "Graph.h"
#include "Setting.h"
#include "Judge.h"
#include "RecordController.h"
#include "RecordOriginator.h"
    USING_NS_CC;
    Judge::Judge() :eng((time(0))), hex(0, 59), whc(1, 3)
    {

    }

    int Judge::judgeWhich()
    {
        return whc(eng);
    }


    int Judge::judgeClickPos(EventMouse *event, std::shared_ptr<Graph> graph)
    {
        auto Pos = event->getLocation();
        auto pos = std::pair<double, double>(Pos.x, 720 - Pos.y);
        return graph->findNearestBlock(pos);
    }

    int Judge::judgeRandomPos(std::shared_ptr<Graph> graph)
    {
        int index = hex(eng);
        while (!graph->isempty(index))index = hex(eng);
        return index;
    }

    int Judge::judgeProperPos(std::shared_ptr<Graph> graph)
    {
        int index,time=0;
        bool permission = false;
        while (!permission)
        {
            index = judgeRandomPos(graph);
            if(graph->findIsolatedBlock(index)||time>100)//找不到孤立节点
                permission = true;
            time++;
        }
        return index;
    }

    int Judge::judgeClosePos(std::shared_ptr<Graph> graph)
    {
        return graph->randomPath();
    }

    int Judge::judgeClosestPos(std::shared_ptr<Graph>graph)
    {
        int next = graph->shortestPath();
        if (next == -1)//老鼠无路可走,隐藏逻辑
            next = Judge::getInstance().judgeClosePos(graph);
        return next;
    }