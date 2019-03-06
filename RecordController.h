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
        //全局状态
        //Caretaker,负责人只负责保有备忘录和相关信息,不可进行备忘录的状态改变
    {
    private:
        //静态成员
        RecordController() = default;
        ~RecordController() = default;
        //功能成员
        //保管备忘录
        std::shared_ptr<RecordMemento> memento;
        bool isreview = false;
        //Item
    public:
        static RecordController& getInstance() {
            static RecordController instance;
            return instance;
        }
        //记录功能
        //从场景中获取记录并保存至本地
        void setRecord(std::shared_ptr<RecordMemento>);
        //本地获取记录
        std::shared_ptr<RecordMemento> getRecord();
        //判断是否有记录
        bool isrecorded() { return cocos2d::UserDefault::getInstance()->getBoolForKey("recorded"); }//本地获取
        //判断是否开启复盘
        bool isreviewed() { return isreview; }//信息
        //不开启复盘
        void newgame() { isreview = false; }
        //开启复盘
        void reviewgame(){ isreview = true;
        memento= std::make_shared<RecordMemento>("");
        }
    };