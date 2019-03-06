#include "RecordMemento.h"
USING_NS_CC;
using std::to_string;

string RecordMemento::transformString(string msg)//这里直接返回char *导致乱码?
{
    if (type.empty())return msg;
    else return type + msg;
}

RecordMemento::RecordMemento(string msg) :
     type(msg)
{
    reviewLocal();
}

RecordMemento::RecordMemento(std::shared_ptr<RecordMemento> st,string msg):
    RecordMemento(st->getState(), msg)//委托构造函数
{
    recordLocal();
}



RecordMemento::RecordMemento(std::vector<std::pair<std::string, int>>& st, string msg) :
    state(std::move(st)), type(msg)//移动构造!
{
    recordLocal();
}

void RecordMemento::setState(std::vector<std::pair<std::string, int>>& st)
{
    state=st;
}

std::vector<std::pair<std::string, int>>& RecordMemento::getState()
{
    return state;
}

void RecordMemento::recordLocal()
{
    UserDefault::getInstance()->setBoolForKey("recorded", true);
    int recordnum = state.size();
    UserDefault::getInstance()->setIntegerForKey(transformString("recordnum").c_str(), recordnum);
    for (auto&x : state)
    {
        string msgname = string("msg") + to_string(recordnum);
        string indexname = string("index") + to_string(recordnum--);
        UserDefault::getInstance()->setStringForKey(transformString(msgname).c_str(), x.first);
        UserDefault::getInstance()->setIntegerForKey(transformString(indexname).c_str(), x.second);
    }
}

void RecordMemento::reviewLocal()
{
    int recordnum = UserDefault::getInstance()->getIntegerForKey(transformString("recordnum").c_str());
    for (int i = recordnum; i >= 0; i--)
    {
        string msgname = string("msg") + to_string(i);
        string indexname = string("index") + to_string(i);
        auto msg = UserDefault::getInstance()->getStringForKey(transformString(msgname).c_str());
        auto index = UserDefault::getInstance()->getIntegerForKey(transformString(indexname).c_str());
        state.push_back(std::pair<string, int>(msg, index));
    }
}