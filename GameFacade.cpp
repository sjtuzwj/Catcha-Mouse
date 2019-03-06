#include "GameFacade.h"
#include "MainScene.h"
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "Trap.h"
#include "Referee.h"
#include "Mouse.h"
#include "Prototype.h"
#include "Hole.h"
#include "DataController.h"
#include "Graph.h"
#include "Bgm.h"
#include "Setting.h"
#include "RecordOriginator.h"
#include "Judge.h"
#include "RecordController.h"
#include "CreateItem.h"
#include "CallbackTimer.h"
using std::make_pair;
using std::pair;
using std::string;

USING_NS_CC;
void GameFacade::init(MainScene* binding)//重置
{
    actionCounter.clear();
    recordCounter.clear();
    record->state.clear();
    TrapItems.clear();
    HoleItems.clear();
    shadowable=3;
    isshadowed=0;
    eggFlag = 0;
    cur = 0;
    graph = std::make_shared<Graph>();//抽象图模型
    undoable = false;//人操作后才可撤回
    clickable = true;//必须是PV*且没有胜败才可进行鼠标事件
    turn = 1;
    ismouseturn = false;
    scene = binding;
    functionMemberInit();
    modeInit();
    weatherInit();
}

////////////////////////////////////
////////初始
void GameFacade::functionMemberInit()
{
    ////////////////////////////
    //////////////计时器
    //跳过回合计时器
    for (int i = 0; i < 2; i++)
    {
        auto Counter = CallbackTimeCounter::create();
        actionCounter.push_back(Counter);
        scene->addChild(Counter);
    }
    //超时计时器
    timeCounter = CallbackTimeCounter::create();
    scene->addChild(timeCounter);
    //////////////
}

void GameFacade::weatherInit()
{
    weather = Weather(Judge::getInstance().judgeWhich());
    if (weather == Weather::snow)
    {
        BGM::weather("snow");
        weatherEmitter = ParticleSnow::create();
    }
    else if (weather == Weather::rain)
    {
        weatherEmitter = ParticleRain::create();
        BGM::weather("rain");
        weatherEmitter->setStartSize(7);
    }
    else if (weather == Weather::sun)
    {
        weatherEmitter = ParticleSun::create();
        auto _mouseListener = EventListenerMouse::create();
    }
    else return;
    scene->addChild(weatherEmitter, 10);
    ItemFunction::puttop(weatherEmitter);
}

void GameFacade::modeInit()
{

    if (RecordController::getInstance().isreviewed())
        review();

    else//不在复盘模式
    {
        if (!DataController::getInstance().isloaded())//不在读档模式
            newGame();
        else DataController::getInstance().load(this);
        prepare();
        /////////////////////////////////////////////
    }
}

void GameFacade::newGame()
{
    /////////////////////////////////////////////////////
    //////////////////////产生洞穴
    //////////////////
    auto MaxHole = Setting::getInstance().getMaxHole();
    for (int i = 0; i < MaxHole; i++)
        addRandomHole();
    //////////////////////////
    //////产生老鼠
    ///////////////////////////////
    mouseItem = std::make_shared<Mouse>(Prototype::create("mouse"));
    mouseItem->random(graph);
    scene->addChild(mouseItem->getSprite(), 3);
    record->state.emplace_back("setmouse", mouseItem->getIndex());
    //////////////////////////////////
    /////记录初始状态
    /////////////////////////////
}

void GameFacade::prepare()
{
    if (!Setting::getInstance().getMouse() && !Setting::getInstance().getHuman())//均不控制观战模式
    {
        skipTurn();
        return;
    }
    else if (!ismouseturn && !Setting::getInstance().getHuman())//人行动,人控制老鼠，由电脑控制人先进行一次
        humanETurn();
    else if (ismouseturn && !Setting::getInstance().getMouse())//老鼠行动,人控制人，由电脑老鼠控制先进行一次
        mouseETurn();
    skipCurrentTurn();
}

void GameFacade::delayBGM()
{
    timeCounter->start(10.0f, [this]() {
        if (!this->clickable)return; 
        BGM::overtime();
        this->mouseItem->anime("idle");
    });
}
//////////////////////////////////////////
/////////////动态
void GameFacade::addTurn()
{
    ismouseturn ^= 1;
    turn++;
    if (turn % 20 == 0)
    {
        addRandomHole();
    }
}

bool GameFacade::humanPTurn(EventMouse *event)
{
    //创建捕鼠夹
    auto trap = std::make_shared<Trap>(Prototype::create("trap"));
    if (!trap->click(graph, event))return false;//不合法
    scene->addChild(trap->getSprite(), 2);
    if (isshadowed[1])
        trap->getSprite()->setVisible(false);
    TrapItems.push_back(trap);
    record->state.emplace_back("settrap", trap->getIndex());//emplace-back好文明
    Referee::getInstance().judgeHumanWin(mouseItem->getIndex(), this);
    addTurn();
    if (isshadowed[0]) {
        mouseItem->getSprite()->setVisible(true); isshadowed[0] = false;
    }//显形
    undoable = true;
    return true;
}

