#pragma once
#include<utility>
#include <string>
class Subject;
class Observer//一个观察者观察多个目标,观察者不储存目标的引用,因此update有一定修改
{
public: virtual void update(Subject*)=0;
};