//
//  SelectLanguageLayer.cpp
//  CoolRun
//
//  Created by ManYou on 15/5/18.
//
//

#include "SelectLanguageLayer.h"
#include "NormalFrame.h"
#include "MYMultiLanguageManager.h"

SelectLanguageLayer::SelectLanguageLayer()
: Layer()
, m_enBtn(nullptr)
, m_chBtn(nullptr)
, m_bgFrame(nullptr)
, m_callback(nullptr)
{
    
}
SelectLanguageLayer::~SelectLanguageLayer()
{
    
}

bool SelectLanguageLayer::init()
{
    if (!Layer::init())
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto frameSize = Size(800, 500);
    m_bgFrame = NormalFrame::create(frameSize, MYMultiLanguageManager::getInstance()->getText("Language").c_str());
    m_bgFrame->setAnchorPoint(Vec2(0.5, 0.5));
    m_bgFrame->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2));
    m_bgFrame->addCloseCallback(CC_CALLBACK_2(SelectLanguageLayer::closeBtnCallback, this));
    this->addChild(m_bgFrame);
    
    m_enBtn = MYButton::createWithFrameName("btn_rect.png", "btn_rect_hl.png");
    m_enBtn->addBMFLabel("SetBtn.fnt", MYMultiLanguageManager::getInstance()->getText("English").c_str());
    m_enBtn->setAnchorPoint(Vec2(0.5, 0.5));
    m_enBtn->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2));
    m_enBtn->addTouchEventListener(CC_CALLBACK_2(SelectLanguageLayer::selectDoneCallback, this));
    this->addChild(m_enBtn);
    
    m_chBtn = MYButton::createWithFrameName("btn_rect.png", "btn_rect_hl.png");
    m_chBtn->addBMFLabel("SetBtn.fnt", MYMultiLanguageManager::getInstance()->getText("Chinese").c_str());
    m_chBtn->setAnchorPoint(Vec2(0.5, 0.5));
    m_chBtn->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2 - 120));
    m_chBtn->addTouchEventListener(CC_CALLBACK_2(SelectLanguageLayer::selectDoneCallback, this));
    this->addChild(m_chBtn);
    
    return true;
}

void SelectLanguageLayer::selectDoneCallback(Ref* _ref, MYButton::TouchEventType _type)
{
    if (_type == MYButton::TouchEventType::ENDED)
    {
        if (_ref == m_enBtn)
        {
            MYMultiLanguageManager::getInstance()->setCurrentLanguage(MYMultiLanguageManager::MultiLanguageType::ENGLISH);
        }
        else if(_ref == m_chBtn)
        {
            MYMultiLanguageManager::getInstance()->setCurrentLanguage(MYMultiLanguageManager::MultiLanguageType::CHINESE);
        }
        
        this->closeBtnCallback(this, _type);
    }
}

void SelectLanguageLayer::closeBtnCallback(Ref* _ref, MYButton::TouchEventType _type)
{
    if(_type == MYButton::TouchEventType::ENDED)
    {
        this->removeFromParentAndCleanup(true);
        m_callback(_ref, _type);
    }
}