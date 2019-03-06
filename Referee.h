#pragma once
#include "cocos2d.h"
#include <random>
#include <ctime>
#include <memory>

class Graph;
class GameFacade;
/////////////////////////////////////
//////////////决定游戏胜负的类,全局
///////////////////////////////
class Referee
{
private:
    //静态成员
    Referee()=default;
    ~Referee() = default;
    //胜积分计算
    void judgeWin();
    //负积分计算
    void judgeLose();
public:
    //判断人的胜负
    void judgeHumanWin(int mouseindex, GameFacade* scene);
    //判断老鼠胜负
    void judgeMouseWin(int index, GameFacade* scene);
    //单例模式
    static Referee& getInstance() {
        static Referee instance;
        return instance;
    }
};

