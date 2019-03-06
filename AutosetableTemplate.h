#pragma once
#include <memory>

class Graph;
class AutosetableTemplate
{
public:
    //自动行动
    void autoset(std::shared_ptr<Graph>& graph);
protected:
    virtual bool nextIndexIllegal(std::shared_ptr<Graph>& graph, int) = 0;
    //对于非法索引进行处理
    virtual int doWithIllegalNextIndex(std::shared_ptr<Graph>& graph) = 0;
    virtual void doWithNextIndex(std::shared_ptr<Graph>& graph, int) = 0;
};
