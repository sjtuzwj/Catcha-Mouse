#pragma once

#include <utility>
using std::pair;
//////////////////////////////////////
//////������ͼ��ͳһ�ӿ�
/////////////////////////////
class GraphInterface
{
public:
    //���·��
    virtual int randomPath()=0;
    //���·������
    virtual int shortestPath()=0;
    //��ȡλ����������
    virtual int findNearestBlock(std::pair<double, double>& pos) = 0;
    //�Ƿ�Ϊ�����ڵ�
    virtual bool findIsolatedBlock(int) = 0;
    //�Ƿ�Ϊ�ս�ڵ�
    virtual bool findDeathBlock(int) = 0;
};