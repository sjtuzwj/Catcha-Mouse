#pragma once
#include "cocos2d.h"
#include "RecordMemento.h"
#include <vector>
#include <string>
#include <utility>
#include <memory>
#include <queue>

    using std::vector;
    using std::queue;
    class cocos2d::UserDefault;
    class RecordController final
        //ȫ��״̬
        //Caretaker,������ֻ�����б���¼�������Ϣ,���ɽ��б���¼��״̬�ı�
    {
    private:
        //��̬��Ա
        RecordController() = default;
        ~RecordController() = default;
        //���ܳ�Ա
        //���ܱ���¼
        std::shared_ptr<RecordMemento> memento;
        bool isreview = false;
        //Item
    public:
        static RecordController& getInstance() {
            static RecordController instance;
            return instance;
        }
        //��¼����
        //�ӳ����л�ȡ��¼������������
        void setRecord(std::shared_ptr<RecordMemento>);
        //���ػ�ȡ��¼
        std::shared_ptr<RecordMemento> getRecord();
        //�ж��Ƿ��м�¼
        bool isrecorded() { return cocos2d::UserDefault::getInstance()->getBoolForKey("recorded"); }//���ػ�ȡ
        //�ж��Ƿ�������
        bool isreviewed() { return isreview; }//��Ϣ
        //����������
        void newgame() { isreview = false; }
        //��������
        void reviewgame(){ isreview = true;
        memento= std::make_shared<RecordMemento>("");
        }
    };