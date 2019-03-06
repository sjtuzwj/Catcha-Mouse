#include "cocos2d.h"
#include "RandomableTemplate.h"
#include "AutosetableTemplate.h"
#include "ClickableTemplate.h"
#include "Judge.h"

void AutosetableTemplate::autoset(std::shared_ptr<Graph>& graph)
{
    int next = Judge::getInstance().judgeClosestPos(graph);//���·��
    if (nextIndexIllegal(graph, next))//���Ϸ���
        next = doWithIllegalNextIndex(graph);//�����쳣
    doWithNextIndex(graph, next);//�������·������������Ϊ
}

bool ClickableTemplate::click(std::shared_ptr<Graph>& graph, cocos2d::EventMouse *event)
{
    auto index = Judge::getInstance().judgeClickPos(event, graph);//�������
    if (clickIndexIllegal(graph, index))return false;//���Ϸ���
    doWithClickIndex(graph, index);//���ݵ��������Ϊ
    return true;
}

void RandomableTemplate::random(std::shared_ptr<Graph>& graph) {
    int index = getRandomIndex(graph);//��ȡ�������
    doWithRandomIndex(graph, index);//�����漴���������ж�
}