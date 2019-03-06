#pragma once

#include "cocos2d.h"
#include "PrototypeDecorator.h"
#include "RandomableTemplate.h"
#include "AutosetableTemplate.h"
#include "ClickableTemplate.h"

               //老鼠类
               //对原型进行装饰
    class Mouse final: public PrototypeDecorator,public RandomableTemplate, public AutosetableTemplate, public ClickableTemplate
    {
    private:
        virtual void destroy(std::shared_ptr<Graph>& graph) {}//禁用
        //Click
        virtual bool clickIndexIllegal(std::shared_ptr<Graph>& graph, int);
        virtual void doWithClickIndex(std::shared_ptr<Graph>& graph, int);
        //Random
        virtual int getRandomIndex(std::shared_ptr<Graph>& graph);
        virtual void doWithRandomIndex(std::shared_ptr<Graph>& graph, int);
        //Autoset
        virtual bool nextIndexIllegal(std::shared_ptr<Graph>& graph,int);
        virtual int doWithIllegalNextIndex(std::shared_ptr<Graph>& graph);
        virtual void doWithNextIndex(std::shared_ptr<Graph>& graph, int);
    public:
        Mouse() = delete;
        virtual ~Mouse() = default;
        using PrototypeDecorator::PrototypeDecorator;//继承构造函数
         //overwrite//触发通知
        virtual Sprite * create(std::shared_ptr<Graph>& graph, int index);//触发通知
        //////根据传入的字符串,执行跳跃 入洞 闲暇三种动画
        void anime(const char*);
        //移动到图的指定索引处,触发通知
        void move(std::shared_ptr<Graph>& graph, int index);
    };