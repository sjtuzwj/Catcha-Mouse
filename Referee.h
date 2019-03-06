#pragma once
#include "cocos2d.h"
#include <random>
#include <ctime>
#include <memory>

class Graph;
class GameFacade;
/////////////////////////////////////
//////////////������Ϸʤ������,ȫ��
///////////////////////////////
class Referee
{
private:
    //��̬��Ա
    Referee()=default;
    ~Referee() = default;
    //ʤ���ּ���
    void judgeWin();
    //�����ּ���
    void judgeLose();
public:
    //�ж��˵�ʤ��
    void judgeHumanWin(int mouseindex, GameFacade* scene);
    //�ж�����ʤ��
    void judgeMouseWin(int index, GameFacade* scene);
    //����ģʽ
    static Referee& getInstance() {
        static Referee instance;
        return instance;
    }
};

