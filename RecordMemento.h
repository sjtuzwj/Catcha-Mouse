#pragma once
#include "cocos2d.h"
#include <vector>
#include <string>
#include <utility>
#include <memory>
#include <queue>
using std::vector;
using std::queue;
using std::string;
class MainScene;
class cocos2d::UserDefault;
class RecordOriginator;
//////////////////////////////
////////����¼,�洢��¼,���������뱾���ļ��Ľ���
//////////////////////////////
class RecordMemento final
{
    //����ԭ�������ſ�ӿ�,������������ı�״̬,�߶ȷ�װ+խ�ӿ�
    friend class RecordOriginator;
public:
    ~RecordMemento()=default;
    RecordMemento(const RecordMemento&) = delete;
    RecordMemento() = delete; 
    RecordMemento(std::shared_ptr<RecordMemento> st, string msg = "");
    RecordMemento(string = "");
    RecordMemento(std::vector<std::pair<std::string, int>>& st,string="");
private:
    std::vector<std::pair<std::string, int>>state;
    std::string type;
    void setState(std::vector<std::pair<std::string, int>>&);
    std::vector<std::pair<std::string, int>>&getState();
    //��������
    string transformString(string msg);
    //���ؼ�¼
    void reviewLocal();
    //�����¼
    void recordLocal();
};

