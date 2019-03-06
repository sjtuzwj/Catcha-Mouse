#include "Setting.h"
#include "cocos2d.h"
    using std::pair;
    USING_NS_CC;
    Setting::Setting()
    {
        initBlockInfo();
        initSetting();
    }


    void Setting::initSetting()
    {
        bgm = UserDefault::getInstance()->getIntegerForKey("bgm");
        volume = UserDefault::getInstance()->getDoubleForKey("volume");
        MaxHole = UserDefault::getInstance()->getIntegerForKey("MaxHole");
        isdark = UserDefault::getInstance()->getBoolForKey("isdark");
        ismouse = UserDefault::getInstance()->getBoolForKey("ismouse");
        ishuman = UserDefault::getInstance()->getBoolForKey("ishuman");
    }

    //算法就是暴力
    void Setting::initBlockInfo()
    {
        //计算所有六边形几何中心
        for (int i = 0; i < 9; i++)
        {
            blockInfo[i].first = 60;
            blockInfo[i].second = 720 - (75 + i * 65);
        }
        for (int i = 9; i < 17; i++)
        {
            blockInfo[i].first = 60 + 60.5;
            blockInfo[i].second = 720 - (105 + (i - 9) * 65);
        }
        for (int i = 17; i < 26; i++)
        {
            blockInfo[i].first = 60 + 121;
            blockInfo[i].second = 720 - (75 + (i - 17) * 65);
        }
        for (int i = 26; i < 34; i++)
        {
            blockInfo[i].first = 60 + 60.5 * 3;
            blockInfo[i].second = 720 - (105 + (i - 26) * 65);
        }
        for (int i = 34; i < 43; i++)
        {
            blockInfo[i].first = 60 + 121 * 2;
            blockInfo[i].second = 720 - (75 + (i - 34) * 65);
        }
        for (int i = 43; i < 51; i++)
        {
            blockInfo[i].first = 60 + 60.5 * 5;
            blockInfo[i].second = 720 - (105 + (i - 43) * 65);
        }
        for (int i = 51; i < 60; i++)
        {
            blockInfo[i].first = 60 + 121 * 3;
            blockInfo[i].second = 720 - (75 + (i - 51) * 65);
        }
    }