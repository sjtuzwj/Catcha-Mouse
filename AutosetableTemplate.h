#pragma once
#include <memory>

class Graph;
class AutosetableTemplate
{
public:
    //�Զ��ж�
    void autoset(std::shared_ptr<Graph>& graph);
protected:
    virtual bool nextIndexIllegal(std::shared_ptr<Graph>& graph, int) = 0;
    //���ڷǷ��������д���
    virtual int doWithIllegalNextIndex(std::shared_ptr<Graph>& graph) = 0;
    virtual void doWithNextIndex(std::shared_ptr<Graph>& graph, int) = 0;
};
