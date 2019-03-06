#pragma once
#include<string>
#include<utility>
#include<vector>
    using std::pair;
    ////////////////////////////
    ///////六边形模型,接口仅对Graph开放,对外隐藏
    ///////////////////////////////
    class Hexagon final
    {
        friend class Graph;
    private:
        ~Hexagon() = default;
        Hexagon() = default;
        //读写接口
        void setPos(pair<double, double>newposition) { position = newposition; }
        pair<double, double>getPos() {
            return position;
        }
        std::vector<int> getneighbor() { return neighbor; }
        //成员信息
        std::vector<int>neighbor;//返回相邻节点
        pair<double, double> position;
    };
