//
//  GameOverMenu.cpp
//  CoolRun
//
//  Created by ManYou on 15/6/2.
//
//

#include "GameOverMenu.h"
#include "MYUserDefaultManager.h"
#include "NormalFrame.h"
#include "MYMultiLanguageManager.h"
#include "ResourceManager.h"


GameOverMenu::GameOverMenu()
: PopViewLayer()
, m_retryBtn(nullptr)
, m_homeBtn(nullptr)
, m_finalDis(nullptr)
, m_highDis(nullptr)
, m_jadeNum(nullptr)
, m_jadeNum_Ext(nullptr)
, m_retryCallback(nullptr)
, m_homeCallback(nullptr)
, b_isNewRecord(false)
, m_newRecordSp(nullptr)
{
    
}
GameOverMenu::~GameOverMenu()
{
    
}

bool GameOverMenu::init()
{
    if (!PopViewLayer::init())
    {
        return false;
    }
    
    
    
    
    return true;
}

bool GameOverMenu::init(CoolRun::RunType type)
{
    if (!this->init())
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto hpos = Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2);
    
    auto frame = NormalFrame::create(Size(660, 580),
                                     MYMultiLanguageManager::getInstance()->getText("menu_gameover").c_str(),
                                     false);
    frame->setAnchorPoint(Vec2(0.5, 0.5));
    frame->setPosition(hpos);
    this->addChild(frame);
    
    auto topPos = Vec2(hpos.x, hpos.y + 160);
    if (CoolRun::RunType::EDITOR == type)
    {
        topPos.y -= 10;
    }
    auto finalTxt = Label::createWithBMFont(ResourceManager::getInstance()->getFntRes("SetBtn"),
                                            MYMultiLanguageManager::getInstance()->getText("menu_finalScore"));
    finalTxt->setAnchorPoint(Vec2(0.5, 0.5));
    finalTxt->setPosition(topPos);
    finalTxt->setScale(0.8f);
    this->addChild(finalTxt);
    
    if (CoolRun::RunType::EDITOR == type)
    {
        topPos.y -= 60;
    }
    else
    {
        topPos.y -= 60;
    }
    m_finalDis = Label::createWithBMFont(ResourceManager::getInstance()->getFntRes("Score"), "0");
    m_finalDis->setAnchorPoint(Vec2(0.5, 0.5));
    m_finalDis->setPosition(topPos);
    m_finalDis->setScale(1.2f);
    //m_finalDis->setAlignment(TextHAlignment::LEFT, TextVAlignment::CENTER);
    this->addChild(m_finalDis);
    
    
    if (CoolRun::RunType::EDITOR == type)
    {
        topPos.y -= 80;
    }
    else
    {
        topPos.y -= 50;
    }
    auto highTxt = Label::createWithBMFont(ResourceManager::getInstance()->getFntRes("SetBtn"),
                                           MYMultiLanguageManager::getInstance()->getText("menu_highScore"));
    highTxt->setAnchorPoint(Vec2(0.5, 0.5));
    highTxt->setPosition(topPos);
    highTxt->setScale(0.8f);
    this->addChild(highTxt);
    
    if (CoolRun::RunType::EDITOR == type)
    {
        topPos.y -= 60;
    }
    else
    {
        topPos.y -= 60;
    }
    m_highDis = Label::createWithBMFont(ResourceManager::getInstance()->getFntRes("M"), "0");
    m_highDis->setAnchorPoint(Vec2(0.5, 0.5));
    m_highDis->setPosition(topPos);
    m_highDis->setScale(1.2f);
    //m_finalDis->setAlignment(TextHAlignment::LEFT, TextVAlignment::CENTER);
    this->addChild(m_highDis);
    
    if (CoolRun::RunType::EDITOR != type)
    {
        topPos.y -= 60;
        
        auto _jadeIcon = Sprite::createWithSpriteFrameName("jade.png");
        _jadeIcon->setPosition(Vec2(topPos.x - 50, topPos.y));
        _jadeIcon->setScale(0.6);
        this->addChild(_jadeIcon);
        m_jadeNum = Label::createWithBMFont(ResourceManager::getInstance()->getFntRes("Score"), "+0");
        m_jadeNum->setAnchorPoint(Vec2(0, 0.5));
        m_jadeNum->setPosition(Vec2(topPos.x - 10, topPos.y - 10));
        m_jadeNum->setAlignment(TextHAlignment::LEFT, TextVAlignment::CENTER);
        m_jadeNum->setScale(1.2f);
        this->addChild(m_jadeNum);
        
        auto jadeNumSize = m_jadeNum->getContentSize();
        
        m_jadeNum_Ext= Label::createWithBMFont(ResourceManager::getInstance()->getFntRes("M"), "+0");
        m_jadeNum_Ext->setAnchorPoint(Vec2(0, 0.5));
        m_jadeNum_Ext->setPosition(Vec2(topPos.x - 10 + jadeNumSize.width, topPos.y - 10));
        m_jadeNum_Ext->setAlignment(TextHAlignment::LEFT, TextVAlignment::CENTER);
        m_jadeNum_Ext->setScale(1.2f);
        this->addChild(m_jadeNum_Ext);
    }

    
    if (CoolRun::RunType::EDITOR == type)
    {
        topPos.y -= 120;
    }
    else
    {
        topPos.y -= 110;
    }
    m_homeBtn = MYButton::createWithFrameName("btn_home02.png", "btn_home02_hl.png");
    m_homeBtn->addTouchEventListener(CC_CALLBACK_2(GameOverMenu::homeCallback, this));
    m_homeBtn->setAnchorPoint(Vec2(0.5, 0.5));
    m_homeBtn->setPosition(Vec2(topPos.x - 130, topPos.y));
    this->addChild(m_homeBtn);
    
    m_retryBtn = MYButton::createWithFrameName("btn_restart.png", "btn_restart_hl.png");
    m_retryBtn->addTouchEventListener(CC_CALLBACK_2(GameOverMenu::retryCallback, this));
    m_retryBtn->setAnchorPoint(Vec2(0.5, 0.5));
    m_retryBtn->setPosition(Vec2(topPos.x + 130, topPos.y));
    this->addChild(m_retryBtn);
    
    m_newRecordSp = Sprite::createWithSpriteFrameName(
                                                      MYMultiLanguageManager::getInstance()->getText("menu_newRecordSpName")
                                                      );
    m_newRecordSp->setPosition(Vec2(hpos.x + 200, hpos.y + 120));
    this->addChild(m_newRecordSp);
    m_newRecordSp->setVisible(false);
    
    return true;
}
GameOverMenu* GameOverMenu::create(CoolRun::RunType type)
{
    auto _gom = new GameOverMenu();
    if (_gom && _gom->init(type))
    {
        _gom->autorelease();
        return _gom;
    }
    delete _gom;
    _gom = nullptr;
    return nullptr;
}

