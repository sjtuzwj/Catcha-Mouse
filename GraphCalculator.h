#pragma once
#include <utility>
#include <queue>
#include <vector>
#include "GraphInterface.h"
class Graph;
using std::queue;
using std::vector;
using std::pair;
//ͼ�ļ����,��Graph����ӿ�
//����ֻ��Ҫһ��ʵ��,Ҳ��Ӧ�ð󶨵���ȫ�ֵ�������,ȥ������
class GraphCalculator final : public GraphInterface
{
    friend class Graph;
private:
    //����������Ȩ��ֻ��Graph���Ŵ���
    GraphCalculator() = default;
    ~GraphCalculator() = default;
    //��ʼ��
    void init(Graph*);
    int randomPath();//���·��
    int shortestPath();//���·������
    int findNearestBlock(std::pair<double, double>& pos);//��ȡλ����������
    bool findIsolatedBlock(int);
    bool findDeathBlock(int);
//������ӿ�,���ߺ���������
    //�󶨵�ͼ,ȷ��ֻ��һ��ͼ��������
    Graph * graph;
    void initblock();
    void initconnect();
    //��ѧ���ߺ���
    double sqr(double x)const;
    double distance(pair<double, double>&lhs, pair<double, double>&rhs);
    double distance(int index1, int index2);
    //ͼ�ļ����
    void breathFirstSearch(vector<int>&, vector<int>&, bool[], int, queue<int>&);
    int findMinPath(const vector<int>&,const vector<int>&,bool[],int);//����,���ݹ����������������·��
};

