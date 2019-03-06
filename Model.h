#pragma once
#include<utility>
#include<string>


    class Prototype;
    //基类 储存 索引 位置 类型, 假的Model, 只有数据没有方法,只对Prototype开放接口
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
