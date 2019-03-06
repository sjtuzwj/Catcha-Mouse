#pragma once
#include "cocos2d.h"
#include "Subject.h"
#include <utility>
///////////////////////////////////
///////Interface of Prototype
///////////////////////////////
using cocos2d::Sprite;
class Graph;
class PrototypeInterface:public Subject//定义抽象类的接口,接口继承接口是好文明!
{
public:
    virtual ~PrototypeInterface()=default;
    //生灭
    virtual Sprite * create(std::shared_ptr<Graph>& graph, int index)=0;
    virtual void destroy()=0; 
    //成员接口
    virtual const std::pair<double, double> getPos()const = 0;
    virtual const int getIndex()const = 0;
    virtual Sprite* getSprite()const = 0;
    virtual std::string getMsg()const = 0; 
    //修改成员的接口
    virtual void setPos(const std::pair<double, double>) = 0;
    virtual void setIndex(const int) = 0;
};

