#pragma once
#include<utility>
#include <string>
class Observer;
using std::string;
//抽象主题接口
////为什么用View作为主题,而Model作为观察者:
////和Web不同,游戏的数据往往来自于View层,而Model观察View从动;而WEB常用的MVC则是基于后端的数据改变前端.因此最终采取了graph观察actor的策略
////最主要的还是先变Graph太难了,很多特定的行为方法,如果知道了具体逻辑,完全可以直接更改View端然后让Model同步,而先用Model的话导致没有对应方法
class Subject
{
public:
    //与观察者相关的接口
    virtual void attach(std::shared_ptr<Observer>)=0;
    virtual void detach(std::shared_ptr<Observer>)=0;
    //与主题类相关的接口
    virtual std::pair < std:: string, int > getState()=0;//推模型,假定了观察者所需要的信息
    virtual void setState(string, int) = 0;
    //发布通知,可以用户自定义也可以自动发布,实现接口的细节由实现类决定
    virtual void notify() = 0;
};