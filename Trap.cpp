#include "Trap.h"
#include "Mouse.h"
#include "cocos2d.h"
#include "Prototype.h"
#include "CreateItem.h"
#include "Setting.h"
#include "Hexagon.h"
#include "Model.h"
#include "RecordOriginator.h"
#include "Judge.h"
#include "Graph.h"
#include "MainScene.h"
USING_NS_CC;

/////////////////////////////
////Click
///////////////////////////
bool Trap::clickIndexIllegal(std::shared_ptr<Graph>& graph, int index)
{
    return index == -1 || !graph->isempty(index);
}

void Trap::doWithClickIndex(std::shared_ptr<Graph>& graph, int index)
{
    create(graph, index);
}

////////////////////////////////
//////Autoset
/////////////////////////////////
bool Trap::nextIndexIllegal(std::shared_ptr<Graph>& graph, int next) {
    return next == -1|| graph->ishole(next);
}

int Trap::doWithIllegalNextIndex(std::shared_ptr<Graph>& graph) {
    return Judge::getInstance().judgeRandomPos(graph);
}

void Trap::doWithNextIndex(std::shared_ptr<Graph>& graph, int next) {
    create(graph, next);
}