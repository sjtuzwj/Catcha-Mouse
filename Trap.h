#pragma once
#include "cocos2d.h"
#include "CreateItem.h"
#include "Model.h"
#include "PrototypeDecorator.h"
#include "AutosetableTemplate.h"
#include "ClickableTemplate.h"
    //�������
    //��ԭ�ͽ���װ��
using cocos2d::Sprite;
    class Trap final : public PrototypeDecorator,public ClickableTemplate,public AutosetableTemplate
    {
        //Click
        virtual bool clickIndexIllegal(std::shared_ptr<Graph>& graph, int);
        virtual void doWithClickIndex(std::shared_ptr<Graph>& graph, int);
        //Autoset
        virtual bool nextIndexIllegal(std::shared_ptr<Graph>& graph, int);
        virtual int doWithIllegalNextIndex(std::shared_ptr<Graph>& graph);
        virtual void doWithNextIndex(std::shared_ptr<Graph>& graph, int);
    public:
        virtual ~Trap() = default;
        Trap() = delete;
        using PrototypeDecorator::PrototypeDecorator;//�̳й��캯��
    };