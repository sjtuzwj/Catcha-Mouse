#pragma once
#include <string>
class BGM final
{
public:
    ////////////////////////
    //////控制背景音乐播放的接口,包装了SimpleAudioEngine
    ///////////////////////////
    static void easteregg(std::string);
    static void weather(std::string);
    static void playbgm();
    static void playvictory();
    static void press();//按键声,提高交互实感,同时便于探测游戏逻辑是否正常运转
    static void preload();//预加载
    static void overtime();//超时机器角色扮演};
    BGM() = delete;//禁止创建实例
};