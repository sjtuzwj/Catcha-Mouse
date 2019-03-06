#pragma once
#include "cocos2d.h"
#include <random>
#include <ctime>
#include <memory>


    class Graph;
    class GameFacade;

    //////////////////////////////
    ////////������Ϸ�߼����������
    //////////////////////////////
    class Judge final
        //����ģʽ,ȫ��״̬
    {
    private:
        //��̬��Ա
        Judge();
        ~Judge() = default;
        //���ܳ�Ա
        std::default_random_engine eng;//�������������(���ʹ��ʵ��)
        std::uniform_int_distribution<int> hex;//������ֲ�����0-59����Ӧ����������
        std::uniform_int_distribution<int> whc;//������ֲ�����1-3����ӦͼƬ�����ֺ�������Դ
        //����ٽ��ڵ�
        int judgeClosePos(std::shared_ptr<Graph>);
    public:
        //������ͼ����
        //�������·��
        int judgeClosestPos(std::shared_ptr<Graph>);
        //����սڵ�
        int judgeRandomPos(std::shared_ptr<Graph>);
        //��������ڵ�
        int judgeProperPos(std::shared_ptr<Graph>);
        //����ڵ�
        int judgeClickPos(cocos2d::EventMouse *event, std::shared_ptr<Graph> graph);
        //�������,��Ϊ��Ҫ�õ��������������,���Ժ;�����ͼ�����ھ���
        int judgeWhich();
        //����ģʽ
        static Judge& getInstance() {
            static Judge instance;
            return instance;
        }
    };