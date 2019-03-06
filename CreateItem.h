#pragma once
#include "cocos2d.h"
#include <string>
    ////////////////////////////ItemFunction::
    ////不同场景中反复出现元素的工具函数
    /////////////////////////
using cocos2d::Sprite;
using cocos2d::Node;
using cocos2d::MenuItemImage;
class ItemFunction
{
private:
    ////比例
    static void setadapt(Sprite* sprite, double scale);//与屏幕适应
    ItemFunction() = delete;
public:

    ////创建
    static Sprite* createSprite(std::string& name);

    static Sprite* createHelloWorld();//庆祝界面以及游戏引导界面多次出现

    static Sprite* createBackground(std::string& msg);

    template<typename Func>
    static MenuItemImage* createMenu(std::string& name, Func& function)
    {
        auto Item = MenuItemImage::create(
            name,
            name,
            function);
        Item->setScale(Setting::getInstance().getItemScale()); //设置宽度缩放比例
        return Item;
    }
    ////绝对位置,使用Node基类指针指向所有派生类
    static void puttop(Node* item);

    static void putmid(Node* item);

    static void putbottom(Node* item);

    static void putrighttop(Node* item);

    static void putlefttop(Node* item);

    static void putdown(Node* item);

    ////相对位置,使用Node基类指针指向所有派生类
    static void putbyup(Node* item,int distance);

    static void putbyleft(Node* item, int distance);

    static void putbyright(Node* item, int distance);

    static void putbydown(Node* item, int distance);

};