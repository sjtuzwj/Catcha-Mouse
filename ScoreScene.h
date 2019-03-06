#pragma once
#include "cocos2d.h"
#include "BackInterface.h"
#include "UIInterface.h"
#include "ui/CocosGUI.h"

/****************************************************************************
���ط����͵ȼ��Ľ���
****************************************************************************/
class BackInterface;
class ScoreScene  final : public cocos2d::Scene, public BackInterface, virtual public UIInterface
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
private:
    //�ص�����
    void menuBackCallback(cocos2d::Ref* pSender);
    //��ʼ������
    void UIMemberInit();
    void menuInit();
    void labelInit();//��ʾʤ�����κ͵ȼ�
    void loadingBarInit();//��ʾ����ֵ
    cocos2d::Label* createLabel(const char* msg, int info);
    //implement the "static create()" method manually
    CREATE_FUNC(ScoreScene);
};
