#pragma once
#include "cocos2d.h"
#include "BackInterface.h"
#include "UIInterface.h"
#include "ui/CocosGUI.h"
/****************************************************************************
ѡ��˵�ҳ��
****************************************************************************/
class BackInterface;
class OptionScene  final : public cocos2d::Scene, public BackInterface, virtual public UIInterface
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
private:
    //�ص�����
    void menuBackCallback(cocos2d::Ref* pSender);
    void bgmSliderCallBack(cocos2d::Ref *pSender);
    void modeSliderCallBack(cocos2d::Ref *pSender);
    //������ʼ�����ߺ���
    void UIMemberInit();
    void menuInit();
    void checkBoxInit();
    void sliderInit();
    void buttonInit();
    //��ѡ
    cocos2d::Label* createLabelWith(const char* msg, cocos2d::ui::CheckBox*);
    cocos2d::ui::CheckBox* createCheckBox();
    cocos2d::ui::CheckBox* createMouseCheckBox();
    cocos2d::ui::CheckBox* createHumanCheckBox();
    cocos2d::ui::CheckBox* createDarkCheckBox();
    //��ť
    cocos2d::ui::Button* createBgmButton();
    //������
    cocos2d::Label* createLabelWith(const char* msg, cocos2d::ui::Slider*);
    cocos2d::ui::Slider* createSlider();
    cocos2d::ui::Slider* createBgmSlider();
    cocos2d::ui::Slider* createModeSlider();
    // implement the "static create()" method manually
    CREATE_FUNC(OptionScene);
};