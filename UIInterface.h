#pragma once
//UI����ӿ�,attention!!����ຬ�����ݳ�Ա,�������̳�
class UIInterface
{
protected:
    cocos2d::Vector<cocos2d::MenuItem*> MenuItems;//��Ϊ�����׵�,��������͹��Ҽ̳����ݳ�Ա����
    virtual void UIMemberInit()=0;
    virtual void menuInit() = 0;
};