void GameOverMenu::onEnter()
{
    PopViewLayer::onEnter();
    
    if (b_isNewRecord)
    {
        
    }
}

void GameOverMenu::setFinalScore(int score, int jade, CoolRun::RunType _type)
{
    string s;
    stringstream ss(s);
    
    int high_score = 0;
    if (_type != CoolRun::RunType::EDITOR)
    {
        high_score = MYUserDefaultManager::getInstance()->getHighScoreNormal();
        
        ss << jade;
        ss >> s;
        m_jadeNum->setString(s);
        ss.clear();
        
        int extJadeNum = score/10;
        ss << extJadeNum;
        ss >> s;
        m_jadeNum_Ext->setString(" +" + s);
        ss.clear();
        
        auto jadeNumSize = m_jadeNum->getContentSize();
        auto jadeNumPos = m_jadeNum->getPosition();
        m_jadeNum_Ext->setPosition(Vec2(jadeNumPos.x + jadeNumSize.width, jadeNumPos.y));
        
        
        MYUserDefaultManager::getInstance()->addOwnJade(jade + extJadeNum);
    }
    else if(_type == CoolRun::RunType::EDITOR)
    {
        high_score = MYUserDefaultManager::getInstance()->getHighScoreNormalEditor();
    }
    if (score > high_score)
    {
        high_score = score;
        
        b_isNewRecord = true;
        
        m_newRecordSp->setVisible(true);
        m_newRecordSp->setScale(1.2f);
        m_newRecordSp->setOpacity(100);
        
        
        auto _fadeIn = FadeIn::create(0.2);
        auto _scaleTo = ScaleTo::create(0.2, 0.8f);
        auto _spawn = Spawn::create(_fadeIn, _scaleTo, NULL);
        m_newRecordSp->runAction(_spawn);
        
        if (_type == CoolRun::RunType::NORMAL)
        {
            MYUserDefaultManager::getInstance()->setHighScoreNormal(high_score);
        }
        else if(_type == CoolRun::RunType::EDITOR)
        {
            MYUserDefaultManager::getInstance()->setHighScoreNormalEditor(high_score);
        }
    }
    
    
    ss << score;
    ss >> s;
    m_finalDis->setString(s);
    ss.clear();
    
    ss << high_score;
    ss >> s;
    m_highDis->setString(s);
    ss.clear();
}


void GameOverMenu::retryCallback(Ref* _ref, MYButton::TouchEventType _type)
{
    if (_type == MYButton::TouchEventType::ENDED)
    {
        if (m_retryCallback)
        {
            m_retryCallback(this, _type);
        }
    }
}
void GameOverMenu::homeCallback(Ref* _ref, MYButton::TouchEventType _type)
{
    if (_type == MYButton::TouchEventType::ENDED)
    {
        if (m_homeCallback)
        {
            m_homeCallback(this, _type);
        }
    }
}