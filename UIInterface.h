#pragma once
//UI组件接口,attention!!这个类含有数据成员,请务必虚继承
class UIInterface
{
protected:
    cocos2d::Vector<cocos2d::MenuItem*> MenuItems;//因为是配套的,所以这里就姑且继承数据成员好了
    virtual void UIMemberInit()=0;
    virtual void menuInit() = 0;
};

