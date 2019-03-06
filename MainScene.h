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
��Ϸ������
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
    //ģ�黯��ʼ����
    void functionMemberInit();
    void UIMemberInit();
    //���ߺ���
    void menuInit();
    //�ص�����
    void menuBackCallback(cocos2d::Ref* pSender);//��Ĭ��ʵ�ֽ�������չ
    void menuSaveCallback(cocos2d::Ref* pSender);
    void menuShadowCallback(cocos2d::Ref* pSender);
    void menuRecordCallback(cocos2d::Ref* pSender);
    void menuUndoCallback(cocos2d::Ref* pSender);
    void onMouseDown(cocos2d::EventMouse *event);
    //implement the "static create()" method
    CREATE_FUNC(MainScene);
};