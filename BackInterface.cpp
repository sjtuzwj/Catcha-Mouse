#pragma once
#include "BackInterface.h"
#include "Bgm.h"
#include "HelloWorldScene.h"

void BackInterface::menuBackCallback(cocos2d::Ref* pSender)//�����ɼ�,��ѡ���Լ̳е�ʵ��
{
    //�л�������HelloWorld
    BGM::press();
    cocos2d::Director::getInstance()->replaceScene(cocos2d::TransitionFade::create(0.5, HelloWorld::createScene(),
        cocos2d::Color3B(0, 255, 255)));
}