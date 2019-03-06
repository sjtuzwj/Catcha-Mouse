#include "MainScene.h"
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "GameFacade.h"
#include "Bgm.h"
#include "Setting.h"
#include "Judge.h"
#include "RecordOriginator.h"
#include "DataController.h"
#include "RecordController.h"
#include "CreateItem.h"
using std::make_pair;
using std::pair;
using std::string;

USING_NS_CC;
////////////////////////////////////
////////��ʼ
Scene* MainScene::createScene()
{
    auto scene = Scene::create();
    auto layer = MainScene::create();
    scene->addChild(layer);
    return scene;
}

bool MainScene::init()
{
    //////////////////////////////
    // �趨��ʼ��
    ///////////////////////////////
    if (!Scene::init())
    {
        return false; 
    }
    GameFacade::getInstance().init(this);
    functionMemberInit();
    UIMemberInit();
    return true;
}

void MainScene::functionMemberInit()
{
    //////////////////////////
    //�󶨻ص� 
    auto _mouseListener = EventListenerMouse::create();
    _eventDispatcher->addEventListenerWithSceneGraphPriority(_mouseListener, this);
    _mouseListener->onMouseDown = CC_CALLBACK_1(MainScene::onMouseDown, this);
    //////////////
}

void MainScene::UIMemberInit()
{
    /////////////////////////////////////////
    //���Ʊ���
    ///////////////////////////////////////
    auto background = ItemFunction::createBackground(std::string("Game"));
    this->addChild(background, 0);
    ////////////////////////////////
    /////////////���Ƶ�ͼ
    ////////////////////
    auto map = ItemFunction::createBackground(std::string("Map"));
    this->addChild(map, 1);
    ///////////////////���Ʋ˵�
    menuInit();
    
}

void MainScene::menuInit()
{
    ////////////////////////////////////
    ///////////�˵�
    MenuItemImage* backItem = ItemFunction::createMenu(
        std::string("Back.png"),
        CC_CALLBACK_1(MainScene::menuBackCallback, this));
    ItemFunction::putrighttop(backItem);
    MenuItems.pushBack(backItem);

    MenuItemImage* undoItem = ItemFunction::createMenu(
        std::string("Undo.png"),
        CC_CALLBACK_1(MainScene::menuUndoCallback, this));
    ItemFunction::putrighttop(undoItem);
    ItemFunction::putbyleft(undoItem, 1);
    MenuItems.pushBack(undoItem);

    if (Setting::getInstance().getMouse() && Setting::getInstance().getHuman())//PVP
    {
        MenuItemImage* shadowItem = ItemFunction::createMenu(
            std::string("Shadow.png"),
            CC_CALLBACK_1(MainScene::menuShadowCallback, this));
        ItemFunction::putrighttop(shadowItem);
        ItemFunction::putbyleft(shadowItem, 2);
        shadowItem->setScale(0.3f);
        MenuItems.pushBack(shadowItem);
    }

    if (!RecordController::getInstance().isreviewed())//����ģʽ�´浵�Ƿ�
    {
        MenuItemImage* saveItem = ItemFunction::createMenu(
            std::string("Save.png"),
            CC_CALLBACK_1(MainScene::menuSaveCallback, this));
        ItemFunction::putlefttop(saveItem);
        MenuItems.pushBack(saveItem);
    }


        MenuItemImage* recordItem = ItemFunction::createMenu(
            std::string("Record.png"),
            CC_CALLBACK_1(MainScene::menuRecordCallback, this));
        ItemFunction::putbottom(recordItem);
        MenuItems.pushBack(recordItem);

    /////////////////////
    auto menu = Menu::createWithArray(MenuItems);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 3);
}

///////////////////////////////////////////
//////////////�ص�
void MainScene::menuBackCallback(Ref* pSender)
{
    //�л�������HelloWorld
    RecordController::getInstance().newgame();//ģʽ����
    DataController::getInstance().newgame();
    BGM::playbgm();
    BackInterface::menuBackCallback(pSender);
}

void MainScene::menuRecordCallback(Ref* pSender)
{
    GameFacade::getInstance().dealWithRecord(pSender);
}

void MainScene::menuSaveCallback(Ref* pSender)
{
    GameFacade::getInstance().dealWithSave(pSender);
}

void MainScene::menuShadowCallback(Ref* pSender)
{
    GameFacade::getInstance().dealWithShadow(pSender);
}

void MainScene::menuUndoCallback(Ref* pSender)
{
    GameFacade::getInstance().dealWithUndo(pSender);
}

void MainScene::onMouseDown(EventMouse *event)
{
    GameFacade::getInstance().dealWithMouse(event);
}