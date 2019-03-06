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
////������ϵͳ�߶Ƚ��������޳�,��������ɹ�
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
    //�ӿ�,�Կͻ���MainScene������ϵͳ
    void init(MainScene*);//����һ����ٵ����
    void dealWithSave(cocos2d::Ref* pSender);
    void dealWithShadow(cocos2d::Ref* pSender);
    void dealWithRecord(cocos2d::Ref* pSender);
    void dealWithUndo(cocos2d::Ref* pSender);
    void dealWithMouse(cocos2d::EventMouse *event);
private:
    GameFacade()=default;
    ~GameFacade() = default;
    //���еĽ���,��Ȼ���Ǻ����õ������������ڷ�ȫ�ֵĶ���,���ǲ��õ���������۶���Ҳ���ﰡ,���󶨴��ݲ���Ҳ���ﰡ,������ô�찡,��Ҳ�ܾ�����.
    MainScene* scene;
    ///////////////////////////////////////
    //////////��ϵͳ ��ʼ������
    ////////////////////////////////////
    //ģ�黯��ʼ����
    void functionMemberInit();
    void modeInit();//ȷ������/����/�¿�
                    //���ߺ���
    void prepare();//��֤��ҿ���ֱ��������ѡ���
    void newGame();
    ///////////////////////////////////////
    ////////��ϵͳ ��Ϸ����
    ///////////////////////////////////
    //�غϻ���
    int turn;
    bool ismouseturn;
    void addTurn();//ÿ20�غ�,���һ����
    void skipTurn();//EVE
    void skipCurrentTurn();//�ͷ�����,20�벻�ж�������ǰ�غ�
    void skipHumanTurn();//�˳ͷ�
    void skipMouseTurn();//��ͷ�
    void humanETurn();
    void mouseETurn();
    bool mousePTurn(cocos2d::EventMouse *event);
    bool humanPTurn(cocos2d::EventMouse *event);
    //�жϺϷ���
    bool undoable;//�˲�����ſɳ���
    bool clickable;//������PV*��û��ʤ�ܲſɽ�������¼�
    //�������
    enum class Actortype { mouse, human };//ʹ�ÿɶ��Ը���,���ƿռ���Ⱦ����,���ͼ������ϸ��ö����
    std::bitset<2> shadowable;
    std::bitset<2> isshadowed;
    //ʤ������
    void victory();
    void mouseVictory();
    void humanVictory();
    /////////////////////////////////
    //////////��ϵͳ ��ɫ
    /////////////////////////////////////////////
    //����Ԫ��
    std::vector<std::shared_ptr<Trap>> TrapItems;
    std::vector<std::shared_ptr<Hole>> HoleItems;
    std::shared_ptr<Mouse>mouseItem;
    void addRandomHole();//��Ӷ��Ĺ��ߺ���
    ///////////////////////////////////////
    /////////��ϵͳ ͼ
    /////////////////////////////////////////
    std::shared_ptr<Graph> graph;//����ͼģ��
    ///////////////////////////////////////////
    //////////��ϵͳ ��ʱ
    ///////////////////////////////////////
    //��ʱ��Ԫ��
    int cur;//��ȡ���ü�ʱ��
    vector<CallbackTimeCounter*>actionCounter;//�ƺ����ܸı��Լ��������û����л��ķ�ʽʵ��ѭ��
    CallbackTimeCounter* timeCounter;
    vector<CallbackTimeCounter*>recordCounter;
    void delayBGM();
    ////////////////////////////////
    ////////��ϵͳ ��¼
    /////////////////////////////////////
    //��Ϸ��¼
    std::shared_ptr<RecordOriginator> record = std::make_shared<RecordOriginator>();
    //���ݸ��� �漰��������Ⱦ����,�����Ϊ��Ա��RecordController����
    void review();
    std::vector<std::pair<std::string, int>>::iterator firstState();//��ʼ��
    void nextStep(std::pair<std::string, int>);//����ط�
    void lastStep(std::pair<std::string, int > &);
    ////////////////////////
    //������Ч����Ч
    //////////////////////////
    void weatherInit();
    enum class Weather { snow = 1, rain, sun };
    ParticleSystem * weatherEmitter;
    Weather weather;
    //////////////////////
    ////////Secret
    //////////////////////////
    enum  class Flagtype { sun };//����ֱ����Ϊ����
    std::bitset<4> eggFlag;//0 set
    void easterEgg();
};

