#pragma once
#include<utility>
#include<string>


    class Prototype;
    //���� ���� ���� λ�� ����, �ٵ�Model, ֻ������û�з���,ֻ��Prototype���Žӿ�
    class SpriteModel
    {
        friend class Prototype;
    private:
        SpriteModel() = default;
        SpriteModel(std::string omsg):msg(std::move(omsg)) {}
        virtual ~SpriteModel() = default;
        std::pair<double, double>pos;
        std::string msg;
        int index;
    };
