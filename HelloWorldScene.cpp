#include "MainScene.h"
#include "HelloWorldScene.h"
#include "OptionScene.h"
#include "ScoreScene.h"
#include "DataController.h"
#include "Bgm.h"
#include "Setting.h"
#include "Graph.h"
#include "Judge.h"
#include "RecordOriginator.h"
#include "RecordController.h"
#include "CreateItem.h"
USING_NS_CC;
    Scene* HelloWorld::createScene()
    {
        auto scene = Scene::create();
        auto layer = HelloWorld::create();
        scene->addChild(layer);
        return scene;
    }

    bool HelloWorld::init()
    {
        // init setting
        if (!Scene::init())
        {
            return false;
        }
        UIMemberInit();

        ///////////////////////////////
        return true;
    }

    void HelloWorld::UIMemberInit()
    {
        //////////////
        /////LOGO
        /////
        /////////////
        auto helloworld = ItemFunction::createHelloWorld();
        this->addChild(helloworld, 1);
        ///////////////////////////////////////
        ///////Background
        ////////////////////////////////

        auto background = ItemFunction::createBackground(std::string("HelloWorld"));
        this->addChild(background, 0);

        menuInit();
    }

    void HelloWorld::menuInit()
    {
        ///////////////////////////////////////
        //Begin a new game 位于LOGO下方
        ///////////////
        auto newItem = ItemFunction::createMenu(
            std::string("New.png"),
            CC_CALLBACK_1(HelloWorld::menuNewCallback, this));
        ItemFunction::putdown(newItem);

        MenuItems.pushBack(newItem);
        ///////////////////////////////////////////////////
        /////Go to option Scene 位于new按钮下方
        //////////////////////////
        auto optionItem = ItemFunction::createMenu(
            std::string("Options.png"),
            CC_CALLBACK_1(HelloWorld::menuOptionCallback, this));

        ItemFunction::putdown(optionItem);
        ItemFunction::putbydown(optionItem, 1);


        MenuItems.pushBack(optionItem);
        ///////////////////////////////////////////////////
        /////Go to option Scene 位于new按钮下方
        //////////////////////////
        auto scoreItem = ItemFunction::createMenu(
            std::string("Help.png"),
            CC_CALLBACK_1(HelloWorld::menuScoreCallback, this));

        ItemFunction::putdown(scoreItem);
        ItemFunction::putbydown(scoreItem, 2);
        MenuItems.pushBack(scoreItem);
        ///////////////////////
        /////Exit 位于option按钮下方
        /////////////////////
        auto closeItem = ItemFunction::createMenu(
            std::string("Back.png"),
            CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

        ItemFunction::putdown(closeItem);
        ItemFunction::putbydown(closeItem, 3);
        MenuItems.pushBack(closeItem);
        //////////////////////////////
        //////////////读取菜单
        if (DataController::getInstance().issaved())
        {

            auto loadItem = ItemFunction::createMenu(
                std::string("Load.png"),
                CC_CALLBACK_1(HelloWorld::menuLoadCallback, this));
            ItemFunction::putlefttop(loadItem);

            MenuItems.pushBack(loadItem);
        }
        /////////////////////////////
        //////////复盘菜单
        //////////////////////////

        if (RecordController::getInstance().isrecorded())
        {

            auto reviewItem = ItemFunction::createMenu(
                std::string("Record.png"),
                CC_CALLBACK_1(HelloWorld::menuReviewCallback, this));
            ItemFunction::putrighttop(reviewItem);

            MenuItems.pushBack(reviewItem);
        }
        /////////////////////////////
        /////////////
        auto menu = Menu::createWithArray(MenuItems);
        menu->setPosition(Vec2::ZERO);
        this->addChild(menu, 2);
    }

    void HelloWorld::menuCloseCallback(Ref* pSender)
    {
        //Close the cocos2d-x game scene and quit the application
        BGM::press();
        Director::getInstance()->end();
    }

    void HelloWorld::menuNewCallback(Ref* pSender)
    {
        //切换场景至Mainscene    
        RecordController::getInstance().newgame();//模式重置
        DataController::getInstance().newgame();
        BGM::press();
        Director::getInstance()->replaceScene(TransitionFade::create(0.5, MainScene::createScene(), Color3B(0, 255, 255)));
    }

    void HelloWorld::menuOptionCallback(Ref* pSender)
    {
        //切换场景至Optionscrene
        BGM::press();
        Director::getInstance()->replaceScene(TransitionFade::create(0.5, OptionScene::createScene(), Color3B(0, 255, 255)));
    }

    void HelloWorld::menuScoreCallback(Ref* pSender)
    {
        //切换场景至Scorescrene
        BGM::press();
        Director::getInstance()->replaceScene(TransitionFade::create(0.5, ScoreScene::createScene(), Color3B(0, 255, 255)));
    }

    void HelloWorld::menuLoadCallback(Ref* pSender)
    {
        //LOAD
        BGM::press();
        DataController::getInstance().load();
        Director::getInstance()->replaceScene(TransitionFade::create(0.5, MainScene::createScene(), Color3B(0, 255, 255)));
    }


    void HelloWorld::menuReviewCallback(Ref* pSender)
    {
        BGM::press();
        RecordController::getInstance().reviewgame();
        Director::getInstance()->replaceScene(TransitionFade::create(0.5, MainScene::createScene(), Color3B(0, 255, 255)));
    }
