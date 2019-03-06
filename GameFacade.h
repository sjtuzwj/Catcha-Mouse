#pragma once
#include "cocos2d.h"
#include <vector>
#include <string>
#include <utility>
#include <memory>
#include <queue>
#include <bitset>
#include <iterator>
USING_NS_CC;
using std::vector;
using std::queue;
class Trap;
class Mouse;
class Graph;
class Hole;
class Referee;
class MainScene;
class RecordOriginator;
class DataController;
class RecordController;
class CallbackTimeCounter;
//////////////////////////////////
////各种子系统高度交互的修罗场,里面藏污纳垢
//////////////////////////////////////
class GameFacade final
{
    friend class DataController;
    friend class RecordController;
    friend class Referee;
public:
    static GameFacade& getInstance() {
        static GameFacade instance;
        return instance;
    }
    //接口,对客户端MainScene隐藏子系统
    void init(MainScene*);//这是一个虚假的外观
    void dealWithSave(cocos2d::Ref* pSender);
    void dealWithShadow(cocos2d::Ref* pSender);
    void dealWithRecord(cocos2d::Ref* pSender);
    void dealWithUndo(cocos2d::Ref* pSender);
    void dealWithMouse(cocos2d::EventMouse *event);
private:
    GameFacade()=default;
    ~GameFacade() = default;
    //持有的界面,虽然不是很想拿单例绑定生命周期非全局的对象,但是不用单例构造外观对象也遭罪啊,不绑定传递参数也遭罪啊,我能怎么办啊,我也很绝望啊.
    MainScene* scene;
    ///////////////////////////////////////
    //////////子系统 初始化工具
    ////////////////////////////////////
    //模块化初始工具
    void functionMemberInit();
    void modeInit();//确定复盘/读档/新开
                    //工具函数
    void prepare();//保证玩家可以直接游玩所选身份
    void newGame();
    ///////////////////////////////////////
    ////////子系统 游戏机制
    ///////////////////////////////////
    //回合机制
    int turn;
    bool ismouseturn;
    void addTurn();//每20回合,添加一个洞
    void skipTurn();//EVE
    void skipCurrentTurn();//惩罚机制,20秒不行动跳过当前回合
    void skipHumanTurn();//人惩罚
    void skipMouseTurn();//鼠惩罚
    void humanETurn();
    void mouseETurn();
    bool mousePTurn(cocos2d::EventMouse *event);
    bool humanPTurn(cocos2d::EventMouse *event);
    //判断合法性
    bool undoable;//人操作后才可撤回
    bool clickable;//必须是PV*且没有胜败才可进行鼠标事件
    //特殊道具
    enum class Actortype { mouse, human };//使用可读性更高,名称空间污染更低,类型检测更加严格的枚举类
    std::bitset<2> shadowable;
    std::bitset<2> isshadowed;
    //胜利场景
    void victory();
    void mouseVictory();
    void humanVictory();
    /////////////////////////////////
    //////////子系统 角色
    /////////////////////////////////////////////
    //精灵元素
    std::vector<std::shared_ptr<Trap>> TrapItems;
    std::vector<std::shared_ptr<Hole>> HoleItems;
    std::shared_ptr<Mouse>mouseItem;
    void addRandomHole();//添加洞的工具函数
    ///////////////////////////////////////
    /////////子系统 图
    /////////////////////////////////////////
    std::shared_ptr<Graph> graph;//抽象图模型
    ///////////////////////////////////////////
    //////////子系统 计时
    ///////////////////////////////////////
    //计时器元素
    int cur;//获取空置计时器
    vector<CallbackTimeCounter*>actionCounter;//似乎不能改变自己，所以用互相切换的方式实现循环
    CallbackTimeCounter* timeCounter;
    vector<CallbackTimeCounter*>recordCounter;
    void delayBGM();
    ////////////////////////////////
    ////////子系统 记录
    /////////////////////////////////////
    //游戏记录
    std::shared_ptr<RecordOriginator> record = std::make_shared<RecordOriginator>();
    //重演复盘 涉及到具体渲染过程,因此作为成员被RecordController控制
    void review();
    std::vector<std::pair<std::string, int>>::iterator firstState();//初始化
    void nextStep(std::pair<std::string, int>);//间隔回放
    void lastStep(std::pair<std::string, int > &);
    ////////////////////////
    //天气特效与音效
    //////////////////////////
    void weatherInit();
    enum class Weather { snow = 1, rain, sun };
    ParticleSystem * weatherEmitter;
    Weather weather;
    //////////////////////
    ////////Secret
    //////////////////////////
    enum  class Flagtype { sun };//允许直接作为索引
    std::bitset<4> eggFlag;//0 set
    void easterEgg();
};

