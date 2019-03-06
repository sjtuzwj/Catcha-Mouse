#include "Hole.h"
#include "Graph.h"
#include "CreateItem.h"
#include "Prototype.h"
#include "Setting.h"
#include "Judge.h"
#include "Model.h"


Sprite * Hole::create(std::shared_ptr<Graph>& graph, int index)
{   
    auto sprite=PrototypeDecorator::create(graph, index);
    sprite->setScale(Setting::getInstance().getSpriteScale());
    return sprite;
}

////////////////////////////////
////////Random
////////////////////////////////////
int  Hole::getRandomIndex(std::shared_ptr<Graph>& graph) {
    return Judge::getInstance().judgeRandomPos(graph);
}

void  Hole::doWithRandomIndex(std::shared_ptr<Graph>& graph, int index) {
    create(graph, index);
}