bool GameFacade::mousePTurn(EventMouse *event)//老鼠朝点击处走去
{
    if (!mouseItem->click(graph, event))return false;
    record->state.emplace_back("movemouse", mouseItem->getIndex());
    Referee::getInstance().judgeMouseWin(mouseItem->getIndex(), this);
    addTurn();
    if (isshadowed[1]) {
        TrapItems.back()->getSprite()->setVisible(true); isshadowed[1] = false;
    }//显形
    undoable = true;
    return true;
}

void GameFacade::mouseETurn()//老鼠自动寻路
{
    mouseItem->autoset(graph);
    record->state.emplace_back("movemouse", mouseItem->getIndex());
    Referee::getInstance().judgeMouseWin(mouseItem->getIndex(), this);
    addTurn();
}

void GameFacade::humanETurn()//人自动挡路
{
    auto trap = std::make_shared<Trap>(Prototype::create("trap"));
    trap->autoset(graph);
    scene->addChild(trap->getSprite(), 2);
    TrapItems.push_back(trap);
    record->state.emplace_back("settrap", trap->getIndex());
    addTurn();
    Referee::getInstance().judgeHumanWin(mouseItem->getIndex(), this);
}

void GameFacade::addRandomHole()//难度递增或递减,提高公平性
{
    auto hole = std::make_shared<Hole>(Prototype::create("hole"));
    hole->random(graph);
    scene->addChild(hole->getSprite(), 2);
    HoleItems.push_back(hole);
    record->state.emplace_back("sethole", hole->getIndex());
}

void GameFacade::skipTurn()//EVE缩短跳过时间间隔
{
    if (!clickable)return;
    humanETurn();
    mouseETurn();
    actionCounter[(++cur) & 1]->start(2.0f, [this]() {this->skipTurn(); });
}

void GameFacade::skipMouseTurn()//老鼠的惩罚
{
    mouseETurn();
    BGM::overtime();
    humanETurn();
    skipCurrentTurn();
}

void GameFacade::skipHumanTurn()//人的惩罚
{
    humanETurn();
    BGM::overtime();
    mouseETurn();
    skipCurrentTurn();
}

void GameFacade::skipCurrentTurn()//跳过当前回合
{
    delayBGM();
    actionCounter[cur & 1]->pause();
    if (ismouseturn)
        actionCounter[(++cur) & 1]->start(20.0f, [this]() {this->skipMouseTurn(); });
    else
        actionCounter[(++cur) & 1]->start(20.0f, [this]() {this->skipHumanTurn(); });
}

void GameFacade::victory()
{
    //音效及画面
    clickable = false;
    BGM::playvictory();
    auto helloworld = ItemFunction::createHelloWorld();
    scene->addChild(helloworld, 7);
}

void GameFacade::mouseVictory()
{
    mouseItem->anime("holein"); 
    victory();
}


void GameFacade::humanVictory()
{
    auto emitter = ParticleMeteor::create();
    auto pos = mouseItem->getPos();
    emitter->setPosition(Vec2(pos.first, pos.second));
    scene->addChild(emitter, 5);
    victory();
}
/////////////////////////////////////////
////////////////////////////////////
///////////////重演
void GameFacade::review()//record记录正常
{
    clickable = false;
    record->restoreToMemento(RecordController::getInstance().getRecord());
    auto beg = firstState() + 1;//初始化
    int j = 1;
    for (; beg != record->state.end(); beg++)//逐步推演
    {
        auto Counter = CallbackTimeCounter::create();
        auto msg = *beg;
        scene->addChild(Counter);
        recordCounter.push_back(Counter);
        Counter->start(j++, [this, msg]() {this->nextStep(msg); });//beg 必须按照值捕获
    }
}

std::vector<std::pair<std::string, int>>::iterator GameFacade::firstState()
{
    auto ptr = record->state.begin();
    while (ptr->first != "setmouse")
    {
        nextStep(*ptr++);
    }
    nextStep(*ptr);
    return ptr;
}

void GameFacade::nextStep(std::pair<std::string, int> msg)//逐步推演
{
    if (msg.first == "sethole") {
        auto hole = std::make_shared<Hole>(Prototype::create("hole"));
        hole->create(graph, msg.second);
        scene->addChild(hole->getSprite(), 2);
        HoleItems.push_back(hole);
    }
    else if (msg.first == "settrap")
    {
        auto trap = std::make_shared<Trap>(Prototype::create("trap"));
        trap->create(graph, msg.second);
        scene->addChild(trap->getSprite(), 2);
        TrapItems.push_back(trap);
        Referee::getInstance().judgeHumanWin(mouseItem->getIndex(), this);
    }
    else if (msg.first == "movemouse")
    {
        mouseItem->move(graph, msg.second);
        Referee::getInstance().judgeMouseWin(mouseItem->getIndex(), this);
    }
    else if (msg.first == "setmouse")
    {
        mouseItem = std::make_shared<Mouse>(Prototype::create("mouse"));
        mouseItem->create(graph, msg.second);
        scene->addChild(mouseItem->getSprite(), 3);
    }
}

