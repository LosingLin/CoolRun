//
//  MYButton.cpp
//  CoolRun
//
//  Created by ManYou on 14-8-25.
//
//

#include "MYButton.h"
#include "Base.h"
#include "AudioHelp.h"

MYButton::MYButton()
: Node()
, m_callback(nullptr)
, m_normalSp(nullptr)
, m_highLightSp(nullptr)
, m_disableSp(nullptr)
, b_isEnable(false)
, m_touchType(MYButtonType::ONEBYONE)
, m_touchListener(nullptr)
, m_allTouchListener(nullptr)
{
}
MYButton::~MYButton()
{
    CC_SAFE_RELEASE_NULL(m_touchListener);
    CC_SAFE_RELEASE_NULL(m_allTouchListener);
}

bool MYButton::init()
{
    
    setTouchEnabled(true);
    return true;
}

MYButton* MYButton::create(const string& _normal, const string& _highLight, const string& _disable)
{
    auto _btn = MYButton::create();
    
    auto _sp = Sprite::create(_normal);
    _btn->setNormalSprite(_sp);
    if (!_highLight.empty())
    {
        _sp = Sprite::create(_highLight);
        _btn->setHighLightSprite(_sp);
    }
    if (!_disable.empty())
    {
        _sp = Sprite::create(_disable);
        _btn->setDisableSprite(_sp);
    }
    
    return _btn;
}
MYButton* MYButton::createWithFrameName(const string& _normal, const string& _highLight, const string& _disable)
{
    auto _btn = MYButton::create();
    
    auto _sp = Sprite::createWithSpriteFrameName(_normal);
    _btn->setNormalSprite(_sp);
    if (!_highLight.empty())
    {
        _sp = Sprite::createWithSpriteFrameName(_highLight);
        _btn->setHighLightSprite(_sp);
    }
    if (!_disable.empty())
    {
        _sp = Sprite::createWithSpriteFrameName(_disable);
        _btn->setDisableSprite(_sp);
    }
    
    return _btn;
}

MYButton* MYButton::createWithContentSize(const Size& _size)
{
    
    auto _btn = MYButton::create();
    
    _btn->setContentSize(_size);
    
    return _btn;
}

void MYButton::setOpacity(GLubyte opacity)
{
    if (m_normalSp) {
        m_normalSp->setOpacity(opacity);
    }
    
    if (m_highLightSp) {
        m_highLightSp->setOpacity(opacity);
    }
    
    if (m_disableSp) {
        m_disableSp->setOpacity(opacity);
    }
}

void MYButton::setNormalSprite(Sprite* _sp)
{    
    SAFEREMOVEANDCLEARNCHILD(m_normalSp);
    m_normalSp = _sp;
    auto size = m_normalSp->getContentSize();
    this->setContentSize(size);
    m_normalSp->setPosition(Vec2(size.width/2, size.height/2));
    this->addChild(m_normalSp);
    
    this->displaySprites();
}
void MYButton::setHighLightSprite(Sprite* _sp)
{
    SAFEREMOVEANDCLEARNCHILD(m_highLightSp);
    m_highLightSp = _sp;
    auto size = this->getContentSize();
    m_highLightSp->setPosition(Vec2(size.width/2, size.height/2));
    this->addChild(m_highLightSp);
    
    this->displaySprites();
}
void MYButton::setDisableSprite(Sprite* _sp)
{
    SAFEREMOVEANDCLEARNCHILD(m_disableSp);
    m_disableSp = _sp;
    auto size = this->getContentSize();
    m_disableSp->setPosition(Vec2(size.width/2, size.height/2));
    this->addChild(m_disableSp);
    
    this->displaySprites();
}

void MYButton::displaySprites()
{
    if (!b_isEnable)
    {
        SAFESETVISIBLE(m_normalSp, false);
        SAFESETVISIBLE(m_highLightSp, false);
        SAFESETVISIBLE(m_disableSp, true);
    }
    else
    {
        SAFESETVISIBLE(m_normalSp, true);
        SAFESETVISIBLE(m_highLightSp, false);
        SAFESETVISIBLE(m_disableSp, false);
    }
}

bool MYButton::isTouchInContent(Touch *touch)
{
    auto _loc = convertTouchToNodeSpace(touch);
    auto _size = this->getContentSize();
    //log("touch loc : (%f, %f)", _loc.x, _loc.y);
    if (_loc.x >= 0 && _loc.x <= _size.width &&
        _loc.y >= 0 && _loc.y <= _size.height)
    {
        return true;
    }
    return false;
}

