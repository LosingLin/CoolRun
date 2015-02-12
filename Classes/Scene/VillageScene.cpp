//
//  VillageScene.cpp
//  CoolRun
//
//  Created by ManYou on 14-9-5.
//
//

#include "VillageScene.h"
#include "Runner.h"
#include "Villager.h"


VillageLayer::VillageLayer()
: Layer()
, m_runner(nullptr)
{
}
VillageLayer::~VillageLayer()
{
}

bool VillageLayer::init()
{
    if (!Layer::init())
    {
        return false;
    }
    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("parkour.plist");
    Director::getInstance()->getTextureCache()->addImage("village_bg.png");
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto _bg = Sprite::create("village_bg.png");
    _bg->setAnchorPoint(Vec2::ZERO);
    _bg->setPosition(Vec2(origin.x, origin.y -180));
    this->addChild(_bg);
    
    m_runner = Runner::create();
    m_runner->setAnchorPoint(Vec2(0.5, 0));
    m_runner->setPosition(Vec2(origin.x + 120, origin.y + 160));
    this->addChild(m_runner, 15);
    
    auto _cz = Villager::createWithFrameName("v_cz.png", "中和村欢迎您！！风雪连天枯枝寂，寒崖陡峭剑客寥");
    _cz->setAnchorPoint(Vec2(0.5, 0));
    _cz->setPosition(Vec2(origin.x + 250, origin.y + 200));
    _cz->addTouchCallback(CC_CALLBACK_2(VillageLayer::villagerTouchCallback, this, _cz));
    this->addChild(_cz, 10);
    
    auto _mv = Villager::createWithFrameName("v_mn.png", "hey，帅哥～ 进来玩～～");
    _mv->setAnchorPoint(Vec2(0.5, 0));
    _mv->setPosition(Vec2(origin.x + 450, origin.y + 200));
    _mv->addTouchCallback(CC_CALLBACK_2(VillageLayer::villagerTouchCallback, this, _mv));
    this->addChild(_mv, 10);
    
    return true;
}

Scene* VillageLayer::createScene()
{
    auto _scene = Scene::create();
    auto _layer = VillageLayer::create();
    _scene->addChild(_layer);
    return _scene;
}

void VillageLayer::onEnter()
{
    Layer::onEnter();
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    
    listener->onTouchBegan = CC_CALLBACK_2(VillageLayer::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(VillageLayer::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(VillageLayer::onTouchEnded, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}
void VillageLayer::onExit()
{
}

void VillageLayer::villagerTouchCallback(Ref* _ref, MYButton::TouchEventType _type, Villager* _villager)
{
    if (_type == MYButton::TouchEventType::ENDED)
    {
        auto _loc = _villager->getPosition();
        this->runnerMove(_loc, CC_CALLBACK_0(VillageLayer::runnerTalk, this, _villager));
    }
}
void VillageLayer::runnerMove(const Vec2& _loc, const std::function<void()> &func)
{
    auto _pos = m_runner->getPosition();
    auto _distance = abs(_pos.x - _loc.x);
    
    auto _action = m_runner->getActionByTag(1000);
    if (_action)
    {
        m_runner->stopActionByTag(1000);
    }
    
    auto _time = _distance / 300;
    auto _moveTo = MoveTo::create(_time, Vec2(_loc.x, _pos.y));
    auto _call = CallFunc::create(func);
    auto _seq = Sequence::create(_moveTo, _call, NULL);
    _seq->setTag(1000);
    m_runner->runAction(_seq);
}

void VillageLayer::runnerMoveEnd()
{
    log("VillageLayer::runnerMoveEnd..");
}
void VillageLayer::runnerTalk(Villager* _villager)
{
    log("VillageLayer::runnerTalk..");
    
    _villager->talk();
    
}

#pragma mark - touch event

bool VillageLayer::onTouchBegan(Touch* touch, Event* event)
{
    return true;
}
void VillageLayer::onTouchMoved(Touch* touch, Event* event)
{
}
void VillageLayer::onTouchEnded(Touch* touch, Event* event)
{
    auto _loc = convertTouchToNodeSpace(touch);
    log("touch (%f, %f)", _loc.x, _loc.y);
    this->runnerMove(_loc, CC_CALLBACK_0(VillageLayer::runnerMoveEnd, this));
}