#pragma once
#include <utility>
#include "cocos2d.h"

    using std::pair;
    using cocos2d::UserDefault;
    //////////////////////////////
    //存储设置信息及游戏数值设定,主要与View进行交互,全局状态
    ////////////////////////////
    class Graph;
    class Setting final
        //单例模式
    {
        friend class GraphCalculator;
    private:
        //初始化
        Setting(); 
        ~Setting() = default;
        void initSetting();//本地保存数据,游戏时加载,目的减小get时的IO
        void initBlockInfo();//计算在初始化时完成,节约Graph的创建时间
        
        //不可变的系统设置,View模块依赖
        const char* bgmList[3] = { "bgm1.mp3", "bgm2.mp3", "bgm3.mp3" };
        //缩放比例
        const double itemScale = 1.2;
        double spriteScale = 1.5;
        //按键大小
        const double itemHeight = 36 * itemScale;
        const double itemWidth = 67 * itemScale;
        //图计算
        pair<double, double>blockInfo[60];

        //可修改的系统设置,View模块依赖
        //bgm索引
        int bgm;
        //音量
        double volume;
        //最大洞数,随着回合升高会创建新的洞
        int MaxHole;
        //图片风格
        bool isdark;
        //控制权限
        bool ismouse;
        bool ishuman;
    public:
        //只写接口
        void setVolume(double res) {
            if (volume > 1 || volume < 0)return;
        volume = res;
        UserDefault::getInstance()->setDoubleForKey("volume", res);
        }
        void setMaxHole(int res) {
            if (MaxHole > 11 || MaxHole < 0)return;
        MaxHole = res; 
        UserDefault::getInstance()->setIntegerForKey("MaxHole", res);
        }
        void setMouse(bool res) { ismouse = res; 
        UserDefault::getInstance()->setBoolForKey("ismouse", res);
        }
        void setHuman(bool res) { ishuman = res; 
        UserDefault::getInstance()->setBoolForKey("ishuman", res);
        }
        void setDark(bool res) { isdark = res; 
        UserDefault::getInstance()->setBoolForKey("isdark", res);
        }
        void changeBgm() { bgm = (bgm + 1) % 3; UserDefault::getInstance()->setIntegerForKey("bgm", bgm); }
        //单例模式
        static Setting& getInstance() {
            static Setting instance;
            return instance;
        }
        //只读接口
        double getVolume()const noexcept { return volume; }
        int getMaxHole()const noexcept { return MaxHole; }
        bool getMouse()const noexcept { return ismouse; }
        bool getHuman()const noexcept { return ishuman; }
        bool getDark()const noexcept { return isdark; }
        double getItemScale()const noexcept { return itemScale; };
        double getItemHeight()const noexcept { return itemHeight; };
        double getItemWidth()const noexcept { return itemWidth; };
        double getSpriteScale()const noexcept { return spriteScale; }
        const char* getBgm()const noexcept { return bgmList[bgm]; }
    };