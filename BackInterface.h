#pragma once
#include "cocos2d.h"
//返回至上界面的接口
class BackInterface
{
protected:
    virtual void menuBackCallback(cocos2d::Ref* pSender)=0;
};
