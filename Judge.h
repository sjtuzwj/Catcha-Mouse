#pragma once
#include "cocos2d.h"
#include <random>
#include <ctime>
#include <memory>


    class Graph;
    class GameFacade;

    //////////////////////////////
    ////////控制游戏逻辑与随机运算
    //////////////////////////////
    class Judge final
        //单例模式,全局状态
    {
    private:
        //静态成员
        Judge();
        ~Judge() = default;
        //功能成员
        std::default_random_engine eng;//随机数发生引擎(因此使用实例)
        std::uniform_int_distribution<int> hex;//随机数分布对象，0-59，对应六边形索引
        std::uniform_int_distribution<int> whc;//随机数分布对象，1-3，对应图片和音乐和天气资源
        //随机临近节点
        int judgeClosePos(std::shared_ptr<Graph>);
    public:
        //决定地图索引
        //至洞最短路径
        int judgeClosestPos(std::shared_ptr<Graph>);
        //随机空节点
        int judgeRandomPos(std::shared_ptr<Graph>);
        //随机孤立节点
        int judgeProperPos(std::shared_ptr<Graph>);
        //点击节点
        int judgeClickPos(cocos2d::EventMouse *event, std::shared_ptr<Graph> graph);
        //决定编号,因为需要用到随机数发生引擎,所以和决定地图索引内聚了
        int judgeWhich();
        //单例模式
        static Judge& getInstance() {
            static Judge instance;
            return instance;
        }
    };