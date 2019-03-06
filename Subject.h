#pragma once
#include<utility>
#include <string>
class Observer;
using std::string;
//��������ӿ�
////Ϊʲô��View��Ϊ����,��Model��Ϊ�۲���:
////��Web��ͬ,��Ϸ����������������View��,��Model�۲�View�Ӷ�;��WEB���õ�MVC���ǻ��ں�˵����ݸı�ǰ��.������ղ�ȡ��graph�۲�actor�Ĳ���
////����Ҫ�Ļ����ȱ�Graph̫����,�ܶ��ض�����Ϊ����,���֪���˾����߼�,��ȫ����ֱ�Ӹ���View��Ȼ����Modelͬ��,������Model�Ļ�����û�ж�Ӧ����
class Subject
{
public:
    //��۲�����صĽӿ�
    virtual void attach(std::shared_ptr<Observer>)=0;
    virtual void detach(std::shared_ptr<Observer>)=0;
    //����������صĽӿ�
    virtual std::pair < std:: string, int > getState()=0;//��ģ��,�ٶ��˹۲�������Ҫ����Ϣ
    virtual void setState(string, int) = 0;
    //����֪ͨ,�����û��Զ���Ҳ�����Զ�����,ʵ�ֽӿڵ�ϸ����ʵ�������
    virtual void notify() = 0;
};