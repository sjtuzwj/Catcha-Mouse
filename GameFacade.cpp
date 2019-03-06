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
void GameFacade::init(MainScene* binding)//����
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
    graph = std::make_shared<Graph>();//����ͼģ��
    undoable = false;//�˲�����ſɳ���
    clickable = true;//������PV*��û��ʤ�ܲſɽ�������¼�
    turn = 1;
    ismouseturn = false;
    scene = binding;
    functionMemberInit();
    modeInit();
    weatherInit();
}

////////////////////////////////////
////////��ʼ
void GameFacade::functionMemberInit()
{
    ////////////////////////////
    //////////////��ʱ��
    //�����غϼ�ʱ��
    for (int i = 0; i < 2; i++)
    {
        auto Counter = CallbackTimeCounter::create();
        actionCounter.push_back(Counter);
        scene->addChild(Counter);
    }
    //��ʱ��ʱ��
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

    else//���ڸ���ģʽ
    {
        if (!DataController::getInstance().isloaded())//���ڶ���ģʽ
            newGame();
        else DataController::getInstance().load(this);
        prepare();
        /////////////////////////////////////////////
    }
}

void GameFacade::newGame()
{
    /////////////////////////////////////////////////////
    //////////////////////������Ѩ
    //////////////////
    auto MaxHole = Setting::getInstance().getMaxHole();
    for (int i = 0; i < MaxHole; i++)
        addRandomHole();
    //////////////////////////
    //////��������
    ///////////////////////////////
    mouseItem = std::make_shared<Mouse>(Prototype::create("mouse"));
    mouseItem->random(graph);
    scene->addChild(mouseItem->getSprite(), 3);
    record->state.emplace_back("setmouse", mouseItem->getIndex());
    //////////////////////////////////
    /////��¼��ʼ״̬
    /////////////////////////////
}

void GameFacade::prepare()
{
    if (!Setting::getInstance().getMouse() && !Setting::getInstance().getHuman())//�������ƹ�սģʽ
    {
        skipTurn();
        return;
    }
    else if (!ismouseturn && !Setting::getInstance().getHuman())//���ж�,�˿��������ɵ��Կ������Ƚ���һ��
        humanETurn();
    else if (ismouseturn && !Setting::getInstance().getMouse())//�����ж�,�˿����ˣ��ɵ�����������Ƚ���һ��
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
/////////////��̬
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
    //���������
    auto trap = std::make_shared<Trap>(Prototype::create("trap"));
    if (!trap->click(graph, event))return false;//���Ϸ�
    scene->addChild(trap->getSprite(), 2);
    if (isshadowed[1])
        trap->getSprite()->setVisible(false);
    TrapItems.push_back(trap);
    record->state.emplace_back("settrap", trap->getIndex());//emplace-back������
    Referee::getInstance().judgeHumanWin(mouseItem->getIndex(), this);
    addTurn();
    if (isshadowed[0]) {
        mouseItem->getSprite()->setVisible(true); isshadowed[0] = false;
    }//����
    undoable = true;
    return true;
}

bool GameFacade::mousePTurn(EventMouse *event)//���󳯵������ȥ
{
    if (!mouseItem->click(graph, event))return false;
    record->state.emplace_back("movemouse", mouseItem->getIndex());
    Referee::getInstance().judgeMouseWin(mouseItem->getIndex(), this);
    addTurn();
    if (isshadowed[1]) {
        TrapItems.back()->getSprite()->setVisible(true); isshadowed[1] = false;
    }//����
    undoable = true;
    return true;
}

void GameFacade::mouseETurn()//�����Զ�Ѱ·
{
    mouseItem->autoset(graph);
    record->state.emplace_back("movemouse", mouseItem->getIndex());
    Referee::getInstance().judgeMouseWin(mouseItem->getIndex(), this);
    addTurn();
}

