#pragma once

#include "cocos2d.h"
#include "PrototypeDecorator.h"
#include "RandomableTemplate.h"
#include "AutosetableTemplate.h"
#include "ClickableTemplate.h"

               //������
               //��ԭ�ͽ���װ��
    class Mouse final: public PrototypeDecorator,public RandomableTemplate, public AutosetableTemplate, public ClickableTemplate
    {
    private:
        virtual void destroy(std::shared_ptr<Graph>& graph) {}//����
        //Click
        virtual bool clickIndexIllegal(std::shared_ptr<Graph>& graph, int);
        virtual void doWithClickIndex(std::shared_ptr<Graph>& graph, int);
        //Random
        virtual int getRandomIndex(std::shared_ptr<Graph>& graph);
        virtual void doWithRandomIndex(std::shared_ptr<Graph>& graph, int);
        //Autoset
        virtual bool nextIndexIllegal(std::shared_ptr<Graph>& graph,int);
        virtual int doWithIllegalNextIndex(std::shared_ptr<Graph>& graph);
        virtual void doWithNextIndex(std::shared_ptr<Graph>& graph, int);
    public:
        Mouse() = delete;
        virtual ~Mouse() = default;
        using PrototypeDecorator::PrototypeDecorator;//�̳й��캯��
         //overwrite//����֪ͨ
        virtual Sprite * create(std::shared_ptr<Graph>& graph, int index);//����֪ͨ
        //////���ݴ�����ַ���,ִ����Ծ �붴 ��Ͼ���ֶ���
        void anime(const char*);
        //�ƶ���ͼ��ָ��������,����֪ͨ
        void move(std::shared_ptr<Graph>& graph, int index);
    };