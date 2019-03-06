#include "OptionScene.h"
#include "HelloWorldScene.h"
#include "CreateItem.h"
#include "Bgm.h"
#include "SimpleAudioEngine.h"
#include "Setting.h"
#include "cocos2d.h"
//仅引入与类无关的头文件
USING_NS_CC;
using namespace CocosDenshion;

Scene* OptionScene::createScene()
{
    auto scene = Scene::create();
    auto layer = OptionScene::create();
    scene->addChild(layer);
    return scene;
}

bool OptionScene::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }
    UIMemberInit();
    return true;
}

///////////////////////////
//////UI组件
///////////////////////////

void OptionScene::UIMemberInit() {
    ////////////////////
    ////background
    /////////////
    auto background = ItemFunction::createBackground(std::string("Option"));
    this->addChild(background, 0);
    menuInit();
    buttonInit();
    checkBoxInit();
    sliderInit();
}

void OptionScene::menuInit()
{
    /////////////////////
    //////菜单
    ///////////////////
    ////////////////////////////////////

    MenuItemImage* backItem = ItemFunction::createMenu(
        std::string("Back.png"),
        CC_CALLBACK_1(OptionScene::menuBackCallback, this));
    ItemFunction::putbottom(backItem);

    MenuItems.pushBack(backItem);
    //////////////////////////////

    auto menu = Menu::createWithArray(MenuItems);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

}

void OptionScene::checkBoxInit()
{

    //////////////////////////

    auto darkCheckBox = createDarkCheckBox();
    this->addChild(darkCheckBox);

    auto darkLabel = createLabelWith("Dark", darkCheckBox);
    this->addChild(darkLabel);

    //////////////////////////
    auto mouseCheckBox = createMouseCheckBox();
    this->addChild(mouseCheckBox);

    auto mouseLabel = createLabelWith("Mouse", mouseCheckBox);
    this->addChild(mouseLabel);
    /////////////////////
    auto humanCheckBox = createHumanCheckBox();
    this->addChild(humanCheckBox);

    auto humanLabel = createLabelWith("Human", humanCheckBox);
    this->addChild(humanLabel);
}

void OptionScene::sliderInit()
{

    //////////////////////
    auto bgmSlider = createBgmSlider();
    this->addChild(bgmSlider);

    auto bgmLabel = createLabelWith("Volume", bgmSlider);
    this->addChild(bgmLabel);
    ///////////////////////
    auto modeSlider = createModeSlider();
    this->addChild(modeSlider);

    auto modeLabel = createLabelWith("Holes", modeSlider);
    this->addChild(modeLabel);

}

void OptionScene::buttonInit()
{

    auto bgmButton = createBgmButton();
    this->addChild(bgmButton);
}

ui::Button* OptionScene::createBgmButton()
{
    auto button = ui::Button::create("bgm1.png", "bgm2.png", "bgm3.png");
    button->setTitleText("Bgm");
    button->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
        switch (type)
        {
        case ui::Widget::TouchEventType::BEGAN:
            break;
        case ui::Widget::TouchEventType::ENDED:
            Setting::getInstance().changeBgm();
            BGM::playbgm();
            break;
        default:
            break;
        }
    });
    button->setScale(0.15f);
    ItemFunction::putmid(button);
    return button;
}

ui::CheckBox* OptionScene::createDarkCheckBox()
{

    auto checkbox = createCheckBox();
    if (Setting::getInstance().getDark())
        checkbox->setSelected(true);
    else
        checkbox->setSelected(false);
    checkbox->addEventListener([&](Ref* sender, ui::CheckBox::EventType type) {
        switch (type)
        {
        case cocos2d::ui::CheckBox::EventType::SELECTED:
            Setting::getInstance().setDark(true);
            break;
        case cocos2d::ui::CheckBox::EventType::UNSELECTED:
            Setting::getInstance().setDark(false);
            break;
        default:
            break;
        }

    });
    ItemFunction::putrighttop(checkbox);
    return checkbox;
}

