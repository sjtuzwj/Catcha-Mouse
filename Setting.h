#pragma once
#include <utility>
#include "cocos2d.h"

    using std::pair;
    using cocos2d::UserDefault;
    //////////////////////////////
    //�洢������Ϣ����Ϸ��ֵ�趨,��Ҫ��View���н���,ȫ��״̬
    ////////////////////////////
    class Graph;
    class Setting final
        //����ģʽ
    {
        friend class GraphCalculator;
    private:
        //��ʼ��
        Setting(); 
        ~Setting() = default;
        void initSetting();//���ر�������,��Ϸʱ����,Ŀ�ļ�Сgetʱ��IO
        void initBlockInfo();//�����ڳ�ʼ��ʱ���,��ԼGraph�Ĵ���ʱ��
        
        //���ɱ��ϵͳ����,Viewģ������
        const char* bgmList[3] = { "bgm1.mp3", "bgm2.mp3", "bgm3.mp3" };
        //���ű���
        const double itemScale = 1.2;
        double spriteScale = 1.5;
        //������С
        const double itemHeight = 36 * itemScale;
        const double itemWidth = 67 * itemScale;
        //ͼ����
        pair<double, double>blockInfo[60];

        //���޸ĵ�ϵͳ����,Viewģ������
        //bgm����
        int bgm;
        //����
        double volume;
        //�����,���Żغ����߻ᴴ���µĶ�
        int MaxHole;
        //ͼƬ���
        bool isdark;
        //����Ȩ��
        bool ismouse;
        bool ishuman;
    public:
        //ֻд�ӿ�
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
        //����ģʽ
        static Setting& getInstance() {
            static Setting instance;
            return instance;
        }
        //ֻ���ӿ�
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