//
//  ExitGameMenu.cpp
//  CoolRun
//
//  Created by ManYou on 15/6/13.
//
//

#include "ExitGameMenu.h"
#include "MYUserDefaultManager.h"
#include "NormalFrame.h"
#include "MYMultiLanguageManager.h"
#include "MobClickCpp.h"


ExitGameMenu::ExitGameMenu()
: PopViewLayer()
, m_confirmBtn(nullptr)
, m_cancelBtn(nullptr)
, b_isPaused(false)
{
    
}
ExitGameMenu::~ExitGameMenu()
{
    
}

bool ExitGameMenu::init()
{
    if (!PopViewLayer::init())
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto hpos = Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2);
    
    auto frame = NormalFrame::create(Size(660, 320),
                                     MYMultiLanguageManager::getInstance()->getText("quitgame").c_str(),
                                     false);
    frame->setAnchorPoint(Vec2(0.5, 0.5));
    frame->setPosition(hpos);
    this->addChild(frame);
    
    
    m_cancelBtn = MYButton::createWithFrameName("btn_rect02.png", "btn_rect02_hl.png");
    m_cancelBtn->addTouchEventListener(CC_CALLBACK_2(ExitGameMenu::cancelCallback, this));
    m_cancelBtn->setAnchorPoint(Vec2(0.5, 0.5));
    m_cancelBtn->setPosition(Vec2(hpos.x - 130, hpos.y - 36));
    m_cancelBtn->addBMFLabel("SetBtn.fnt", MYMultiLanguageManager::getInstance()->getText("cancel").c_str());
    this->addChild(m_cancelBtn);
    
    m_confirmBtn = MYButton::createWithFrameName("btn_rect02.png", "btn_rect02_hl.png");
    m_confirmBtn->addTouchEventListener(CC_CALLBACK_2(ExitGameMenu::confirmCallback, this));
    m_confirmBtn->setAnchorPoint(Vec2(0.5, 0.5));
    m_confirmBtn->setPosition(Vec2(hpos.x + 130, hpos.y - 36));
    m_confirmBtn->addBMFLabel("SetBtn.fnt", MYMultiLanguageManager::getInstance()->getText("confirm").c_str());
    this->addChild(m_confirmBtn);
    
    this->setLocalZOrder(ZORDER_SYS);
    
    if (Director::getInstance()->isPaused())
    {
        b_isPaused = true;
    }
    else
    {
        b_isPaused = false;
        Director::getInstance()->pause();
    }
    
    
    return true;
}

void ExitGameMenu::onEnter()
{
    PopViewLayer::onEnter();
    
}



void ExitGameMenu::confirmCallback(Ref* _ref, MYButton::TouchEventType _type)
{
    if (_type == MYButton::TouchEventType::ENDED)
    {
        
        umeng::MobClickCpp::end();
        
        Director::getInstance()->end();
        
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        exit(0);
#endif
    }
}
void ExitGameMenu::cancelCallback(Ref* _ref, MYButton::TouchEventType _type)
{
    if (_type == MYButton::TouchEventType::ENDED)
    {
        this->removeFromParentAndCleanup(true);
        if (!b_isPaused)
        {
            Director::getInstance()->resume();
        }
    }
}