ui::CheckBox* OptionScene::createMouseCheckBox()
{
    auto checkbox = createCheckBox();
    if (Setting::getInstance().getMouse())
        checkbox->setSelected(true);
    else
        checkbox->setSelected(false);
    checkbox->addEventListener([&](Ref* sender, ui::CheckBox::EventType type) {
        switch (type)
        {
        case cocos2d::ui::CheckBox::EventType::SELECTED:
            Setting::getInstance().setMouse(true);
            break;
        case cocos2d::ui::CheckBox::EventType::UNSELECTED:
            Setting::getInstance().setMouse(false);
            break;
        default:
            break;
        }

    });
    ItemFunction::putlefttop(checkbox);
    return checkbox;
}

ui::CheckBox* OptionScene::createHumanCheckBox()
{
    auto checkbox = createCheckBox();
    if (Setting::getInstance().getHuman())
        checkbox->setSelected(true);
    else
        checkbox->setSelected(false);
    checkbox->addEventListener([&](Ref* sender, ui::CheckBox::EventType type) {
        switch (type)
        {
        case cocos2d::ui::CheckBox::EventType::SELECTED:
            Setting::getInstance().setHuman(true);
            break;
        case cocos2d::ui::CheckBox::EventType::UNSELECTED:
            Setting::getInstance().setHuman(false);
            break;
        default:
            break;
        }

    });
    ItemFunction::putlefttop(checkbox);
    ItemFunction::putbyright(checkbox, 1);
    return checkbox;
}

ui::CheckBox * OptionScene::createCheckBox()
{
    auto checkbox = ui::CheckBox::create("CheckBox_Normal.png",
        "CheckBox_Press.png",
        "CheckBoxNode_Normal.png",
        "CheckBox_Disable.png",
        "CheckBoxNode_Disable.png");
    return checkbox;
}

ui::Slider * OptionScene::createSlider()
{
    auto slider = ui::Slider::create();
    slider->loadBarTexture("Slider_Back.png"); // what the slider looks like
    slider->loadSlidBallTextures("SliderNode_Normal.png", "SliderNode_Press.png", "SliderNode_Disable.png");
    slider->loadProgressBarTexture("Slider_PressBar.png");
    return slider;
}

ui::Slider * OptionScene::createBgmSlider()
{
    auto slider = createSlider();
    slider->setPercent(SimpleAudioEngine::getInstance()->getBackgroundMusicVolume()*100.0f);
    slider->addEventListener(CC_CALLBACK_1(OptionScene::bgmSliderCallBack, this));
    ItemFunction::putdown(slider);
    return slider;
}

ui::Slider * OptionScene::createModeSlider()
{
    auto slider = createSlider();
    slider->setPercent((Setting::getInstance().getMaxHole() -1)*10);
    slider->addEventListener(CC_CALLBACK_1(OptionScene::modeSliderCallBack, this));
    ItemFunction::putdown(slider);
    ItemFunction::putbydown(slider, 2);
    return slider;
}

Label* OptionScene::createLabelWith(const char* msg,ui::Slider* slider)
{
    auto Label = Label::createWithTTF(msg, "fonts/Marker Felt.ttf", 24);
    Label->setPosition(slider->getPosition());
    ItemFunction::putbyup(Label, 1);
    Label->enableOutline(Color4B::BLACK, 1);
    return Label;
}

Label* OptionScene::createLabelWith(const char* msg, ui::CheckBox* checkbox)
{
    auto Label = Label::createWithTTF(msg, "fonts/Marker Felt.ttf", 24);
    Label->setPosition(checkbox->getPosition());    
    ItemFunction::putbydown(Label, 1);
    Label->enableOutline(Color4B::BLACK, 1);
    return Label;
}

///////////////////
////////回调
///////////////////////////
void OptionScene::bgmSliderCallBack(Ref *sender) {
    auto item = (ui::Slider*)(sender);
    Setting::getInstance().setVolume(item->getPercent() / 100.0f);
    SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(item->getPercent() / 100.0f);
}

void OptionScene::modeSliderCallBack(Ref *sender) {
    auto item = (ui::Slider*)(sender);
    Setting::getInstance().setMaxHole((item->getPercent()) / 10 + 1);

}

void OptionScene::menuBackCallback(Ref* pSender)
{
    BackInterface::menuBackCallback(pSender);
}