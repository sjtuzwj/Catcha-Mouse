#include "RecordOriginator.h"

void RecordOriginator::restoreToMemento(std::shared_ptr<RecordMemento> pMemento)
{
    state.clear();
    state = pMemento->getState();
}

std::shared_ptr<RecordMemento> RecordOriginator::createMemento(string msg)
{
    auto ptr= std::make_shared<RecordMemento>(state,msg);
    return ptr;
}

std::vector<std::pair<std::string, int>>& RecordOriginator::getState()
{
    return state;
}

void RecordOriginator::setState(std::vector<std::pair<std::string, int>>& st)
{
    state = st;
}