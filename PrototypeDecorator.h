#pragma once
#include "cocos2d.h"
#include "Model.h"
#include "PrototypeInterface.h"
#include <utility>
#include <string>
class PrototypeInterface;
class PrototypeDecorator:public PrototypeInterface//装饰器,转发请求
{
    std::shared_ptr<PrototypeInterface> component;//持有接口指针,指向实现的Handle,利用组合复用了实现
public:
    virtual ~PrototypeDecorator()=default;
    PrototypeDecorator(std::shared_ptr<PrototypeInterface>);
    PrototypeDecorator() = delete;
    Sprite * create(std::shared_ptr<Graph>& graph, int index);
    void destroy();
    const std::pair<double, double> getPos()const;
    const int getIndex()const;
    Sprite* getSprite()const;
    std::string getMsg()const;
    //观察者订阅
    void attach(std::shared_ptr<Observer> link) { component->attach(link); }
    void detach(std::shared_ptr<Observer> delink) { component->detach(delink); }
    //外界获取状态
    std::pair < std::string, int > getState() { return component->getState(); }
    void setState(std::string msg, int index) { component->setState(msg, index); };
protected://重写权限,仅允许装饰器可写
    void setPos(const std::pair<double, double>);
    void setIndex(const int);
private:
    void notify(){};//禁止自动更新
};

