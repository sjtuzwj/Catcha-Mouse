#pragma once
#include<cocos2d.h>
///////////////////////////////
///////计时器
////////////////////////////////////
    class CallbackTimeCounter final :public cocos2d::Node
    {
    public:
        //构造
        CallbackTimeCounter();
        virtual ~CallbackTimeCounter();
        CREATE_FUNC(CallbackTimeCounter);
        virtual bool init();
        virtual void update(float dt);
        //功能函数
        void pause() { m_isCounting = false; }
        void start(float fCBTime, std::function<void()>func);//一段时间后执行函数
    private:
        float m_Time;//计时器时间
        float m_fCBTime;//时间阈值
        bool m_isCounting;//是否计时
        std::function<void()>m_func;
    };