#include "Referee.h"
#include "GameFacade.h"
#include "Mouse.h"
#include "Graph.h"
#include "Setting.h"
#include "RecordController.h"
#include "RecordOriginator.h"
USING_NS_CC;

void Referee::judgeHumanWin(int mouseindex, GameFacade* game)
{
    bool life = game->graph->findDeathBlock(mouseindex);
    if (!life)
    {
        game->humanVictory();
        if (Setting::getInstance().getMouse() == Setting::getInstance().getHuman() ||
            RecordController::getInstance().isreviewed())return;//仅在pve下计算胜负场次
        if (Setting::getInstance().getHuman())
            judgeWin();
        else
            judgeLose();
    }
}

void Referee::judgeMouseWin(int index, GameFacade* scene)
{
    if (scene->graph->ishole(index))
    {
        scene->mouseVictory();
        if (Setting::getInstance().getMouse() == Setting::getInstance().getHuman() ||
            RecordController::getInstance().isreviewed())return;//仅在pve下计算胜负场次
        if (Setting::getInstance().getMouse())
            judgeWin();
        else
            judgeLose();
    }
    else scene->mouseItem->anime("jump");
}

void Referee::judgeWin()
{
    auto win = UserDefault::getInstance()->getIntegerForKey("win");
    UserDefault::getInstance()->setIntegerForKey("win", win + 1);
    auto score = UserDefault::getInstance()->getIntegerForKey("score");
    UserDefault::getInstance()->setIntegerForKey("score", score + 3);//积分与经验挂钩
}


void Referee::judgeLose()
{
    auto lose = UserDefault::getInstance()->getIntegerForKey("lose");
    UserDefault::getInstance()->setIntegerForKey("lose", lose + 1);
    auto score = UserDefault::getInstance()->getIntegerForKey("score");
    UserDefault::getInstance()->setIntegerForKey("score", score + 1);//积分与经验挂钩
}