void MYButton::setTouchEnabled(bool enable, MYButtonType _type)
{
    if (enable == b_isEnable && _type == m_touchType)
    {
        return;
    }
    b_isEnable = enable;
    m_touchType = _type;
    
    if (m_touchListener)
    {
        _eventDispatcher->removeEventListener(m_touchListener);
        CC_SAFE_RELEASE_NULL(m_touchListener);
    }
    if (m_allTouchListener)
    {
        _eventDispatcher->removeEventListener(m_allTouchListener);
        CC_SAFE_RELEASE_NULL(m_allTouchListener);
    }
    
    if (b_isEnable)
    {
        if (m_touchType == MYButtonType::ONEBYONE)
        {
            m_touchListener = EventListenerTouchOneByOne::create();
            CC_SAFE_RETAIN(m_touchListener);
            m_touchListener->setSwallowTouches(true);
            m_touchListener->onTouchBegan = CC_CALLBACK_2(MYButton::onTouchBegan, this);
            m_touchListener->onTouchMoved = CC_CALLBACK_2(MYButton::onTouchMoved, this);
            m_touchListener->onTouchEnded = CC_CALLBACK_2(MYButton::onTouchEnded, this);
            m_touchListener->onTouchCancelled = CC_CALLBACK_2(MYButton::onTouchCancelled, this);
            _eventDispatcher->addEventListenerWithSceneGraphPriority(m_touchListener, this);
        }
        else
        {
            m_allTouchListener = EventListenerTouchAllAtOnce::create();
            CC_SAFE_RETAIN(m_allTouchListener);
            m_allTouchListener->onTouchesBegan = CC_CALLBACK_2(MYButton::onTouchesBegan, this);
            m_allTouchListener->onTouchesMoved = CC_CALLBACK_2(MYButton::onTouchesMoved, this);
            m_allTouchListener->onTouchesEnded = CC_CALLBACK_2(MYButton::onTouchesEnded, this);
            m_allTouchListener->onTouchesCancelled = CC_CALLBACK_2(MYButton::onTouchesCancelled, this);
            _eventDispatcher->addEventListenerWithSceneGraphPriority(m_allTouchListener, this);
            
        }
        
    }
    
    this->displaySprites();
}

void MYButton::addTouchEventListener(MYButtonCallback callback)
{
    this->m_callback = callback;
}

#pragma mark - touch event

bool MYButton::onTouchBegan(Touch *touch, Event *unusedEvent)
{
    
    if (!b_isEnable || !isVisible() || !isTouchInContent(touch))
    {
        return false;
    }
    if (m_highLightSp)
    {
        SAFESETVISIBLE(m_normalSp, false);
        SAFESETVISIBLE(m_highLightSp, true);
    }
    
    AudioHelp::playEft("btn_click.wav");
    
    if (m_callback)
    {
        m_callback(this, TouchEventType::BEGAN);
    }
    
    
    return true;
}
void MYButton::onTouchMoved(Touch *touch, Event *unusedEvent)
{
    if (m_callback)
    {
        m_callback(this, TouchEventType::MOVED);
    }
}
void MYButton::onTouchEnded(Touch *touch, Event *unusedEvent)
{
    if (m_highLightSp)
    {
        SAFESETVISIBLE(m_normalSp, true);
        SAFESETVISIBLE(m_highLightSp, false);
    }
    
    if (isTouchInContent(touch))
    {
        if (m_callback)
        {
            m_callback(this, TouchEventType::ENDED);
        }
    }
    
}
void MYButton::onTouchCancelled(Touch *touch, Event *unusedEvent)
{
    m_callback(this, TouchEventType::CANCELED);
}

void MYButton::onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *event)
{
    log("onTouchesBegan............");
    Size winSize = Director::getInstance()->getWinSize();
    vector<Touch*>::const_iterator touchIter = touches.begin();
    while(touchIter != touches.end())
    {
        Touch *pTouch = (Touch*)(*touchIter);
        if (!b_isEnable || !isVisible() || !isTouchInContent(pTouch))
        {
            ++ touchIter;
            continue;
        }
        if (m_highLightSp)
        {
            SAFESETVISIBLE(m_normalSp, false);
            SAFESETVISIBLE(m_highLightSp, true);
        }
        
        if (m_callback)
        {
            m_callback(this, TouchEventType::BEGAN);
        }
        ++ touchIter;
    }
}
    
void MYButton::onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *event)
{
}
void MYButton::onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *event)
{
    log("onTouchesEnded............");
    if (m_callback)
    {
        m_callback(this, TouchEventType::ENDED);
    }
}
void MYButton::onTouchesCancelled(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *event)
{
}