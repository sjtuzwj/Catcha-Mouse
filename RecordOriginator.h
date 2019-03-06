#pragma once
#include "cocos2d.h"
#include <vector>
#include <string>
#include "RecordMemento.h"
#include <utility>
#include <memory>
#include <queue>
using std::vector;
using std::queue;
using std::string;
class MainScene;
class cocos2d::UserDefault;
class RecordOriginator final
    //原发器,提供IO接口,存储游戏记录
    //状态仅在存档时才有效,而过程则全局都有意义,如撤销功能,因此储存过程,而仅对状态热读取.
{
    friend class  GameFacade;//原发器只能被游戏所写入
private:
    std::vector<std::pair<std::string, int>>state;//本身存在时序,索引潜在映射着记录顺序,因此采取向量
public:
    RecordOriginator()=default;
    ~RecordOriginator()=default;
    //从Caretaker获取备忘录并加载为状态
    void restoreToMemento(std::shared_ptr<RecordMemento> pMemento);
    //原发器,将状态转换为备忘录转移给Controller保管
    std::shared_ptr<RecordMemento> createMemento(string msg="");
    void setState(std::vector<std::pair<std::string, int>>&);
    std::vector<std::pair<std::string, int>>& getState();
};

