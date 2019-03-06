#include "GraphCalculator.h"
#include "Graph.h"
#include "Hexagon.h"
#include "Setting.h"


void GraphCalculator::init(Graph* binding) {
    graph = binding;
    initblock();
    initconnect();
}

void GraphCalculator::initblock() {
    auto setting = Setting::getInstance();
    for (int i = 0; i < 60; i++)
        graph->setpos(i,setting.blockInfo[i]);
}

void GraphCalculator::initconnect() {
    for (int i = 0; i < 60; i++)
        for (int j = i + 1; j < 60; j++)
        {
            if (distance(graph->pos(i), graph->pos(j)) < 100)
            {
                graph->connected[i][j] = graph->connected[j][i] = true;
                graph->getneighbor(i).push_back(j);
                graph->getneighbor(j).push_back(i);
            }
            else graph->connected[i][j] = graph->connected[j][i] = false;
        }
}

double GraphCalculator::sqr(double x)const {
    return x * x;
}

double  GraphCalculator::distance(int index1, int index2)
{ return distance(graph->pos(index1), graph->pos(index2)); }

double GraphCalculator::distance(pair<double, double>&lhs, pair<double, double>&rhs) {
    return sqrt(sqr(lhs.first - rhs.first) + sqr(lhs.second - rhs.second));
}

int GraphCalculator::randomPath() {
    int origin = graph->mouse;
    int next = -1;
    for (auto & x:graph->getneighbor(origin))
        if (graph->isempty(x))
        {
            next = x;//挑选第一条可选择的道路
            break;
        }
    return next;
}

int GraphCalculator::shortestPath() {
    int origin = graph->mouse;
    queue<int> Q;//到达该顶点最短路径已知么
    vector<int> edgeTo(60);//最后一个顶点
    vector<int> Holes;//所有洞
    bool marked[60];
    breathFirstSearch(Holes, edgeTo, marked, origin, Q);
    return findMinPath(Holes, edgeTo,marked,origin);
}

int GraphCalculator::findNearestBlock(std::pair<double, double>& pos) {
    int index = 0;
    for (int i = 0; i < 60; i++)
    {
        if (distance(pos, graph->pos(i)) <= graph->maxr) {
            index = i; break;
        }
        if (i == 59)return -1;
    }
    return index;
}

bool GraphCalculator::findIsolatedBlock(int index) {
    for (auto& x : graph->getneighbor(index))
    {
        if (graph->ishole(x))return false;
        for(auto & y:graph->getneighbor(x))
            if (graph->ishole(y))return false;
    }
    return true;
}

bool GraphCalculator::findDeathBlock(int index) {

    bool life = false;
    for (int i = 0; i < 60; i++)
    {
        if (i != index && graph->isconnected(i, index) && !graph->istrap(i))
            life = true;
    }
    return life;
}

int GraphCalculator::findMinPath(const vector<int>& Holes,const vector<int>& edgeTo, bool marked[],int origin)
{
    int i = 0;
    int min = INT_MAX;
    int minindex = -1;
    for (auto x : Holes)
    {
        if (marked[x])
        {
            i = 0;
            while (!graph->isconnected(x, origin))//终止节点为与起点相邻
            {
                x = edgeTo[x];
                i++;
            }
            if (i < min) { min = i; minindex = x; }
        }
    }
    return minindex;
}

void GraphCalculator::breathFirstSearch(vector<int>& Holes, vector<int>& edgeTo, bool marked[], int origin, queue<int>& Q)
{
    for (int i = 0; i < 60; i++)
    {
        if (graph->ismouse(i) || graph->istrap(i))marked[i] = 1;
        else
        {
            if (graph->ishole(i))Holes.push_back(i);
            marked[i] = 0;
        }
    }
    Q.push(origin);
    while (!Q.empty())
    {
        int v = Q.front();
        Q.pop();
        for (auto& w : graph->getneighbor(v))
            if (!marked[w])
            {
                edgeTo[w] = v;
                marked[w] = true;
                Q.push(w);
            }
    }
}