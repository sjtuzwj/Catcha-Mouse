#pragma once
#include<utility>
#include <string>
class Subject;
class Observer//һ���۲��߹۲���Ŀ��,�۲��߲�����Ŀ�������,���update��һ���޸�
{
public: virtual void update(Subject*)=0;
};