#pragma once
#include <string>
class BGM final
{
public:
    ////////////////////////
    //////���Ʊ������ֲ��ŵĽӿ�,��װ��SimpleAudioEngine
    ///////////////////////////
    static void easteregg(std::string);
    static void weather(std::string);
    static void playbgm();
    static void playvictory();
    static void press();//������,��߽���ʵ��,ͬʱ����̽����Ϸ�߼��Ƿ�������ת
    static void preload();//Ԥ����
    static void overtime();//��ʱ������ɫ����};
    BGM() = delete;//��ֹ����ʵ��
};