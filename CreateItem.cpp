#include "CreateItem.h"
#include "cocos2d.h"
#include "Setting.h"
using namespace cocos2d;
Sprite* ItemFunction:: createSprite(std::string& msg)
    {
        Sprite* sprite;
        if (Setting::getInstance().getDark())
            sprite = Sprite::create(msg + "Dark.png");
        else
            sprite = Sprite::create(msg + ".png");
        sprite->setScale(Setting::getInstance().getItemScale()); //设置精灵宽度缩放比例
        return sprite;

    }

    Sprite* ItemFunction::createHelloWorld()//庆祝界面以及游戏引导界面多次出现
    {
        auto helloworld =
            createSprite(std::string("HelloWorld"));
        putmid(helloworld);
        setadapt(helloworld, 0.8);
        return helloworld;
    }

    Sprite* ItemFunction::createBackground(std::string& msg)//背景多次出现
    {
        auto background =
            createSprite(msg + "Back");
        putmid(background);
        setadapt(background, 1);
        return background;
    }

    void ItemFunction::setadapt(Sprite* sprite, double scale)
    {

        Size mywinsize = Director::getInstance()->getWinSize();
        double winw = mywinsize.width; //获取屏幕宽度
        double winh = mywinsize.height;//获取屏幕高度
        double spx = sprite->getTextureRect().getMaxX();
        double spy = sprite->getTextureRect().getMaxY();
        sprite->setScaleX(winw / spx * scale); //设置精灵缩放比例
        sprite->setScaleY(winh / spy * scale);
    }

    void ItemFunction::putmid(Node* item)
    {
        auto visibleSize = Director::getInstance()->getVisibleSize();
        Vec2 origin = Director::getInstance()->getVisibleOrigin();
        item->setPosition(Vec2(
            visibleSize.width / 2 + origin.x,
            visibleSize.height / 2 + origin.y));
    }

    void ItemFunction::puttop(Node* item)
    {
        auto visibleSize = Director::getInstance()->getVisibleSize();
        Vec2 origin = Director::getInstance()->getVisibleOrigin();
        item->setPosition(Vec2(
            visibleSize.width / 2 + origin.x,
            origin.y + visibleSize.height - Setting::getInstance().getItemHeight() / 2));
    }

    void ItemFunction::putbottom(Node* item) {
        auto visibleSize = Director::getInstance()->getVisibleSize();
        Vec2 origin = Director::getInstance()->getVisibleOrigin();
        item->setPosition(Vec2(
            origin.x + visibleSize.width / 2,
            origin.y + Setting::getInstance().getItemHeight() / 2 ));
    }

    void ItemFunction::putrighttop(Node* item)
    {
        auto visibleSize = Director::getInstance()->getVisibleSize();
        Vec2 origin = Director::getInstance()->getVisibleOrigin();
        item->setPosition(Vec2(
            origin.x + visibleSize.width - Setting::getInstance().getItemWidth() / 2,
            origin.y + visibleSize.height - Setting::getInstance().getItemHeight() / 2));
    }

    void ItemFunction::putlefttop(Node* item)
    {
        auto visibleSize = Director::getInstance()->getVisibleSize();
        Vec2 origin = Director::getInstance()->getVisibleOrigin();
        item->setPosition(Vec2(
            origin.x + Setting::getInstance().getItemWidth() / 2,
            origin.y + visibleSize.height - Setting::getInstance().getItemHeight() / 2));
    }

    void ItemFunction::putdown(Node* item) {//  quarter of the scene
        auto visibleSize = Director::getInstance()->getVisibleSize();
        Vec2 origin = Director::getInstance()->getVisibleOrigin();
        item->setPosition(Vec2(
            visibleSize.width / 2 + origin.x,
            visibleSize.height / 4 + origin.y));
    }


    void ItemFunction::putbyup(Node* item, int distance) {//  quarter of the scene
        item->setPositionY(item->getPositionY() + distance * Setting::getInstance().getItemHeight());
    }


    void ItemFunction::putbydown(Node* item, int distance) {//  quarter of the scene
        item->setPositionY(item->getPositionY() - distance * Setting::getInstance().getItemHeight());
    }

    void ItemFunction::putbyleft(Node* item, int distance) {//  quarter of the scene
        item->setPositionX(item->getPositionX() - distance * Setting::getInstance().getItemWidth());
    }

    void ItemFunction::putbyright(Node* item, int distance) {//  quarter of the scene
        item->setPositionX(item->getPositionX() + distance * Setting::getInstance().getItemWidth());
    }