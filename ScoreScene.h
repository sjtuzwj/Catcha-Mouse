#pragma once
#include "cocos2d.h"
#include "BackInterface.h"
#include "UIInterface.h"
#include "ui/CocosGUI.h"

/****************************************************************************
记载分数和等级的界面
****************************************************************************/
class BackInterface;
class ScoreScene  final : public cocos2d::Scene, public BackInterface, virtual public UIInterface
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
private:
    //回调函数
    void menuBackCallback(cocos2d::Ref* pSender);
    //初始化工具
    void UIMemberInit();
    void menuInit();
    void labelInit();//显示胜负场次和等级
    void loadingBarInit();//显示经验值
    cocos2d::Label* createLabel(const char* msg, int info);
    //implement the "static create()" method manually
    CREATE_FUNC(ScoreScene);
};
