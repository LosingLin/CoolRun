//
//  ReviveMenu.cpp
//  CoolRun
//
//  Created by ManYou on 15/6/2.
//
//

#include "ReviveMenu.h"
#include "NormalFrame.h"
#include "MYMultiLanguageManager.h"
#include "MobClickCpp.h"
#include "Vungle.h"
#include "ADLoadingLayer.h"
#include "ThirdPartyManager.h"

ReviveMenu::ReviveMenu()
: PopViewLayer()
, m_videoBtn(nullptr)
, m_gameOverCallback(nullptr)
, m_reviveCallback(nullptr)
, m_proTimer(nullptr)
, m_adLoadingLayer(nullptr)
{
    
}
ReviveMenu::~ReviveMenu()
{
    
}

bool ReviveMenu::init()
{
    if (!PopViewLayer::init())
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto hpos = Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2);
    
    auto frame = NormalFrame::create(Size(500, 460),
                                     MYMultiLanguageManager::getInstance()->getText("menu_revive").c_str(),
                                     false);
    frame->setAnchorPoint(Vec2(0.5, 0.5));
    frame->setPosition(hpos);
    this->addChild(frame);
    
    auto proPos = Vec2(hpos.x, hpos.y + 90);
    auto proBG = Sprite::createWithSpriteFrameName("revive_proBG.png");
    proBG->setPosition(proPos);
    this->addChild(proBG);
    
    m_proTimer = ProgressTimer::create(Sprite::createWithSpriteFrameName("revive_pro.png"));
    m_proTimer->setType(ProgressTimer::Type::BAR);
    m_proTimer->setPercentage(100);
    m_proTimer->setPosition(proPos);
    m_proTimer->setMidpoint(Vec2(0, 0));
    m_proTimer->setBarChangeRate(Vec2(1, 0));
    this->addChild(m_proTimer);
    
    auto proFrame = Sprite::createWithSpriteFrameName("revive_proFrame.png");
    proFrame->setPosition(proPos);
    this->addChild(proFrame);
    
    m_videoBtn = MYButton::createWithFrameName("btn_video.png", "btn_video_hl.png", "btn_video_dis.png");
    m_videoBtn->setAnchorPoint(Vec2(0.5, 0.5));
    m_videoBtn->setPosition(Vec2(hpos.x, hpos.y - 60));
    m_videoBtn->addTouchEventListener(CC_CALLBACK_2(ReviveMenu::watchVideoCallback, this));
    this->addChild(m_videoBtn);
    
    return true;
}

void ReviveMenu::onEnter()
{
    PopViewLayer::onEnter();
    
    auto progressTo = ProgressTo::create(3.0f, 0);
    auto call = CallFunc::create(CC_CALLBACK_0(ReviveMenu::progressDone, this));
    m_proTimer->runAction(Sequence::create(progressTo, call, NULL));
    
//    if (!VungleIsCachedAdAvailable())
//    {
//        m_videoBtn->setTouchEnabled(false);
//    }
}

void ReviveMenu::progressDone()
{
    //this->removeFromParentAndCleanup(true);
    umeng::MobClickCpp::event("revive_pass", "pass");
    if (m_gameOverCallback)
    {
        m_gameOverCallback(this, MYButton::TouchEventType::ENDED);
    }
}

void ReviveMenu::watchVideoCallback(Ref* _ref, MYButton::TouchEventType _type)
{
    if (MYButton::TouchEventType::ENDED == _type)
    {
        m_proTimer->pause();
        
        this->showAdLoading();
        ThirdPartyManager::getInstance()->setReviveMenu(this);
        VunglePlayAd();
        
        umeng::MobClickCpp::event("revive_watch", "watch");
        
        
    }
    //this->removeFromParentAndCleanup(true);
    
}

void ReviveMenu::showAdLoading()
{
    m_adLoadingLayer = ADLoadingLayer::create();
    this->addChild(m_adLoadingLayer);
    
    auto _delay = DelayTime::create(10.0f);
    auto _call = CallFunc::create(CC_CALLBACK_0(ReviveMenu::AdLoadingDone, this, true));
    m_adLoadingLayer->runAction(Sequence::create(_delay, _call, NULL));
}
void ReviveMenu::AdLoadingDone(bool needResume)
{
    if (m_adLoadingLayer)
    {
        m_adLoadingLayer->removeFromParentAndCleanup(true);
        m_adLoadingLayer = nullptr;
    }
    if (needResume)
    {
        m_proTimer->resume();
        m_videoBtn->setTouchEnabled(false);
    }
}

void ReviveMenu::revive()
{
    if (m_reviveCallback)
    {
        m_reviveCallback(this, MYButton::TouchEventType::ENDED);
    }
}
