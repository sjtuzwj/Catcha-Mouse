#pragma once
#include "cocos2d.h"
#include "Model.h"
#include "PrototypeInterface.h"
#include <utility>
#include <string>
#include <vector>
#include <list>
#include <algorithm>

    ///////////////////////////////////
    ///////���о���ԭ��,�洢ʵ��
    ///////////////////////////////
    using cocos2d::Sprite;
    using std::pair;
    using std::string;
    class Graph;
    class Prototype final:public PrototypeInterface//���ɱ�Ĳ�����ɱ�Ĳ��ַ���,ͬʱ��Ϊ���������ɫ����
    {
    private:
        //����Ŀ�굽�۲���֮���ӳ��
        std::list<std::shared_ptr<Observer>> observer; //��׷�����ɾ���ĸ�У,��ȡ����
        //״̬�ı�
        std::pair < std::string, int >state;
        //����
        SpriteModel model;
        //��ͼ
        Sprite* sprite;
        virtual ~Prototype() = default;
        Prototype() = delete;//�޷���������Ϣ��ʵ��
        Prototype(char* omsg) :model(omsg) {}//װ����
        virtual void notify();//��ֹ���ֶ�����
    public:
        static std::shared_ptr<PrototypeInterface> create(char*);//��̬�������ɱ��̳�
        //����������
        virtual Sprite * create(std::shared_ptr<Graph>& graph, int index);//����֪ͨ
        virtual void destroy();//����֪ͨ
        //��ϣ������д��Ĭ��ʵ��,�ӿ�
        const pair<double, double> getPos()const  noexcept { return model.pos; }
        const int getIndex()const noexcept { return model.index; }
        Sprite* getSprite()const  noexcept { return sprite; }
        std::string getMsg()const noexcept { return model.msg; }
        void setPos(const std::pair<double, double>rpos)  noexcept { model.pos = rpos; }
        void setIndex(const int rindex) noexcept { if (rindex < 60 && rindex>0)model.index = rindex; }
        //�۲���ģʽ�ӿ�
        virtual void attach(std::shared_ptr<Observer> link){observer.push_back(link);}
        virtual void detach(std::shared_ptr<Observer> delink)
        {observer.erase(find(observer.begin(),observer.end(),delink)); }
        virtual std::pair < std::string, int > getState() { return state; }
        virtual void setState(string msg, int index) { state = std::make_pair(msg, index); notify(); }//��״̬�趨�����Զ�����
    };
