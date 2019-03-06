#include "Graph.h"
#include "Setting.h"
#include "GraphCalculator.h"
#include "Hexagon.h"
#include "Subject.h"
#include <algorithm>
    using std::pair;
    Graph::Graph()
    {
        calculator.init(this);
    }

    int Graph::findNearestBlock(std::pair<double, double>& pos)
    {
        return calculator.findNearestBlock(pos);
    }

    bool Graph::findIsolatedBlock(int index) {
        return calculator.findIsolatedBlock(index);
    }

    bool Graph::findDeathBlock(int index) {
        return calculator.findDeathBlock(index);
    }

    bool Graph::isconnected(int ind1, int ind2)
    {
        return connected[ind1][ind2];
    }

    int Graph::randomPath()
    {
        return calculator.randomPath();
    }

    int Graph::shortestPath() {
        return calculator.shortestPath();
    }

    void Graph::update(Subject* subject)
    {
        auto state = subject->getState();
        setwhat(state.first, state.second);
    }

    void Graph::setwhat(std::string msg, int i) 
    {
        if (msg == "mouse")mouse = i;
        else if (msg == "hole")holes.insert(i);
        else if (msg == "trap")traps.insert(i);
        else if (msg == "rhole")holes.erase(i);
        else if (msg == "rtrap")traps.erase(i);
    }