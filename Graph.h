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
    ///////����������ͼģ�� ���ݽṹ����,�䵱�ӿ�
    /////////////////////////////
    class GraphCalculator;
    class Hexagon;
    class Graph  final : public GraphInterface, public Observer//����۲��߽�ɫ,һ���۲��߹۲���Ŀ��
    {
        friend class GraphCalculator;
    private:
        //��������ĳ�Ա
        GraphCalculator calculator;
         //��ͼ��60������������,���ӿ�����
        Hexagon block[60];
        //ά��������Ϣ,���ڿ�����������
        set<int>holes;
        set<int>traps;
        int mouse;
        //�ж��Ƿ����������ڲ�
        static const int maxr = 21;
        //�ж��Ƿ��ڽӵ���ֵ
        static const int maxd = 120;
        //�ڽ�
        bool connected[60][60];
        std::vector<int>& getneighbor(int i) { return block[i].neighbor;}
        //���㹤��
        void setpos(int index, pair<double, double>pos) {
            block[index].setPos(pos);
        }
        void setwhat(std::string msg, int i);
    public:
        Graph();
        ~Graph() = default;
        //ֻ���ӿ�
        pair<double, double>pos(int i) {
            return block[i].getPos();
        }
        bool ishole(int i) { return holes.count(i); }
        bool istrap(int i) { return traps.count(i); }
        bool ismouse(int i) { return i == mouse; }
        bool isempty(int i) { return !holes.count(i) && !traps.count(i) && i != mouse; }
        bool isconnected(int, int);
        //ֻд�ӿ�
        void update(Subject*);
        //ͼ�Ĺ����㷨,���ؼ����ߵĽӿ�
        //���·��
        int randomPath();
        //���·������
        int shortestPath();
        //��ȡλ����������
        int findNearestBlock(std::pair<double, double>& pos);
        //�Ƿ�Ϊ�����ڵ�
        bool findIsolatedBlock(int);
        //�Ƿ�Ϊ�ս�ڵ�
        bool findDeathBlock(int);
    };