#include "DataController.h"
#include "GameFacade.h"
#include "Trap.h"
#include "MainScene.h"
#include "Mouse.h"
#include "Prototype.h"
#include "Hole.h"
#include "Graph.h"
#include "RecordOriginator.h"
#include "RecordMemento.h"
#include "Setting.h"
USING_NS_CC;
using std::to_string;
using std::string;
    ///////////////////////////////////////////////////////////////////////
    ////////丑陋的代码,状态在外部生成,但是需求不需要内部保存状态,所以就这样了///
    //////////////////////////////////////////////////////////////////////

    void DataController::saveFlag(GameFacade* scene)
    {
        UserDefault::getInstance()->setBoolForKey("saved", true);
        UserDefault::getInstance()->setIntegerForKey("turn", scene->turn);
        UserDefault::getInstance()->setBoolForKey("ismouseturn", scene->ismouseturn);
        UserDefault::getInstance()->setBoolForKey("mouseshadowable", scene->shadowable[0]);
        UserDefault::getInstance()->setBoolForKey("humanshadowable", scene->shadowable[1]);
        UserDefault::getInstance()->setBoolForKey("mouseisshadowed", scene->isshadowed[0]);
        UserDefault::getInstance()->setBoolForKey("humanisshadowed", scene->isshadowed[1]);
    }

    void DataController::saveMember(GameFacade* scene)
    {
        UserDefault::getInstance()->setIntegerForKey("mouse", scene->mouseItem->getIndex());
        int holenum = scene->HoleItems.size();
        UserDefault::getInstance()->setIntegerForKey("holenum", holenum);
        for (auto&x : scene->HoleItems)
        {
            int index = x->getIndex();
            string holename = string("hole") + to_string(holenum--);
            UserDefault::getInstance()->setIntegerForKey(holename.c_str(), index);
        }
        int trapnum = scene->TrapItems.size();
        UserDefault::getInstance()->setIntegerForKey("trapnum", scene->TrapItems.size());
        for (auto&x : scene->TrapItems)
        {
            int index = x->getIndex();
            string trapname = string("trap") + to_string(trapnum--);
            UserDefault::getInstance()->setIntegerForKey(trapname.c_str(), index);
        }
    }

    void DataController::save(GameFacade* scene)
    {
        scene->record->createMemento("save");//原发器进行存储
        saveFlag(scene);
        saveMember(scene);
    }

    void DataController::loadFlag(GameFacade* scene)
    {
        scene->turn = UserDefault::getInstance()->getIntegerForKey("turn");
        scene->ismouseturn = UserDefault::getInstance()->getBoolForKey("ismouseturn");
        scene->shadowable[0] = UserDefault::getInstance()->getBoolForKey("mouseshadowable");
        scene->shadowable[1] = UserDefault::getInstance()->getBoolForKey("humanshadowable");
        scene->isshadowed[0] = UserDefault::getInstance()->getBoolForKey("mouseisshadowed");
        scene->isshadowed[1] = UserDefault::getInstance()->getBoolForKey("humanisshadowed");
    }

    void DataController::loadMember(GameFacade* game)
    {
        auto mouseindex = UserDefault::getInstance()->getIntegerForKey("mouse");
        game->mouseItem = std::make_shared<Mouse>(Prototype::create("mouse"));
        game->mouseItem->create(game->graph, mouseindex);
        if (game->isshadowed[0])game->mouseItem->getSprite()->setVisible(false);
        game->scene->addChild(game->mouseItem->getSprite(), 2);
        int holenum = UserDefault::getInstance()->getIntegerForKey("holenum");
        for (int i = 1; i <= holenum; i++)
        {
            string holename = string("hole") + to_string(i);
            int index = UserDefault::getInstance()->getIntegerForKey(holename.c_str());
            auto hole = std::make_shared<Hole>(Prototype::create("hole"));
            hole->create(game->graph, index);
            game->scene->addChild(hole->getSprite(), 2);
            game->HoleItems.push_back(hole);
        }
        int trapnum = UserDefault::getInstance()->getIntegerForKey("trapnum");
        for (int i = 1; i <= trapnum; i++)
        {
            string trapname = string("trap") + to_string(i);
            int index = UserDefault::getInstance()->getIntegerForKey(trapname.c_str());
            auto trap = std::make_shared<Trap>(Prototype::create("trap"));
            trap->create(game->graph, index);
            game->scene->addChild(trap->getSprite(), 2);
            game->TrapItems.push_back(trap);
        }
        if (game->isshadowed[1])game->TrapItems.back()->getSprite()->setVisible(false);
    }

    void DataController::load(GameFacade* scene)
    {
        auto savereview= std::make_shared<RecordMemento>("save");//不提供状态,则从本地获取
        scene->record->restoreToMemento(savereview);
        loadFlag(scene);
        loadMember(scene);
    }
