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
    ////////控制存档
    //////////////////////////////
    class DataController final
        //单例模式,全局状态
    {
    private:
        //静态成员
        DataController() = default;
        ~DataController() = default;
        //功能成员
        bool isload = false;
        //工具函数,见名字
        void saveFlag(GameFacade*);
        void saveMember(GameFacade*);
        void loadFlag(GameFacade*);
        void loadMember(GameFacade*);
    public:
        static DataController& getInstance() {//线程安全
            static DataController instance;
            return instance;
        }

        //存档功能
        //进行存档
        void save(GameFacade*);
        //是否存在存档
        bool issaved() { return cocos2d::UserDefault::getInstance()->getBoolForKey("saved"); }

        //读档功能
        //进行读档
        void load(GameFacade*);
        //是否已经读档
        bool isloaded() { return isload; }
        //从开始界面的读档进入
        void load() { isload = true; }
        //不进行读档,开始新游戏
        void newgame() { isload = false; }
    };