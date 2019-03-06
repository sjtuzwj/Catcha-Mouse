#pragma once
#include "cocos2d.h"
#include "PrototypeDecorator.h"
#include "RandomableTemplate.h"
class Graph;
    //����
    //��ԭ�ͽ���װ��
    class Hole final : public PrototypeDecorator, public RandomableTemplate
    {
        //Random
        virtual int getRandomIndex(std::shared_ptr<Graph>& graph);
        virtual void doWithRandomIndex(std::shared_ptr<Graph>& graph, int);
    public:
        virtual ~Hole() = default;
        Hole() = delete;
        using PrototypeDecorator::PrototypeDecorator;//�̳й��캯��
        virtual Sprite * create(std::shared_ptr<Graph>& graph, int index);//overwrite//����֪ͨ
    };