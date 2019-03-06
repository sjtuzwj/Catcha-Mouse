#pragma once

#include <utility>
using std::pair;
//////////////////////////////////////
//////定义了图的统一接口
/////////////////////////////
class GraphInterface
{
public:
    //随机路径
    virtual int randomPath()=0;
    //最短路径查找
    virtual int shortestPath()=0;
    //获取位置所在区块
    virtual int findNearestBlock(std::pair<double, double>& pos) = 0;
    //是否为孤立节点
    virtual bool findIsolatedBlock(int) = 0;
    //是否为终结节点
    virtual bool findDeathBlock(int) = 0;
};