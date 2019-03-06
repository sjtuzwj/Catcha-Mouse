#pragma once
#include <utility>
#include <queue>
#include <vector>
#include "GraphInterface.h"
class Graph;
using std::queue;
using std::vector;
using std::pair;
//图的计算库,与Graph共享接口
//就算只需要一个实例,也不应该绑定到非全局的作用域,去单例化
class GraphCalculator final : public GraphInterface
{
    friend class Graph;
private:
    //怎样不开放权限只对Graph开放创建
    GraphCalculator() = default;
    ~GraphCalculator() = default;
    //初始化
    void init(Graph*);
    int randomPath();//随机路径
    int shortestPath();//最短路径查找
    int findNearestBlock(std::pair<double, double>& pos);//获取位置所在区块
    bool findIsolatedBlock(int);
    bool findDeathBlock(int);
//不共享接口,工具函数被隐藏
    //绑定的图,确保只有一个图进行运算
    Graph * graph;
    void initblock();
    void initconnect();
    //数学工具函数
    double sqr(double x)const;
    double distance(pair<double, double>&lhs, pair<double, double>&rhs);
    double distance(int index1, int index2);
    //图的计算库
    void breathFirstSearch(vector<int>&, vector<int>&, bool[], int, queue<int>&);
    int findMinPath(const vector<int>&,const vector<int>&,bool[],int);//工具,根据广度优先搜索结果最短路径
};

