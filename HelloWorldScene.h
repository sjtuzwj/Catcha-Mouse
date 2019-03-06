#pragma once

#include "cocos2d.h"
#include "UIInterface.h"
    /****************************************************************************
    初始菜单页面
    ****************************************************************************/

    class HelloWorld  final : public cocos2d::Scene, virtual public UIInterface
    {
    public:
        static cocos2d::Scene* createScene();
        virtual bool init();

    private:
        void UIMemberInit();
        void menuInit();
        //回调函数,向各个界面的跳转
        void menuCloseCallback(cocos2d::Ref* pSender);
        void menuNewCallback(cocos2d::Ref* pSender);
        void menuOptionCallback(cocos2d::Ref* pSender);
        void menuScoreCallback(Ref* pSender);
        void menuLoadCallback(Ref* pSender);
        void menuReviewCallback(Ref* pSender);
        //implement the "static create()" method manually
        CREATE_FUNC(HelloWorld);
    };