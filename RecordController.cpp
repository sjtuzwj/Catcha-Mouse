#include "RecordController.h"
#include "MainScene.h"
#include "Graph.h"
#include "RecordOriginator.h"

using std::to_string;
using std::string;
using std::pair;

    void RecordController::setRecord(std::shared_ptr<RecordMemento> st)//游戏界面复盘
    {
        isreview = true;
        memento=std::make_shared<RecordMemento>(st);//移动构造,放弃资源所有权
    }

    std::shared_ptr<RecordMemento> RecordController::getRecord()//获取
    {
        return memento;
    }
