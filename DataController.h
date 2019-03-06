#pragma once
#include "cocos2d.h"
#include <vector>
#include <string>
#include <utility>
#include <memory>
#include <queue>


    using std::vector;
    using std::queue;
    class DataController;
    class CallbackTimeCounter;
    class GameFacade;
    class cocos2d::UserDefault;
    //////////////////////////////
    ////////���ƴ浵
    //////////////////////////////
    class DataController final
        //����ģʽ,ȫ��״̬
    {
    private:
        //��̬��Ա
        DataController() = default;
        ~DataController() = default;
        //���ܳ�Ա
        bool isload = false;
        //���ߺ���,������
        void saveFlag(GameFacade*);
        void saveMember(GameFacade*);
        void loadFlag(GameFacade*);
        void loadMember(GameFacade*);
    public:
        static DataController& getInstance() {//�̰߳�ȫ
            static DataController instance;
            return instance;
        }

        //�浵����
        //���д浵
        void save(GameFacade*);
        //�Ƿ���ڴ浵
        bool issaved() { return cocos2d::UserDefault::getInstance()->getBoolForKey("saved"); }

        //��������
        //���ж���
        void load(GameFacade*);
        //�Ƿ��Ѿ�����
        bool isloaded() { return isload; }
        //�ӿ�ʼ����Ķ�������
        void load() { isload = true; }
        //�����ж���,��ʼ����Ϸ
        void newgame() { isload = false; }
    };