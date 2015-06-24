//
//  SettingScene.cpp
//  CoolRun
//
//  Created by ManYou on 14-9-5.
//
//

#include "SettingScene.h"
#include "MYScene.h"
#include "MYButton.h"
#include "PopViewLayer.h"
#include "NormalFrame.h"
#include "MenuScene.h"
#include "SceneHelp.h"
#include "SelectLanguageLayer.h"
#include "CreditLayer.h"
#include "MYUserDefaultManager.h"
#include "AudioHelp.h"
#include "CommonBackground.h"
#include "Leaves.h"
#include "MYMultiLanguageManager.h"
#include "ResourceManager.h"

SettingLayer::SettingLayer()
: MYKeyBoardLayer()
, m_mainFrame(nullptr)
, m_normalFrame(nullptr)
, m_musicSwitch(nullptr)
, m_effectSwitch(nullptr)
, m_languageBtn(nullptr)
, m_creditBtn(nullptr)
{
}
SettingLayer::~SettingLayer()
{
}

bool SettingLayer::init()
{
    if (!MYKeyBoardLayer::init())
    {
        return false;
    }
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto cbg = CommonBackground::create();
    this->addChild(cbg);
    //return true;
    
    m_mainFrame = Layer::create();
    this->addChild(m_mainFrame);
    
    auto framesize = Size(800, 600);
    m_normalFrame = NormalFrame::create(framesize, MYMultiLanguageManager::getInstance()->getText("Options").c_str());
    m_normalFrame->setAnchorPoint(Vec2(0.5, 0.5));
    m_normalFrame->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2));
    m_normalFrame->addCloseCallback(CC_CALLBACK_2(SettingLayer::closeBtnCallback, this));
    m_mainFrame->addChild(m_normalFrame);
    
    m_effectSwitch = MYSwitch::createWithFrameName("effect_on.png", "effect_off.png");
    m_effectSwitch->setAnchorPoint(Vec2(0.5, 0.5));
    m_effectSwitch->setPosition(Vec2(origin.x + visibleSize.width/2 - 150, origin.y + visibleSize.height/2 + 80));
    m_effectSwitch->addSwitchCallback(CC_CALLBACK_2(SettingLayer::switchBtnCallback, this));
    m_mainFrame->addChild(m_effectSwitch);
    
    m_musicSwitch = MYSwitch::createWithFrameName("music_on.png", "music_off.png");
    m_musicSwitch->setAnchorPoint(Vec2(0.5, 0.5));
    m_musicSwitch->setPosition(Vec2(origin.x + visibleSize.width/2 + 150, origin.y + visibleSize.height/2 + 80));
    m_musicSwitch->addSwitchCallback(CC_CALLBACK_2(SettingLayer::switchBtnCallback, this));
    m_mainFrame->addChild(m_musicSwitch);
    
    m_languageBtn = MYButton::createWithFrameName("btn_rect.png", "btn_rect_hl.png");
    m_languageBtn->addBMFLabel(ResourceManager::getInstance()->getFntRes("SetBtn").c_str(),
                               MYMultiLanguageManager::getInstance()->getText("Language").c_str());
    m_languageBtn->setAnchorPoint(Vec2(0.5, 0.5));
    m_languageBtn->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2 - 60));
    m_languageBtn->addTouchEventListener(CC_CALLBACK_2(SettingLayer::menuBtnCallback, this));
    m_mainFrame->addChild(m_languageBtn);
    
    m_creditBtn = MYButton::createWithFrameName("btn_rect.png", "btn_rect_hl.png");
    m_creditBtn->addBMFLabel(ResourceManager::getInstance()->getFntRes("SetBtn").c_str(),
                             MYMultiLanguageManager::getInstance()->getText("Credit").c_str());
    m_creditBtn->setAnchorPoint(Vec2(0.5, 0.5));
    m_creditBtn->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2 - 180));
    m_creditBtn->addTouchEventListener(CC_CALLBACK_2(SettingLayer::menuBtnCallback, this));
    m_mainFrame->addChild(m_creditBtn);
    
    if (MYUserDefaultManager::getInstance()->isEffectOff())
    {
        m_effectSwitch->setStatus(MYSwitch::MYSwitchStatus::OFF);
    }
    if (MYUserDefaultManager::getInstance()->isMusicOff())
    {
        m_musicSwitch->setStatus(MYSwitch::MYSwitchStatus::OFF);
    }
    
    auto _leaves = Leaves::create();
    this->addChild(_leaves, 90);
    
    return true;
}

void SettingLayer::switchBtnCallback(Ref* _ref, MYSwitch::MYSwitchStatus _status)
{
    if (_ref == m_effectSwitch)
    {
        if (_status == MYSwitch::MYSwitchStatus::ON)
        {
            MYUserDefaultManager::getInstance()->setEffectOff(false);
        }
        else
        {
            MYUserDefaultManager::getInstance()->setEffectOff(true);
        }
    }
    else if (_ref == m_musicSwitch)
    {
        if (_status == MYSwitch::MYSwitchStatus::ON)
        {            
            MYUserDefaultManager::getInstance()->setMusicOff(false);
            AudioHelp::resumeBgA();
            if (!AudioHelp::isBgAPlaying())
            {
                AudioHelp::playBgA("night_min.mp3");
            }
        }
        else
        {
            AudioHelp::pauseBgA();
            MYUserDefaultManager::getInstance()->setMusicOff(true);
        }
    }
}

void SettingLayer::closeBtnCallback(Ref* _ref, MYButton::TouchEventType _type)
{
    if (_type == MYButton::TouchEventType::ENDED)
    {
        auto _scene = MenuLayer::createScene();
        SceneHelp::replaceScene(_scene);
    }
}

void SettingLayer::menuBtnCallback(Ref* _ref, MYButton::TouchEventType _type)
{
    if (_type == MYButton::TouchEventType::ENDED)
    {
        m_mainFrame->setVisible(false);
        
        if (_ref == m_languageBtn)
        {
            auto _sll = SelectLanguageLayer::create();
            _sll->addCloseCallback(CC_CALLBACK_2(SettingLayer::backMenuCallback, this));
            this->addChild(_sll);
        }
        else if (_ref == m_creditBtn)
        {
            auto _cl = CreditLayer::create();
            _cl->addCloseCallback(CC_CALLBACK_2(SettingLayer::backMenuCallback, this));
            this->addChild(_cl);
        }
    }
}

void SettingLayer::backMenuCallback(Ref* _ref, MYButton::TouchEventType _type)
{
    this->updateMainFrame();
    m_mainFrame->setVisible(true);
}

void SettingLayer::updateMainFrame()
{
    m_normalFrame->updateBMFTitleLabel(ResourceManager::getInstance()->getFntRes("NFTitle"),
                                       MYMultiLanguageManager::getInstance()->getText("Options"));
    m_languageBtn->addBMFLabel(ResourceManager::getInstance()->getFntRes("SetBtn").c_str(),
                               MYMultiLanguageManager::getInstance()->getText("Language").c_str());
    m_creditBtn->addBMFLabel(ResourceManager::getInstance()->getFntRes("SetBtn").c_str(),
                             MYMultiLanguageManager::getInstance()->getText("Credit").c_str());
}

Scene* SettingLayer::createScene()
{
    auto _scene = MYScene::create();
    auto _layer = SettingLayer::create();
    _scene->addChild(_layer);
    return _scene;
}