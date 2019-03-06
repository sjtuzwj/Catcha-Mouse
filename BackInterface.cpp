#pragma once
#include "BackInterface.h"
#include "Bgm.h"
#include "HelloWorldScene.h"

void BackInterface::menuBackCallback(cocos2d::Ref* pSender)//奇淫巧技,可选择性继承的实现
{
    //切换场景至HelloWorld
    BGM::press();
    cocos2d::Director::getInstance()->replaceScene(cocos2d::TransitionFade::create(0.5, HelloWorld::createScene(),
        cocos2d::Color3B(0, 255, 255)));
}