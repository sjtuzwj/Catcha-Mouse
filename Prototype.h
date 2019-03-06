#pragma once
#include "cocos2d.h"
#include "Model.h"
#include "PrototypeInterface.h"
#include <utility>
#include <string>
#include <vector>
#include <list>
#include <algorithm>

    ///////////////////////////////////
    ///////所有精灵原型,存储实体
    ///////////////////////////////
    using cocos2d::Sprite;
    using std::pair;
    using std::string;
    class Graph;
    class Prototype final:public PrototypeInterface//不可变的部分与可变的部分分离,同时作为具体主题角色存在
    {
    private:
        //创建目标到观察者之间的映射
        std::list<std::shared_ptr<Observer>> observer; //更追求插入删除的高校,采取链表
        //状态改变
        std::pair < std::string, int >state;
        //数据
        SpriteModel model;
        //视图
        Sprite* sprite;
        virtual ~Prototype() = default;
        Prototype() = delete;//无法创建无信息的实例
        Prototype(char* omsg) :model(omsg) {}//装饰者
        virtual void notify();//禁止了手动更新
    public:
        static std::shared_ptr<PrototypeInterface> create(char*);//静态方法不可被继承
        //创建与销毁
        virtual Sprite * create(std::shared_ptr<Graph>& graph, int index);//触发通知
        virtual void destroy();//触发通知
        //不希望被重写的默认实现,接口
        const pair<double, double> getPos()const  noexcept { return model.pos; }
        const int getIndex()const noexcept { return model.index; }
        Sprite* getSprite()const  noexcept { return sprite; }
        std::string getMsg()const noexcept { return model.msg; }
        void setPos(const std::pair<double, double>rpos)  noexcept { model.pos = rpos; }
        void setIndex(const int rindex) noexcept { if (rindex < 60 && rindex>0)model.index = rindex; }
        //观察者模式接口
        virtual void attach(std::shared_ptr<Observer> link){observer.push_back(link);}
        virtual void detach(std::shared_ptr<Observer> delink)
        {observer.erase(find(observer.begin(),observer.end(),delink)); }
        virtual std::pair < std::string, int > getState() { return state; }
        virtual void setState(string msg, int index) { state = std::make_pair(msg, index); notify(); }//由状态设定操作自动更新
    };
