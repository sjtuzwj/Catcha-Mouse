#include "cocos2d.h"
#include "HelloWorldScene.h"
#include "MainScene.h"
#include "CreateItem.h" 
#include "DataController.h"
#include "RecordController.h"
#include "OptionScene.h"
#include "ScoreScene.h"
#include "Graph.h"
#include "RecordOriginator.h"
#include "Bgm.h"
#include "Setting.h"
USING_NS_CC;
using namespace ui;
using std::string;
using std::to_string;

Scene* ScoreScene::createScene()
{
    auto scene = Scene::create();
    auto layer = ScoreScene::create();
    scene->addChild(layer);
    return scene;
}

bool ScoreScene::init()
{
    // init setting
    if (!Scene::init())
    {
        return false;
    }

    UIMemberInit();
  
    return true;
}

void ScoreScene::UIMemberInit()
{

    ///////////////////////////
    auto background = ItemFunction::createBackground(std::string("Help"));
    this->addChild(background, 0);
    menuInit();
    labelInit();
    loadingBarInit();
}

void ScoreScene::menuInit()
{
    ///////////

    MenuItemImage* backItem = ItemFunction::createMenu(
        std::string("Back.png"),
        CC_CALLBACK_1(ScoreScene::menuBackCallback, this));
    ItemFunction::putrighttop(backItem);

    MenuItems.pushBack(backItem);
    /////////////////////
    //////

    auto menu = Menu::createWithArray(MenuItems);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 3);
}

void ScoreScene::labelInit()
{
    //////////////////////////
    ////////标签
    ////////////////////////////////////
    auto score = UserDefault::getInstance()->getIntegerForKey("score");
    int level = score / 100 + 1;
    auto levelLabel = createLabel("Level: ", level);
    this->addChild(levelLabel);
    ItemFunction::putbottom(levelLabel);
    ItemFunction::putbyup(levelLabel, 1);

    auto win = UserDefault::getInstance()->getIntegerForKey("win");
    auto winLabel = createLabel("Win: ", win);
    this->addChild(winLabel);
    ItemFunction::putmid(winLabel);


    auto lose = UserDefault::getInstance()->getIntegerForKey("lose");
    auto loseLabel = createLabel("Lose: ", lose);
    this->addChild(loseLabel);
    ItemFunction::putmid(loseLabel);    
    ItemFunction::putbydown(loseLabel, 1);

}

void ScoreScene::loadingBarInit()
{
    /////////////////////////////
    //经验条
    ///////////////////////////////
    auto score = UserDefault::getInstance()->getIntegerForKey("score");
    int percent = score % 100;
    auto loadingBar = LoadingBar::create("LoadingBarFile.png");
    loadingBar->setDirection(LoadingBar::Direction::LEFT);
    loadingBar->setPercent(percent * 10);
    this->addChild(loadingBar);
    ItemFunction::putbottom(loadingBar);
}

void ScoreScene::menuBackCallback(Ref* pSender)
{
    BackInterface::menuBackCallback(pSender);
}

Label* ScoreScene::createLabel(const char* msg, int info)
{
    auto label = Label::createWithTTF(string(msg) + to_string(info), "fonts/Marker Felt.ttf", 24);
    label->enableOutline(Color4B::BLACK, 1);
    return label;
}
