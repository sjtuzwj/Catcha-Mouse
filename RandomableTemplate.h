#pragma once
#include <memory>

class Graph;
class RandomableTemplate
{
public:
    //Ëæ»ú´´½¨
    void random(std::shared_ptr<Graph>& graph);
protected:
    virtual int getRandomIndex(std::shared_ptr<Graph>& graph) = 0;
    virtual void doWithRandomIndex(std::shared_ptr<Graph>& graph, int) = 0;
};