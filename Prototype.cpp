#pragma once
#include "cocos2d.h"
#include "Prototype.h"
#include "CreateItem.h"
#include "Setting.h"
#include "Hexagon.h"
#include "Model.h"
#include "Observer.h"
#include "Judge.h"
#include "Graph.h"

USING_NS_CC;
Sprite * Prototype:: create(std::shared_ptr<Graph>& graph, int index)
{
    attach(dynamic_pointer_cast<Observer>(graph));//专为智能指针设计的动态指针转换,Fantasy!
    auto num = Judge::getInstance().judgeWhich();
    sprite = ItemFunction::createSprite(model.msg + std::to_string(num));//和图形库有关
    model.index = index;
    model.pos = graph->pos(model.index);
    setState(model.msg,model.index);
    sprite->setPosition(Vec2(model.pos.first, model.pos.second));//和图形库有关
    return sprite;
}

void Prototype::destroy()
{
    sprite->removeFromParentAndCleanup(true);//和图形库有关
    setState('r'+model.msg,model.index);
}

//接口指针指向实现类
std::shared_ptr<PrototypeInterface> Prototype::create(char* msg)
{
    PrototypeInterface *ptr = dynamic_cast<PrototypeInterface*>(new Prototype(msg));
    return std::shared_ptr<PrototypeInterface>(ptr);
}

void Prototype::notify() {
    for (auto &x : observer) x->update(this);
};