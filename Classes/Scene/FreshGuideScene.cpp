//
//  FreshGuideScene.cpp
//  CoolRun
//
//  Created by ManYou on 15/4/27.
//
//

#include "FreshGuideScene.h"
#include "MYScene.h"
#include "ActionHelp.h"
#include "CoolRunScene.h"


FreshGuideLayer::FreshGuideLayer()
: Layer()
, m_closeBtn(nullptr)
{
}
FreshGuideLayer::~FreshGuideLayer()
{
}

bool FreshGuideLayer::init()
{
    if (!Layer::init())
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto bg = LayerColor::create(Color4B(0, 0, 0, 150));
    this->addChild(bg);
    
    auto left = LayerColor::create(Color4B(255, 255, 255, 200), visibleSize.width/2-2, visibleSize.height);
    left->setPosition(Vec2(origin.x, origin.y));
    this->addChild(left);
    auto leftTap = Sprite::createWithSpriteFrameName("tap01.png");
    leftTap->setPosition(Vec2(origin.x + visibleSize.width/4, origin.y + visibleSize.height/2 - 60));
    this->addChild(leftTap);
    auto leftAction = ActionHelp::createFrameAction("tap%02d.png", 1, 4, 0.3);
    leftTap->runAction(leftAction);
    auto leftText = Label::createWithBMFont("F.fnt", "Atk");
    leftText->setPosition(Vec2(origin.x + visibleSize.width/4, origin.y + visibleSize.height/2 + 30));
    this->addChild(leftText);
    auto _scaleTo01 = ScaleTo::create(0.2, 1.4f);
    auto _scaleTo02 = ScaleTo::create(0.2, 1.0f);
    leftText->runAction(RepeatForever::create(Sequence::create(_scaleTo01, _scaleTo02, NULL)));
    
    auto right = LayerColor::create(Color4B(255, 255, 255, 200), visibleSize.width/2-2, visibleSize.height);
    right->setPosition(Vec2(origin.x + visibleSize.width/2+2, origin.y));
    this->addChild(right);
    auto rightTap = Sprite::createWithSpriteFrameName("tap01.png");
    rightTap->setPosition(Vec2(origin.x + visibleSize.width*3/4, origin.y + visibleSize.height/2 - 60));
    this->addChild(rightTap);
    auto rightAction = ActionHelp::createFrameAction("tap%02d.png", 1, 4, 0.3);
    rightTap->runAction(rightAction);
    auto rigthText = Label::createWithBMFont("F.fnt", "Jump");
    auto pos = Vec2(origin.x + visibleSize.width*3/4, origin.y + visibleSize.height/2 + 30);
    rigthText->setPosition(pos);
    this->addChild(rigthText);
    auto _jump = JumpBy::create(0.5, Vec2(0, 0), 120, 1);
    rigthText->runAction(RepeatForever::create(_jump));
    
    m_closeBtn = MYButton::createWithFrameName("btn_close.png");
    m_closeBtn->setPosition(Vec2(origin.x + visibleSize.width - 100, origin.y + visibleSize.height - 100));
    m_closeBtn->addTouchEventListener(CC_CALLBACK_2(FreshGuideLayer::closeBtnCallback, this));
    this->addChild(m_closeBtn);
    
    auto  touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);
    touchListener->onTouchBegan = CC_CALLBACK_2(FreshGuideLayer::onTouchBegan, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(FreshGuideLayer::onTouchMoved, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(FreshGuideLayer::onTouchEnded, this);
    touchListener->onTouchCancelled = CC_CALLBACK_2(FreshGuideLayer::onTouchCancelled, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    this->setLocalZOrder(ZORDER_FRESHGUIDE);
    
    return true;
}

void FreshGuideLayer::closeBtnCallback(Ref* _ref, MYButton::TouchEventType _type)
{
    if (_type == MYButton::TouchEventType::ENDED)
    {
        this->removeFromParentAndCleanup(true);
    }
}

void FreshGuideLayer::setCloseCallback(MYButton::MYButtonCallback callback)
{
    m_closeBtn->addTouchEventListener(callback);
}

bool FreshGuideLayer::onTouchBegan(Touch *touch, Event *unusedEvent)
{
    return true;
}
void FreshGuideLayer::onTouchMoved(Touch *touch, Event *unusedEvent)
{
    
}
void FreshGuideLayer::onTouchEnded(Touch *touch, Event *unusedEvent)
{
    
}
void FreshGuideLayer::onTouchCancelled(Touch *touch, Event *unusedEvent)
{
    
}

Scene* FreshGuideLayer::createScene()
{
    auto _scene = MYScene::create();
    auto _layer = FreshGuideLayer::create();
    _scene->addChild(_layer);
    return _scene;
}