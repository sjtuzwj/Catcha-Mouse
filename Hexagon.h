#pragma once
#include<string>
#include<utility>
#include<vector>
    using std::pair;
    ////////////////////////////
    ///////������ģ��,�ӿڽ���Graph����,��������
    ///////////////////////////////
    class Hexagon final
    {
        friend class Graph;
    private:
        ~Hexagon() = default;
        Hexagon() = default;
        //��д�ӿ�
        void setPos(pair<double, double>newposition) { position = newposition; }
        pair<double, double>getPos() {
            return position;
        }
        std::vector<int> getneighbor() { return neighbor; }
        //��Ա��Ϣ
        std::vector<int>neighbor;//�������ڽڵ�
        pair<double, double> position;
    };
