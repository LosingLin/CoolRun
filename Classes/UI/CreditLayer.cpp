//
//  CreditLayer.cpp
//  CoolRun
//
//  Created by ManYou on 15/5/19.
//
//

#include "CreditLayer.h"
#include "NormalFrame.h"
#include "MYMultiLanguageManager.h"


CreditLayer::CreditLayer()
: Layer()
, m_bgFrame(nullptr)
, m_callback(nullptr)
{
    
}
CreditLayer::~CreditLayer()
{
    
}

bool CreditLayer::init()
{
    if (!Layer::init())
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto frameSize = Size(800, visibleSize.height);
    m_bgFrame = NormalFrame::create(frameSize, MYMultiLanguageManager::getInstance()->getText("Credit").c_str());
    m_bgFrame->setAnchorPoint(Vec2(0.5, 0.5));
    m_bgFrame->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2));
    m_bgFrame->addCloseCallback(CC_CALLBACK_2(CreditLayer::closeBtnCallback, this));
    this->addChild(m_bgFrame);
    
    //Artist Programmers Special thanks
    int y = origin.y + visibleSize.height - 140;
    int x = origin.x + visibleSize.width/2;
    auto programeLab = Label::createWithBMFont("CreditsTitle.fnt", MYMultiLanguageManager::getInstance()->getText("Programmers"));
    programeLab->setAnchorPoint(Vec2(0.5, 0.5));
    programeLab->setPosition(Vec2(x, y));
    this->addChild(programeLab);
    y -= 44;
    auto pnLab = Label::createWithBMFont("CreditsItem.fnt", MYMultiLanguageManager::getInstance()->getText("Mingmin Lin"));
    pnLab->setAnchorPoint(Vec2(0.5, 0.5));
    pnLab->setPosition(Vec2(x, y));
    this->addChild(pnLab);
    
    y -= 80;
    auto artistLab = Label::createWithBMFont("CreditsTitle.fnt", MYMultiLanguageManager::getInstance()->getText("Artist"));
    artistLab->setAnchorPoint(Vec2(0.5, 0.5));
    artistLab->setPosition(Vec2(x, y));
    this->addChild(artistLab);
    y -= 44;
    auto anLab = Label::createWithBMFont("CreditsItem.fnt", MYMultiLanguageManager::getInstance()->getText("Mingmin Lin"));
    anLab->setAnchorPoint(Vec2(0.5, 0.5));
    anLab->setPosition(Vec2(x, y));
    this->addChild(anLab);
    
    y -= 80;
    auto stLab = Label::createWithBMFont("CreditsTitle.fnt", MYMultiLanguageManager::getInstance()->getText("Speical Thanks"));
    stLab->setAnchorPoint(Vec2(0.5, 0.5));
    stLab->setPosition(Vec2(x, y));
    this->addChild(stLab);
    y -= 44;
    auto stn1Lab = Label::createWithBMFont("CreditsItem.fnt", MYMultiLanguageManager::getInstance()->getText("Cocos2d-x"));
    stn1Lab->setAnchorPoint(Vec2(0.5, 0.5));
    stn1Lab->setPosition(Vec2(x, y));
    this->addChild(stn1Lab);
    
    return true;
}

void CreditLayer::closeBtnCallback(Ref* _ref, MYButton::TouchEventType _type)
{
    if(_type == MYButton::TouchEventType::ENDED)
    {
        this->removeFromParentAndCleanup(true);
        m_callback(_ref, _type);
    }
}