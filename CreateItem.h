#pragma once
#include "cocos2d.h"
#include <string>
    ////////////////////////////ItemFunction::
    ////��ͬ�����з�������Ԫ�صĹ��ߺ���
    /////////////////////////
using cocos2d::Sprite;
using cocos2d::Node;
using cocos2d::MenuItemImage;
class ItemFunction
{
private:
    ////����
    static void setadapt(Sprite* sprite, double scale);//����Ļ��Ӧ
    ItemFunction() = delete;
public:

    ////����
    static Sprite* createSprite(std::string& name);

    static Sprite* createHelloWorld();//��ף�����Լ���Ϸ���������γ���

    static Sprite* createBackground(std::string& msg);

    template<typename Func>
    static MenuItemImage* createMenu(std::string& name, Func& function)
    {
        auto Item = MenuItemImage::create(
            name,
            name,
            function);
        Item->setScale(Setting::getInstance().getItemScale()); //���ÿ�����ű���
        return Item;
    }
    ////����λ��,ʹ��Node����ָ��ָ������������
    static void puttop(Node* item);

    static void putmid(Node* item);

    static void putbottom(Node* item);

    static void putrighttop(Node* item);

    static void putlefttop(Node* item);

    static void putdown(Node* item);

    ////���λ��,ʹ��Node����ָ��ָ������������
    static void putbyup(Node* item,int distance);

    static void putbyleft(Node* item, int distance);

    static void putbyright(Node* item, int distance);

    static void putbydown(Node* item, int distance);

};