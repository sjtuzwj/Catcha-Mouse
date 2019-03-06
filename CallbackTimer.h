#pragma once
#include<cocos2d.h>
///////////////////////////////
///////��ʱ��
////////////////////////////////////
    class CallbackTimeCounter final :public cocos2d::Node
    {
    public:
        //����
        CallbackTimeCounter();
        virtual ~CallbackTimeCounter();
        CREATE_FUNC(CallbackTimeCounter);
        virtual bool init();
        virtual void update(float dt);
        //���ܺ���
        void pause() { m_isCounting = false; }
        void start(float fCBTime, std::function<void()>func);//һ��ʱ���ִ�к���
    private:
        float m_Time;//��ʱ��ʱ��
        float m_fCBTime;//ʱ����ֵ
        bool m_isCounting;//�Ƿ��ʱ
        std::function<void()>m_func;
    };