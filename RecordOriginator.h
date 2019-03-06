#pragma once
#include "cocos2d.h"
#include <vector>
#include <string>
#include "RecordMemento.h"
#include <utility>
#include <memory>
#include <queue>
using std::vector;
using std::queue;
using std::string;
class MainScene;
class cocos2d::UserDefault;
class RecordOriginator final
    //ԭ����,�ṩIO�ӿ�,�洢��Ϸ��¼
    //״̬���ڴ浵ʱ����Ч,��������ȫ�ֶ�������,�糷������,��˴������,������״̬�ȶ�ȡ.
{
    friend class  GameFacade;//ԭ����ֻ�ܱ���Ϸ��д��
private:
    std::vector<std::pair<std::string, int>>state;//�������ʱ��,����Ǳ��ӳ���ż�¼˳��,��˲�ȡ����
public:
    RecordOriginator()=default;
    ~RecordOriginator()=default;
    //��Caretaker��ȡ����¼������Ϊ״̬
    void restoreToMemento(std::shared_ptr<RecordMemento> pMemento);
    //ԭ����,��״̬ת��Ϊ����¼ת�Ƹ�Controller����
    std::shared_ptr<RecordMemento> createMemento(string msg="");
    void setState(std::vector<std::pair<std::string, int>>&);
    std::vector<std::pair<std::string, int>>& getState();
};

