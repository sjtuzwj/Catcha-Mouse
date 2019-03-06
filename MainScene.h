#pragma once
#include "cocos2d.h"
#include "BackInterface.h"
#include "UIInterface.h"
#include <vector>
#include <string>
#include <utility>
#include <memory>
#include <queue>
#include <iterator>
USING_NS_CC;

/****************************************************************************
游戏主界面
****************************************************************************/

using std::vector;
using std::queue;
class DataController;
class RecordController; 
class Judge;
class MainScene  final : public cocos2d::Scene, public BackInterface, virtual public UIInterface
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
private:
    //模块化初始工具
    void functionMemberInit();
    void UIMemberInit();
    //工具函数
    void menuInit();
    //回调函数
    void menuBackCallback(cocos2d::Ref* pSender);//对默认实现进行了拓展
    void menuSaveCallback(cocos2d::Ref* pSender);
    void menuShadowCallback(cocos2d::Ref* pSender);
    void menuRecordCallback(cocos2d::Ref* pSender);
    void menuUndoCallback(cocos2d::Ref* pSender);
    void onMouseDown(cocos2d::EventMouse *event);
    //implement the "static create()" method
    CREATE_FUNC(MainScene);
};