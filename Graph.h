#pragma once
#include <utility>
#include <queue>
#include <vector>
#include <set>
#include "Hexagon.h"
#include "GraphInterface.h"
#include "Observer.h"
#include "GraphCalculator.h"
    using std::queue;
    using std::vector;
    using std::set;
    using std::pair;
    //////////////////////////////////////
    ///////六边形无向图模型 数据结构本身,充当接口
    /////////////////////////////
    class GraphCalculator;
    class Hexagon;
    class Graph  final : public GraphInterface, public Observer//具体观察者角色,一个观察者观察多个目标
    {
        friend class GraphCalculator;
    private:
        //代理操作的成员
        GraphCalculator calculator;
         //地图的60个六边形区块,被接口隐藏
        Hexagon block[60];
        //维护抽象信息,现在看出作用来了
        set<int>holes;
        set<int>traps;
        int mouse;
        //判断是否在六边形内部
        static const int maxr = 21;
        //判断是否邻接的阈值
        static const int maxd = 120;
        //邻接
        bool connected[60][60];
        std::vector<int>& getneighbor(int i) { return block[i].neighbor;}
        //计算工具
        void setpos(int index, pair<double, double>pos) {
            block[index].setPos(pos);
        }
        void setwhat(std::string msg, int i);
    public:
        Graph();
        ~Graph() = default;
        //只读接口
        pair<double, double>pos(int i) {
            return block[i].getPos();
        }
        bool ishole(int i) { return holes.count(i); }
        bool istrap(int i) { return traps.count(i); }
        bool ismouse(int i) { return i == mouse; }
        bool isempty(int i) { return !holes.count(i) && !traps.count(i) && i != mouse; }
        bool isconnected(int, int);
        //只写接口
        void update(Subject*);
        //图的公开算法,隐藏计算者的接口
        //随机路径
        int randomPath();
        //最短路径查找
        int shortestPath();
        //获取位置所在区块
        int findNearestBlock(std::pair<double, double>& pos);
        //是否为孤立节点
        bool findIsolatedBlock(int);
        //是否为终结节点
        bool findDeathBlock(int);
    };