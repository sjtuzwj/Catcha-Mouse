#include "Bgm.h"
#include"SimpleAudioEngine.h"
#include"Judge.h"
#include"Setting.h"
    
using namespace CocosDenshion;
    void BGM::preload()//预加载
    {
        auto audio = SimpleAudioEngine::getInstance();
        audio->preloadBackgroundMusic("bgm1.mp3");
        audio->preloadBackgroundMusic("bgm2.mp3");
        audio->preloadBackgroundMusic("bgm3.mp3");
        audio->preloadEffect("Overtime1.wav");
        audio->preloadEffect("Overtime2.wav");
        audio->preloadEffect("Overtime3.wav");
        audio->preloadBackgroundMusic("victory.wav");
        audio->preloadEffect("Press.wav");
        audio->preloadEffect("rain.wav");
        audio->preloadEffect("sun.wav");
        audio->preloadEffect("sunEasterEgg.wav");
        audio->preloadEffect("snow.wav");
    }

    void BGM::playbgm()//背景音乐
    {
        auto audio = SimpleAudioEngine::getInstance();
        audio->stopAllEffects();
        audio->playBackgroundMusic(Setting::getInstance().getBgm(), true);
        audio->setBackgroundMusicVolume(Setting::getInstance().getVolume());
    }

    void BGM::press()//按键音效
    {
        auto audio = SimpleAudioEngine::getInstance();
        audio->playEffect("Press.wav",false,0,0, Setting::getInstance().getVolume());
    }

    void BGM::overtime()//超时音效
    {
        auto audio = SimpleAudioEngine::getInstance();
        std::string path = "Overtime";
        path = path + std::to_string(Judge::getInstance().judgeWhich()) + ".wav";
        audio->playEffect(path.c_str(),false, 0, 0, Setting::getInstance().getVolume());
    }
    
    void BGM::playvictory()//胜利音效
    {
        auto audio = SimpleAudioEngine::getInstance();
        audio->playBackgroundMusic("victory.wav", false);
        audio->setBackgroundMusicVolume(Setting::getInstance().getVolume()/2);
    }

    void BGM::weather(std::string msg)//天气音效
    {
        auto audio = SimpleAudioEngine::getInstance();
        auto path =  msg + ".wav";
        audio->playEffect(path.c_str(), true, 0, 0, Setting::getInstance().getVolume()/2);
    }

    void BGM::easteregg(std::string msg)//secret
    {
        auto audio = SimpleAudioEngine::getInstance();
        auto path = msg + "EasterEgg.wav";
        audio->playEffect(path.c_str(), false, 0, 0, Setting::getInstance().getVolume());
    }
