#pragma once
#include "cocos2d.h"
#include <vector>
#include <string>
#include <utility>
#include <memory>
#include <queue>
using std::vector;
using std::queue;
using std::string;
class MainScene;
class cocos2d::UserDefault;
class RecordOriginator;
//////////////////////////////
////////备忘录,存储记录,并隐藏了与本地文件的交互
//////////////////////////////
class RecordMemento final
{
    //除了原发器开放宽接口,不允许其他类改变状态,高度封装+窄接口
    friend class RecordOriginator;
public:
    ~RecordMemento()=default;
    RecordMemento(const RecordMemento&) = delete;
    RecordMemento() = delete; 
    RecordMemento(std::shared_ptr<RecordMemento> st, string msg = "");
    RecordMemento(string = "");
    RecordMemento(std::vector<std::pair<std::string, int>>& st,string="");
private:
    std::vector<std::pair<std::string, int>>state;
    std::string type;
    void setState(std::vector<std::pair<std::string, int>>&);
    std::vector<std::pair<std::string, int>>&getState();
    //处理类型
    string transformString(string msg);
    //加载记录
    void reviewLocal();
    //保存记录
    void recordLocal();
};

