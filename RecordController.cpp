#include "RecordController.h"
#include "MainScene.h"
#include "Graph.h"
#include "RecordOriginator.h"

using std::to_string;
using std::string;
using std::pair;

    void RecordController::setRecord(std::shared_ptr<RecordMemento> st)//��Ϸ���渴��
    {
        isreview = true;
        memento=std::make_shared<RecordMemento>(st);//�ƶ�����,������Դ����Ȩ
    }

    std::shared_ptr<RecordMemento> RecordController::getRecord()//��ȡ
    {
        return memento;
    }
