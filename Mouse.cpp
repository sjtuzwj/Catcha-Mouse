#include "Mouse.h"
#include "Graph.h"
#include "Hexagon.h"
#include "CreateItem.h"
#include "Prototype.h"
#include "Judge.h"
#include "Model.h"
#include "cocos2d.h"
#include "MainScene.h"
#include "RecordOriginator.h"

USING_NS_CC;

Sprite * Mouse::create(std::shared_ptr<Graph>& graph, int index)
{
    auto sprite = PrototypeDecorator::create(graph, index);
    anime("idle");//初始时就处于闲暇状态
    return sprite;
}

void Mouse::anime(const char* msg) {
    getSprite()->stopAction(getSprite()->getActionByTag(1));//同时只能进行一个动画
    auto animation = Animation::create();
    int framenum=12;
    if (string(msg) == "idle") { animation->setLoops(-1); //一直进行
    framenum = 36;}//帧数不同
    vector<string>frame;
    for (int i = 0; i < framenum; i++) { frame.push_back(string(msg) + std::to_string(i) + ".png");
    animation->addSpriteFrameWithFile(frame[i]);
    }
    animation->setDelayPerUnit(1.0f / 12.0f);//12帧每秒
    auto action = Animate::create(animation);
    action->setTag(1); 
    getSprite()->runAction(action); 
}

void Mouse::move(std::shared_ptr<Graph>& graph, int index) {
    setState(getMsg(), index);
    setState(std::string("r") + getMsg(), getIndex());
    setIndex(index);
    setPos(graph->pos(index));
    auto moveTo = MoveTo::create(1, Vec2(getPos().first, getPos().second));
    getSprite()->runAction(moveTo);
}
/////////////////////////////
////Click
///////////////////////////
bool Mouse::clickIndexIllegal(std::shared_ptr<Graph>& graph, int index)
{
    return index == -1 ||
        graph->istrap(index) ||
        graph->ismouse(index) ||
        !graph->isconnected(index, getIndex());
}

void Mouse::doWithClickIndex(std::shared_ptr<Graph>& graph, int index)
{
    move(graph, index);
}

////////////////////////////////
////////Random
////////////////////////////////////
int Mouse::getRandomIndex(std::shared_ptr<Graph>& graph) {
    return Judge::getInstance().judgeProperPos(graph);
}

void  Mouse::doWithRandomIndex(std::shared_ptr<Graph>& graph, int index) {
    create(graph, index);
}

////////////////////////////////
//////Autoset
/////////////////////////////////
bool Mouse::nextIndexIllegal(std::shared_ptr<Graph>& graph, int next) {
    return next==-1;
}

int Mouse::doWithIllegalNextIndex(std::shared_ptr<Graph>& graph) {
    return getIndex();
}

void Mouse::doWithNextIndex(std::shared_ptr<Graph>& graph, int next) {
    move(graph, next);
}