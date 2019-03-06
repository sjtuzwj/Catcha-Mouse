#pragma once
#include "cocos2d.h"
#include "Subject.h"
#include <utility>
///////////////////////////////////
///////Interface of Prototype
///////////////////////////////
using cocos2d::Sprite;
class Graph;
class PrototypeInterface:public Subject//���������Ľӿ�,�ӿڼ̳нӿ��Ǻ�����!
{
public:
    virtual ~PrototypeInterface()=default;
    //����
    virtual Sprite * create(std::shared_ptr<Graph>& graph, int index)=0;
    virtual void destroy()=0; 
    //��Ա�ӿ�
    virtual const std::pair<double, double> getPos()const = 0;
    virtual const int getIndex()const = 0;
    virtual Sprite* getSprite()const = 0;
    virtual std::string getMsg()const = 0; 
    //�޸ĳ�Ա�Ľӿ�
    virtual void setPos(const std::pair<double, double>) = 0;
    virtual void setIndex(const int) = 0;
};

