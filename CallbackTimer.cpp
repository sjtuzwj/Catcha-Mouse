#include "CallbackTimer.h"
using namespace cocos2d;
    CallbackTimeCounter::CallbackTimeCounter()
    {
    }


    CallbackTimeCounter::~CallbackTimeCounter()
    {
    }

    bool CallbackTimeCounter::init()
    {
        if (Node::init() == false) {
            return false;
        }
        m_isCounting = false;
        //this->scheduleUpdate();
        Director::getInstance()->getScheduler()->scheduleUpdate(this, 0, false);
        return true;
    }

    void CallbackTimeCounter::update(float dt)
    {

        if (m_isCounting == false) {
            return;
        }
        m_Time += dt;

        if (m_Time >= m_fCBTime) {

            m_func();
            m_isCounting = false;
        }

    }
    void CallbackTimeCounter::start(float fCBTime, std::function<void()>func)
    {
        m_fCBTime = fCBTime;
        m_Time = 0;
        m_func = func;
        m_isCounting = true;
    }