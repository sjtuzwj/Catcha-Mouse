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
    attach(dynamic_pointer_cast<Observer>(graph));//רΪ����ָ����ƵĶ�ָ̬��ת��,Fantasy!
    auto num = Judge::getInstance().judgeWhich();
    sprite = ItemFunction::createSprite(model.msg + std::to_string(num));//��ͼ�ο��й�
    model.index = index;
    model.pos = graph->pos(model.index);
    setState(model.msg,model.index);
    sprite->setPosition(Vec2(model.pos.first, model.pos.second));//��ͼ�ο��й�
    return sprite;
}

void Prototype::destroy()
{
    sprite->removeFromParentAndCleanup(true);//��ͼ�ο��й�
    setState('r'+model.msg,model.index);
}

//�ӿ�ָ��ָ��ʵ����
std::shared_ptr<PrototypeInterface> Prototype::create(char* msg)
{
    PrototypeInterface *ptr = dynamic_cast<PrototypeInterface*>(new Prototype(msg));
    return std::shared_ptr<PrototypeInterface>(ptr);
}

void Prototype::notify() {
    for (auto &x : observer) x->update(this);
};