#include "PrototypeDecorator.h"
#include "String"

PrototypeDecorator::PrototypeDecorator(std::shared_ptr<PrototypeInterface> ptr):component(ptr)
{}

Sprite * PrototypeDecorator::create(std::shared_ptr<Graph>& graph, int index)
{
    return component->create(graph, index);
}
void PrototypeDecorator::destroy() {
    component->destroy();
}

const std:: pair<double, double> PrototypeDecorator::getPos()const
{
    return component->getPos();
}

const int PrototypeDecorator::getIndex()const
{
    return component->getIndex();
}
Sprite* PrototypeDecorator::getSprite()const 
{
    return component->getSprite();
}


std::string PrototypeDecorator::getMsg()const
{
    return component->getMsg();
}


void PrototypeDecorator::setPos(const std::pair<double, double> rpos)
{
    component->setPos(rpos);
}

void PrototypeDecorator::setIndex(const int rindex)
{
    component->setIndex(rindex);
}