void GameFacade::humanETurn()//���Զ���·
{
    auto trap = std::make_shared<Trap>(Prototype::create("trap"));
    trap->autoset(graph);
    scene->addChild(trap->getSprite(), 2);
    TrapItems.push_back(trap);
    record->state.emplace_back("settrap", trap->getIndex());
    addTurn();
    Referee::getInstance().judgeHumanWin(mouseItem->getIndex(), this);
}

void GameFacade::addRandomHole()//�Ѷȵ�����ݼ�,��߹�ƽ��
{
    auto hole = std::make_shared<Hole>(Prototype::create("hole"));
    hole->random(graph);
    scene->addChild(hole->getSprite(), 2);
    HoleItems.push_back(hole);
    record->state.emplace_back("sethole", hole->getIndex());
}

void GameFacade::skipTurn()//EVE��������ʱ����
{
    if (!clickable)return;
    humanETurn();
    mouseETurn();
    actionCounter[(++cur) & 1]->start(2.0f, [this]() {this->skipTurn(); });
}

void GameFacade::skipMouseTurn()//����ĳͷ�
{
    mouseETurn();
    BGM::overtime();
    humanETurn();
    skipCurrentTurn();
}

void GameFacade::skipHumanTurn()//�˵ĳͷ�
{
    humanETurn();
    BGM::overtime();
    mouseETurn();
    skipCurrentTurn();
}

void GameFacade::skipCurrentTurn()//������ǰ�غ�
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
    //��Ч������
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
///////////////����
void GameFacade::review()//record��¼����
{
    clickable = false;
    record->restoreToMemento(RecordController::getInstance().getRecord());
    auto beg = firstState() + 1;//��ʼ��
    int j = 1;
    for (; beg != record->state.end(); beg++)//������
    {
        auto Counter = CallbackTimeCounter::create();
        auto msg = *beg;
        scene->addChild(Counter);
        recordCounter.push_back(Counter);
        Counter->start(j++, [this, msg]() {this->nextStep(msg); });//beg ���밴��ֵ����
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

void GameFacade::nextStep(std::pair<std::string, int> msg)//������
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

void GameFacade::lastStep(std::pair<std::string, int>& msg)//������һ��
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
            if (itr->first == "movemouse" || itr->first == "setmouse")break;//��ȡ�ϴ�����λ��
        mouseItem->anime("jump");
        mouseItem->move(graph, itr->second);
        turn--;
        ismouseturn ^= 1;
    }
}

///////////////////////////////////////////
//////////////�ص�

void GameFacade::dealWithRecord(Ref* pSender)
{
    //���ó���,����ģʽ����
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
    if (!clickable) return;//��
    if (ismouseturn && shadowable[static_cast<size_t>(Actortype::mouse)])//pveģʽ
    {
            shadowable[static_cast<size_t>(Actortype::mouse)] = false;
            isshadowed[static_cast<size_t>(Actortype::mouse)] = true;
            mouseItem->getSprite()->setVisible(false);//�߼���һ��,���úϲ�
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
    if (record->state.empty() || record->state.back().first == "setmouse" || !undoable || !clickable)return;//����Ϸ���
    BGM::press();
    int step = !(Setting::getInstance().getMouse() && Setting::getInstance().getHuman()) + 1;//ΪPVP��ֻ����1��,PVE����
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
    undoable = false;//�Ϸ�������
}

void GameFacade::dealWithMouse(EventMouse *event)
{
    if (!clickable|!Setting::getInstance().getMouse() & !Setting::getInstance().getHuman())return;//��ֹ
    if (ismouseturn && Setting::getInstance().getMouse())
    {
        if (!mousePTurn(event))return;//P�ж�
        if (!Setting::getInstance().getHuman() && clickable)//E�ж�
            humanETurn();
    }
    else if (!ismouseturn&& Setting::getInstance().getHuman())
    {
        if (!humanPTurn(event))return;//P�ж�
        if (!Setting::getInstance().getMouse() && clickable)//E�ж�
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