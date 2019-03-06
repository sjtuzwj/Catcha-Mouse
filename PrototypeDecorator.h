#pragma once
#include "cocos2d.h"
#include "Model.h"
#include "PrototypeInterface.h"
#include <utility>
#include <string>
class PrototypeInterface;
class PrototypeDecorator:public PrototypeInterface//װ����,ת������
{
    std::shared_ptr<PrototypeInterface> component;//���нӿ�ָ��,ָ��ʵ�ֵ�Handle,������ϸ�����ʵ��
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
    //�۲��߶���
    void attach(std::shared_ptr<Observer> link) { component->attach(link); }
    void detach(std::shared_ptr<Observer> delink) { component->detach(delink); }
    //����ȡ״̬
    std::pair < std::string, int > getState() { return component->getState(); }
    void setState(std::string msg, int index) { component->setState(msg, index); };
protected://��дȨ��,������װ������д
    void setPos(const std::pair<double, double>);
    void setIndex(const int);
private:
    void notify(){};//��ֹ�Զ�����
};