void GameFacade::lastStep(std::pair<std::string, int>& msg)//撤销上一步
{
    if (msg.first == "sethole") {
        auto hole = HoleItems.back();
        HoleItems.pop_back();
        hole->destroy();
    }
    else if (msg.first == "settrap")
    {
        auto trap = TrapItems.back();
        TrapItems.pop_back();
        trap->destroy();
        turn--;
        ismouseturn ^= 1;
    }
    else if (msg.first == "movemouse")
    {
        auto itr = record->state.rbegin();
        for (; itr != record->state.rend(); itr++)
            if (itr->first == "movemouse" || itr->first == "setmouse")break;//获取上次老鼠位置
        mouseItem->anime("jump");
        mouseItem->move(graph, itr->second);
        turn--;
        ismouseturn ^= 1;
    }
}

///////////////////////////////////////////
//////////////回调

void GameFacade::dealWithRecord(Ref* pSender)
{
    //重置场景,复盘模式开启
    if(!RecordController::getInstance().isreviewed())
    RecordController::getInstance().setRecord(record->createMemento());
    BGM::playbgm();
    Director::getInstance()->replaceScene(TransitionFade::create(0.5, MainScene::createScene(), Color3B(0, 255, 255)));
}

void GameFacade::dealWithSave(Ref* pSender)
{
    if (!clickable)return;
    BGM::press();
    DataController::getInstance().save(this);
}

void GameFacade::dealWithShadow(Ref* pSender)
{
    if (!clickable) return;//禁
    if (ismouseturn && shadowable[static_cast<size_t>(Actortype::mouse)])//pve模式
    {
            shadowable[static_cast<size_t>(Actortype::mouse)] = false;
            isshadowed[static_cast<size_t>(Actortype::mouse)] = true;
            mouseItem->getSprite()->setVisible(false);//逻辑不一样,不好合并
    }
    else if (!ismouseturn && shadowable[static_cast<size_t>(Actortype::human)])
    {
            shadowable[static_cast<size_t>(Actortype::human)] = false;
            isshadowed[static_cast<size_t>(Actortype::human)] = true;
    }
    else return;
    BGM::press();
}

void GameFacade::dealWithUndo(Ref* pSender)
{
    if (record->state.empty() || record->state.back().first == "setmouse" || !undoable || !clickable)return;//检验合法性
    BGM::press();
    int step = !(Setting::getInstance().getMouse() && Setting::getInstance().getHuman()) + 1;//为PVP则只撤回1步,PVE两布
    for(int i=0;i!=step;i++)
    {
        auto msg = record->state.back();
        if (msg.first == "sethole") {
            record->state.pop_back(); lastStep(msg);
        }//auto destroy hole
        msg = record->state.back();
        record->state.pop_back();
        lastStep(msg);
    }
    undoable = false;//合法性重置
}

void GameFacade::dealWithMouse(EventMouse *event)
{
    if (!clickable|!Setting::getInstance().getMouse() & !Setting::getInstance().getHuman())return;//禁止
    if (ismouseturn && Setting::getInstance().getMouse())
    {
        if (!mousePTurn(event))return;//P行动
        if (!Setting::getInstance().getHuman() && clickable)//E行动
            humanETurn();
    }
    else if (!ismouseturn&& Setting::getInstance().getHuman())
    {
        if (!humanPTurn(event))return;//P行动
        if (!Setting::getInstance().getMouse() && clickable)//E行动
            mouseETurn();
    }
    if (Setting::getInstance().getDark() && weather == Weather::sun 
        && !eggFlag[static_cast<size_t>(Flagtype::sun)] && Judge::getInstance().judgeClickPos(event, graph) == 26)
        easterEgg();
    skipCurrentTurn();
    BGM::press();
}

void GameFacade::easterEgg()
{
    eggFlag[static_cast<size_t>(Flagtype::sun)] = false;
    BGM::easteregg("sun");
    BGM::weather("sun"); 
    for (int i = 0; i < 60; i++)
    {
        if (!graph->ishole(i))continue;
        ParticleSystem* emitter = ParticleFire::create();;
        auto pos = graph->pos(i);
        emitter->setLife(7);
        emitter->setPosition(Vec2(pos.first, pos.second));
        scene->addChild(emitter, 5);
    }
}