//
//  CoolRunScene.cpp
//  CoolRun
//
//  Created by ManYou on 14-8-7.
//
//

#include "CoolRunScene.h"
#include "GravityPhysics.h"
#include "CollideTrack.h"
#include "PhysicNode.h"
#include "PhysicHelp.h"
#include "Runner.h"
#include "Stone.h"
#include "Coin.h"
#include "Mission.h"
#include "MissionInterface.h"
#include "MissionDataInterface.h"
#include "MissionObjects.h"
#include "MissionCollection.h"
#include "MissionEvent.h"
#include "JsonHelp.h"
#include "MYButton.h"
#include "Background.h"
#include "Home.h"
#include "HomeHelp.h"
#include "SpiderPoison.h"
#include "Bullet.h"
#include "Spider.h"
#include "BossDoubleHeads.h"
#include "Score.h"
#include "Stretch.h"
#include "PopViewLayer.h"
#include "MenuScene.h"

#define kWarningTag 100
#define kPauseViewTag 101
#define kOverViewTag  102

CoolRun::CoolRun()
: Layer()
, m_gameState(GameState::HOME)
, m_resCacheCount(0)
, m_velocity(0.0f)
, m_runners(nullptr)
, m_gPhysics(NULL)
, m_cTrack(NULL)
, m_gravityCollideObjs(nullptr)
, m_dirCollideObjs(NULL)
, m_simpleCollideObjs(NULL)
, m_bulletObjs(nullptr)
, m_mission(NULL)
, m_totalStretch(0.0f)
, m_totalStretchForInt(0)
, m_pageStretch(0.0f)
, m_stretchLab(NULL)
, m_pageSLab(nullptr)
, m_pacBtn(nullptr)
, m_jumpBtn(nullptr)
, m_atkBtn(nullptr)
, m_events(nullptr)
, m_nextPage(nullptr)
, m_curPage(nullptr)
, m_farBG(nullptr)
, m_midBG(nullptr)
, m_home(nullptr)
, m_help(nullptr)
, m_enemy(nullptr)
, b_isPaused(false)
, m_scoreView(nullptr)
, m_score(0)
, m_stretchView(nullptr)
, m_stretch(0)
{
}
CoolRun::~CoolRun()
{
    CC_SAFE_RELEASE_NULL(m_gPhysics);
    CC_SAFE_RELEASE_NULL(m_cTrack);
    CC_SAFE_RELEASE_NULL(m_dirCollideObjs);
    CC_SAFE_RELEASE_NULL(m_simpleCollideObjs);
    CC_SAFE_RELEASE_NULL(m_mission);
    CC_SAFE_RELEASE_NULL(m_events);
    
    CC_SAFE_RELEASE_NULL(m_curPage);
    CC_SAFE_RELEASE_NULL(m_nextPage);
}

Scene* CoolRun::createScene(Mission* mission)
{
    auto _scene = Scene::create();
    auto _layer = CoolRun::create(mission);
    _scene->addChild(_layer);
    return _scene;
}

bool CoolRun::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    //设置随机数种子
    srand((int)time(0));
    
    m_velocity = 0.0f;
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
//    Director::getInstance()->getTextureCache()->addImageAsync("bg001.png", CC_CALLBACK_1(CoolRun::finishAddImage, this));
//    Director::getInstance()->getTextureCache()->addImageAsync("bg002.png", CC_CALLBACK_1(CoolRun::finishAddImage, this));
    
//    Director::getInstance()->getTextureCache()->addImageAsync("bg001.png", std::bind(&CoolRun::finishAddImage, this, std::placeholders::_1));
    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("parkour.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("tempRes.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("runner.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("background.plist");
    
//    Director::getInstance()->getTextureCache()->addImage("bg001.png");
//    Director::getInstance()->getTextureCache()->addImage("bg002.png");
    
    m_gPhysics = GravityPhysics::create();
    m_gPhysics->setGravity(-200.0f);
    CC_SAFE_RETAIN(m_gPhysics);
    m_cTrack = CollideTrack::create();
    CC_SAFE_RETAIN(m_cTrack);
    
    //init objects
    CREATEANDRETAINARRAY(m_runners);
    CREATEANDRETAINARRAY(m_dirCollideObjs);
    CREATEANDRETAINARRAY(m_simpleCollideObjs);
    CREATEANDRETAINARRAY(m_gravityCollideObjs);
    CREATEANDRETAINARRAY(m_bulletObjs);
    CREATEANDRETAINARRAY(m_events);
    
    float scale = 1264.0/1024.0;
    
    auto bg = Sprite::createWithSpriteFrameName("bg.png");
    bg->setScale(scale);
    bg->setAnchorPoint(Vec2::ZERO);
    this->addChild(bg);
    
    m_farBG = Background::create("bg03_01.png", "bg03_02.png");
    m_farBG->setVelocity(m_velocity*0.5f);
    m_farBG->setPosition(Vec2(0, 0));
    this->addChild(m_farBG);
    
    auto cover = Sprite::createWithSpriteFrameName("bg_cover.png");
    cover->setScale(scale);
    cover->setAnchorPoint(Vec2::ZERO);
    this->addChild(cover);
    
    m_midBG = Background::create("bg04_01.png", "bg04_02.png");
    m_midBG->setVelocity(m_velocity*1.0f);
    m_midBG->setPosition(Vec2(0, 0));
    this->addChild(m_midBG);

    m_scoreView = Score::create();
    m_scoreView->setPosition(Vec2(origin.x + 2, origin.y + visibleSize.height - 56));
    m_scoreView->setLocalZOrder(ZORDER_HEADMENU);
    this->addChild(m_scoreView);
    
    m_stretchView = Stretch::create();
    m_stretchView->setPosition(Vec2(origin.x + 600, origin.y + visibleSize.height - 56));
    m_stretchView->setLocalZOrder(ZORDER_HEADMENU);
    this->addChild(m_stretchView);
    
    //stretch lab
    m_stretchLab = Label::createWithTTF("00", "Marker Felt.ttf", 36);
    m_stretchLab->setHorizontalAlignment(TextHAlignment::LEFT);
    m_stretchLab->setVerticalAlignment(TextVAlignment::CENTER);
    m_stretchLab->setAnchorPoint(Vec2(0, 0.5));
    m_stretchLab->setPosition(Vec2(origin.x + 260, origin.y + visibleSize.height - 20));
    this->addChild(m_stretchLab, 100);
    
    m_pageSLab = Label::createWithTTF("00", "Marker Felt.ttf", 36);
    m_pageSLab->setHorizontalAlignment(TextHAlignment::LEFT);
    m_pageSLab->setVerticalAlignment(TextVAlignment::CENTER);
    m_pageSLab->setAnchorPoint(Vec2(0, 0.5));
    m_pageSLab->setPosition(Vec2(origin.x + 520, origin.y + visibleSize.height - 20));
    this->addChild(m_pageSLab, 100);
    
    //m_mission = Mission::create("test", Mission::MissionRepeatModel::LAST);
//    m_mission = Mission::create("{\"e\":{\"num\":1}, \"n\":{\"num\":1}, \"h\":{\"num\":1}}");
//    CC_SAFE_RETAIN(m_mission);
    
    m_home = Home::create();
    this->addChild(m_home);
    m_gPhysics->addPhysicNode(m_home);
    m_dirCollideObjs->addObject(m_home);
    
    //this->loadNextPage(true); //第一屏
    //this->loadNextPage(); //预加载第二屏
    
    m_atkBtn = MYButton::createWithFrameName("Skill_n.png", "Skill_h.png", "Skill_d.png");
    m_atkBtn->addTouchEventListener(CC_CALLBACK_2(CoolRun::SkillBtnCallback, this));
    m_atkBtn->setPosition(Vec2(origin.x + 100, origin.y + 100));
    m_atkBtn->setAnchorPoint(Vec2(0.5, 0.5));
    m_atkBtn->setTouchEnabled(true, MYButton::MYButtonType::ALLATONCE);
    this->addChild(m_atkBtn, 100);
    m_atkBtn->setOpacity(100);
    
    
    m_jumpBtn = MYButton::createWithFrameName("Jump_n.png", "Jump_h.png", "Jump_d.png");
    m_jumpBtn->addTouchEventListener(CC_CALLBACK_2(CoolRun::JumpBtnCallback, this));
    m_jumpBtn->setPosition(Vec2(origin.x + visibleSize.width - 100, origin.y + 100));
    m_jumpBtn->setAnchorPoint(Vec2(0.5, 0.5));
    m_jumpBtn->setTouchEnabled(true, MYButton::MYButtonType::ALLATONCE);
    this->addChild(m_jumpBtn, 100);
    m_jumpBtn->setOpacity(100);
    
    m_pacBtn = MYButton::createWithFrameName("btn_pause.png");
    m_pacBtn->addTouchEventListener(CC_CALLBACK_2(CoolRun::PacBtnCallback, this));
    m_pacBtn->setPosition(Vec2(origin.x + visibleSize.width - 50, origin.y + visibleSize.height - 50));
    m_pacBtn->setAnchorPoint(Vec2(0.5, 0.5));
    m_pacBtn->setTouchEnabled(true, MYButton::MYButtonType::ALLATONCE);
    this->addChild(m_pacBtn, 100);
    //m_pacBtn->setOpacity(100);
    

    return true;
}

bool CoolRun::init(Mission* mission)
{
    if (!this->init())
    {
        return false;
    }
    
    this->setMission(mission);
    
    return true;
}
CoolRun* CoolRun::create(Mission* mission)
{
    auto cr = new CoolRun();
    if (cr && cr->init(mission))
    {
        cr->autorelease();
        return cr;
    }
    delete cr;
    return nullptr;
}

void CoolRun::setMission(Mission* mission)
{
    CC_SAFE_RELEASE_NULL(m_mission);
    m_mission = mission;
    CC_SAFE_RETAIN(m_mission);
}

#pragma mark - add

void CoolRun::addRunner()
{
    auto runner = Runner::create();
    runner->setPosition(Vec2(300, 240));
    runner->setGameController(this);
    this->addChild(runner);
    
    m_gPhysics->addPhysicNode(runner);
    m_gravityCollideObjs->addObject(runner);
    //m_cTrack->addPhysicNode(runner);
    
    m_runners->addObject(runner);
}
void CoolRun::addSpiderAndHelp()
{
    m_help = HomeHelp::create();
    m_help->setPosition(Vec2(300, 300));
    this->addChild(m_help, 2);
    m_help->setGravityEffect(true);
    
    m_gPhysics->addPhysicNode(m_help);
    m_gravityCollideObjs->addObject(m_help);
    
    m_enemy = SpiderPoison::create();
    m_enemy->setPosition(Vec2(720, 200));
    m_enemy->setState(kSpiderState_Walk);
    m_enemy->setGravityEffect(true);
    m_enemy->setScaleX(-1);
    auto rect = m_enemy->getCollideRect();
    m_enemy->setCollideRect(Rect(-rect.origin.x-rect.size.width, rect.origin.y, rect.size.width, rect.size.height));
    this->addChild(m_enemy, 2);
    
    
    m_gPhysics->addPhysicNode(m_enemy);
    m_gravityCollideObjs->addObject(m_enemy);
    
    m_help->setXV(300);
    m_enemy->setXV(300);
}

void CoolRun::addBoss()
{
    auto boss = BossDoubleHeads::create();
    boss->setPosition(Vec2(1400, 500));
    m_gPhysics->addPhysicNode(boss);
    m_gravityCollideObjs->addObject(boss);
    m_simpleCollideObjs->addObject(boss);
    boss->setGameController(this);
    boss->setLocalZOrder(ZORDER_ANIMAL);
    boss->setXV(-this->getVelocity());
    this->addChild(boss);
}

void CoolRun::showBossWarning()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto label = Label::createWithTTF("WARNING", "Marker Felt.ttf", 102);
    label->setTag(kWarningTag);
    label->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2));
    label->setLocalZOrder(ZORDER_WARNING);
    this->addChild(label);
    
    auto scale01 = ScaleTo::create(0.5, 1.2);
    auto scale02 = ScaleTo::create(0.5, 1.0);
    auto fadeOut = FadeOut::create(0.5);
    auto callfunc = CallFunc::create(CC_CALLBACK_0(CoolRun::showBossWarningEnd, this));
    
    label->runAction(Sequence::create(scale01, scale02, fadeOut, callfunc, NULL));
}
void CoolRun::showBossWarningEnd()
{
    this->getChildByTag(kWarningTag)->removeFromParentAndCleanup(true);
    this->addBoss();
}

void CoolRun::hideController()
{
    m_jumpBtn->setVisible(false);
    m_atkBtn->setVisible(false);
}
void CoolRun::showController()
{
    m_jumpBtn->setVisible(true);
    m_atkBtn->setVisible(true);
}

void CoolRun::actionCallback()
{
    if (GameState::ATTACK == m_gameState)
    {
        this->addSpiderAndHelp();
    }
    else if (GameState::RUNNING == m_gameState)
    {
        this->setVelocity(400);
        
        this->loadNextPage();
        this->addRunner();
        
        this->showController();
    }
}
void CoolRun::doorCloseCallback()
{
    m_home->closeDoor();
}

void CoolRun::setVelocity(int v)
{
    auto vc = m_velocity-v;
    m_velocity = v;
    //log("#####SetVeloctiy#### %d", v);
    this->_setVelocity(m_simpleCollideObjs, vc);
    this->_setVelocity(m_dirCollideObjs, vc);
    this->_setVelocity(m_bulletObjs, vc);
    m_farBG->setVelocity(m_velocity*0.5f);
    m_midBG->setVelocity(m_velocity*1.0f);
}
void CoolRun::_setVelocity(__Array* _nodes, int vc)
{
    for (int i = 0; i < _nodes->count(); ++ i)
    {
        auto node = dynamic_cast<PhysicNode*>(_nodes->getObjectAtIndex(i));
        auto xv = node->getXV();
        xv += vc;
        node->setXV(xv);
    }
}

#pragma mark - button callback

void CoolRun::PacBtnCallback(Ref* _btn, MYButton::TouchEventType _type)
{
    if (_type == MYButton::TouchEventType::BEGAN)
    {
        log("CoolRun::PacBtnCallback began");
        
        this->pause();
        this->addPauseMenu();
    }
}

void CoolRun::SkillBtnCallback(Ref* _btn, MYButton::TouchEventType _type)
{
    if (_type == MYButton::TouchEventType::BEGAN)
    {
        log("CoolRun::SkillBtnCallback began");
        
        for (int i = 0; i < m_runners->count(); ++ i)
        {
            Runner* runner = dynamic_cast<Runner*>(m_runners->getObjectAtIndex(i));
            runner->attack();
        }
    }
}
void CoolRun::JumpBtnCallback(Ref* _btn, MYButton::TouchEventType _type)
{
    if (_type == MYButton::TouchEventType::BEGAN)
    {
        log("CoolRun::JumpBtnCallback began");
        
        for (int i = 0; i < m_runners->count(); ++ i)
        {
            Runner* runner = dynamic_cast<Runner*>(m_runners->getObjectAtIndex(i));
            runner->jump();
        }
    } 
}

void CoolRun::onEnter()
{
    Layer::onEnter();
    log("CoolRun.......onEnter");
    
//    m_bg->runAction(MoveTo::create(5, Vec2(-2268, 0)));
    
    //this->scheduleUpdate();
    //this->schedule(CC_CALLBACK_1(CoolRun::update, this), 0.01f);
    //this->schedule(schedule_selector(CoolRun::gameMain), 0.0f);
    Director::getInstance()->getScheduler()->schedule(schedule_selector(CoolRun::gameMain), this, 0.0f, kRepeatForever, 0.0f, false);
//    this->scheduleUpdateWithPriority(Scheduler::PRIORITY_SYSTEM);
    
//    auto listener = EventListenerTouchOneByOne::create();
//    listener->setSwallowTouches(true);
//    
//    listener->onTouchBegan = CC_CALLBACK_2(CoolRun::onTouchBegan, this);
//    listener->onTouchMoved = CC_CALLBACK_2(CoolRun::onTouchMoved, this);
//    listener->onTouchEnded = CC_CALLBACK_2(CoolRun::onTouchEnded, this);
//    
//    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

}
void CoolRun::onEnterTransitionDidFinish()
{
    Layer::onEnterTransitionDidFinish();
    log("CoolRun.......onEnterTransitionDidFinish");
}
void CoolRun::onExitTransitionDidStart()
{
    log("CoolRun.......onExitTransitionDidStart");
    Layer::onExitTransitionDidStart();
}
void CoolRun::onExit()
{
    log("CoolRun.......onExit");
    Layer::onExit();
}

void CoolRun::finishAddImage(Texture2D* texture)
{
    log("CoolRun.......finishAddImage");
    
    ++m_resCacheCount;
    if (m_resCacheCount == 2) {
        this->lazyInit();
    }
}

void CoolRun::lazyInit()
{
    log("CoolRun.......lazyInit");
}


#pragma mark - touch

bool CoolRun::onTouchBegan(Touch* touch, Event* event)
{
    return true;
}
void CoolRun::onTouchMoved(Touch* touch, Event* event)
{
}
void CoolRun::onTouchEnded(Touch* touch, Event* event)
{
    log("onTouchEnded..");
}

#pragma mark - collide track

void CoolRun::directionCollideTrack()
{
    PhysicNode* node1 = NULL;
    
    
    for (int j = 0; j < m_gravityCollideObjs->count(); ++ j)
    {
        int cTimes[kCollideDirectionTotal] = {0};
        int pNodeIndex[kCollideDirectionTotal] = {0};
        auto pNodeCount = m_dirCollideObjs->count();
        
        auto node2 = dynamic_cast<PhysicNode*>(m_gravityCollideObjs->getObjectAtIndex(j));
        
        for (int i = 0; i < pNodeCount; ++ i)
        {
            node1 = dynamic_cast<PhysicNode*>(m_dirCollideObjs->getObjectAtIndex(i));
            
            
            if (!node1->isCollideEffect())
            {
                cTimes[kCollideDirectionMiss] ++;
                pNodeIndex[kCollideDirectionMiss] = i;
                continue;
            }
            
            auto rect1 = PhysicHelp::countPhysicNodeRect(node1);
            auto rect2 = PhysicHelp::countPhysicNodeRect(node2);
            
            auto direction = m_cTrack->trackCollideDirection(rect1, rect2);
            
            switch (direction) {
                case kCollideDirectionUnknown:
                {
                    cTimes[kCollideDirectionUnknown] ++;
                    pNodeIndex[kCollideDirectionUnknown] = i;
                }
                    break;
                case kCollideDirectionMiss:
                {
                    cTimes[kCollideDirectionMiss] ++;
                    pNodeIndex[kCollideDirectionMiss] = i;
                }
                    break;
                case kCollideDirectionLeft:
                {
                    cTimes[kCollideDirectionLeft] ++;
                    pNodeIndex[kCollideDirectionLeft] = i;
                }
                    break;
                case kCollideDirectionRight:
                {
                    cTimes[kCollideDirectionRight] ++;
                    pNodeIndex[kCollideDirectionRight] = i;
                }
                    break;
                case kCollideDirectionUp:
                {
                    cTimes[kCollideDirectionUp] ++;
                    pNodeIndex[kCollideDirectionUp] = i;
                }
                    break;
                case kCollideDirectionDown:
                {
                    cTimes[kCollideDirectionDown] ++;
                    pNodeIndex[kCollideDirectionDown] = i;
                }
                    break;
                    
                default:
                    break;
            }
        }
        
        //在空中
        if (cTimes[kCollideDirectionMiss] == pNodeCount) {
            node2->CollideTrackListener_CollideAll(kCollideDirectionMiss);
            continue;
        }
        
        //踩在地面上，而且碰到地面时
        if (cTimes[kCollideDirectionUp] > 0 && cTimes[kCollideDirectionLeft] > 0) {
            auto leftLand = dynamic_cast<Land*>(m_dirCollideObjs->getObjectAtIndex(pNodeIndex[kCollideDirectionLeft]));
            if (leftLand->isLeftIgnore())
            {
                node2->CollideTrackListener_CollideOnce(kCollideDirectionUp, leftLand);
            }
            else
            {
                node2->CollideTrackListener_CollideOnce(kCollideDirectionLeft, leftLand);
            }
            node2->CollideTrackListener_CollideOnce(kCollideDirectionUp, dynamic_cast<PhysicNode*>(m_dirCollideObjs->getObjectAtIndex(pNodeIndex[kCollideDirectionUp])));
            continue;
        }
        
        //踩在地面上
        if (cTimes[kCollideDirectionUp] > 0) {
            node2->CollideTrackListener_CollideOnce(kCollideDirectionUp, dynamic_cast<PhysicNode*>(m_dirCollideObjs->getObjectAtIndex(pNodeIndex[kCollideDirectionUp])));
            continue;
        }
        
        //碰到前面的地面
        if (cTimes[kCollideDirectionLeft] > 0) {
            auto leftLand = dynamic_cast<Land*>(m_dirCollideObjs->getObjectAtIndex(pNodeIndex[kCollideDirectionLeft]));
            if (leftLand->isLeftIgnore())
            {
                node2->CollideTrackListener_CollideOnce(kCollideDirectionUp, leftLand);
            }
            else
            {
                node2->CollideTrackListener_CollideOnce(kCollideDirectionLeft, leftLand);
            }
//            node2->CollideTrackListener_CollideOnce(kCollideDirectionLeft, dynamic_cast<PhysicNode*>(m_dirCollideObjs->getObjectAtIndex(pNodeIndex[kCollideDirectionLeft])));
            continue;
        }
        
        if (cTimes[kCollideDirectionRight])
        {
            auto leftLand = dynamic_cast<Land*>(m_dirCollideObjs->getObjectAtIndex(pNodeIndex[kCollideDirectionRight]));
            if (leftLand->isRightIgnore())
            {
                node2->CollideTrackListener_CollideOnce(kCollideDirectionUp, leftLand);
            }
            else
            {
                node2->CollideTrackListener_CollideOnce(kCollideDirectionRight, leftLand);
            }
            continue;
        }
        
        //头顶到地面
        if (cTimes[kCollideDirectionDown] > 0) {
            auto leftLand = dynamic_cast<Land*>(m_dirCollideObjs->getObjectAtIndex(pNodeIndex[kCollideDirectionDown]));
            if (leftLand->isDownIgnore())
            {
                node2->CollideTrackListener_CollideOnce(kCollideDirectionUp, leftLand);
            }
            else
            {
                node2->CollideTrackListener_CollideOnce(kCollideDirectionDown, leftLand);
            }

//            node2->CollideTrackListener_CollideOnce(kCollideDirectionDown, dynamic_cast<PhysicNode*>(m_dirCollideObjs->getObjectAtIndex(pNodeIndex[kCollideDirectionDown])));
            continue;
        }
        
    }
}

void CoolRun::simpleCollideTrack()
{
    CollideNode* node1 = NULL;
    
    for (int i = 0; i < m_simpleCollideObjs->count(); ++ i)
    {
        node1 = dynamic_cast<CollideNode*>(m_simpleCollideObjs->getObjectAtIndex(i));
        
        if (!node1->isCollideEffect() || node1->isDestoryed())
        {
            continue;
        }
        
        for (int i = 0; i < m_runners->count(); ++ i)
        {
            Runner* runner = dynamic_cast<Runner*>(m_runners->getObjectAtIndex(i));
            
            if (!node1->isCollideEffect() || node1->isDestoryed())
            {
                continue;
            }
            
            node1->trackCollideWithRunner(runner);
        }
        
    }
}

void CoolRun::bulletCollideTrack()
{
    Bullet* bullet = nullptr;
    for (int i = 0; i < m_bulletObjs->count(); ++ i)
    {
        bullet = dynamic_cast<Bullet*>(m_bulletObjs->getObjectAtIndex(i));
        
        if (!bullet->isCollideEffect() || bullet->isDestoryed())
        {
            continue;
        }
        
        if (bullet->isAnimalHurt())
        {
            CollideNode* node1 = NULL;
            
            for (int i = 0; i < m_simpleCollideObjs->count(); ++ i)
            {
                node1 = dynamic_cast<CollideNode*>(m_simpleCollideObjs->getObjectAtIndex(i));
                
                if (!node1->isCollideEffect() || node1->isDestoryed())
                {
                    continue;
                }
                
                node1->trackCollideWithBullet(bullet);
                
            }
        }
        
        if (bullet->isRunnerHurt())
        {
            for (int i = 0; i < m_runners->count(); ++ i)
            {
                Runner* runner = dynamic_cast<Runner*>(m_runners->getObjectAtIndex(i));
                if (!bullet->isCollideEffect() || bullet->isDestoryed())
                {
                    continue;
                }
                //bullet->trackCollideWithRunner(runner);
                runner->trackCollideWithBullet(bullet);
            }
        }
        
    }
}

#pragma mark - updates

void CoolRun::gameMain(float delta)
{
//    log("CoolRun.......update : %f", delta);
    
    if (GameState::HOME == m_gameState)
    {
        this->hideController();
        m_velocity = 0.0f;
        m_gameState = GameState::ATTACK;
        m_home->openDoor();
        
        this->runAction(Sequence::create(DelayTime::create(0.3), CallFunc::create(CC_CALLBACK_0(CoolRun::actionCallback, this)), NULL));
        this->runAction(Sequence::create(DelayTime::create(1), CallFunc::create(CC_CALLBACK_0(CoolRun::doorCloseCallback, this)), NULL));
    }
    else if (GameState::ATTACK == m_gameState)
    {
        if (m_help)
        {
            auto pos = m_help->getPosition();
            if (pos.x > 1264)
            {
                this->destory(m_help);
                m_help = nullptr;
                
                m_gameState = GameState::RUN;
            }
        }
        
        if (m_enemy)
        {
            auto pos = m_enemy->getPosition();
            if (pos.x > 1364)
            {
                this->destory(m_enemy);
                m_enemy = nullptr;
            }
        }
        
    }
    else if(GameState::RUN == m_gameState)
    {
        m_gameState = GameState::RUNNING;
        m_home->openDoor();
        
        this->runAction(Sequence::create(DelayTime::create(0.3), CallFunc::create(CC_CALLBACK_0(CoolRun::actionCallback, this)), NULL));
        this->runAction(Sequence::create(DelayTime::create(1), CallFunc::create(CC_CALLBACK_0(CoolRun::doorCloseCallback, this)), NULL));
    }
    else if(GameState::BOSS == m_gameState)
    {
        
    }
    
    if (delta > 0.06f)
    {
        delta = 0.06f;
    }
    
    //计算路程
    this->totalStretchUpdate(delta);
    this->pageStretchUpdate(delta);
    
    //背景
    this->backGroundUpdate(delta);
    
    //物理模拟启动
    m_gPhysics->updatePhysicNodes(delta);
    
    this->checkEvents();
    
    
    //检测活物与方向上碰撞类型的物体的碰撞
    this->directionCollideTrack();
    
    if (m_runners->count() > 0)
    {
        //检测玩家与简单碰撞类型的物体的碰撞
        this->simpleCollideTrack();
        
        //子弹的碰撞
        this->bulletCollideTrack();
        
        for (int i = 0; i < m_runners->count(); ++ i)
        {
            Runner* runner = dynamic_cast<Runner*>(m_runners->getObjectAtIndex(i));
            auto yv = runner->getYV();
            if(yv >= -20 && yv <= 20 && runner->getRunnerState() == kRunnerState_JumpUp)
            {
                runner->setRunnerState(kRunnerState_JumpDown);
            }
            
            auto pos = runner->getPosition();
            if (pos.y <= -120)
            {
                this->dead(runner);
            }
            
            if (pos.x < -500)
            {
                this->dead(runner);
            }
            
        }
    }
    
    
    //m_cTrack->collideTrackUpdate();
    for (int i = 0; i < m_runners->count(); ++ i)
    {
        auto runner = dynamic_cast<Runner*>(m_runners->getObjectAtIndex(i));
        if (runner->isLandBuildING())
        {
            this->buildLand(runner);
        }
    }
    
    //移除出屏的对象
    this->checkObjectsOut();
    //销毁被标记要销毁的对象
    this->checkObjectsDestoryed();
}

void CoolRun::update(float delta)
{
    this->gameMain(delta);
}

void CoolRun::backGroundUpdate(float delta)
{
    
    m_farBG->updateBackGround(delta);
    m_midBG->updateBackGround(delta);
    
//    for (int i = 0; i < m_references->count(); ++ i)
//    {
//        auto _sp = dynamic_cast<Sprite*>(m_references->getObjectAtIndex(i));
//        auto pos = _sp->getPosition();
//        pos.x -= m_velocity * delta;
//        if (pos.x < -1264)
//        {
//            pos.x = 1264;
//        }
//        
//        _sp->setPosition(pos);
//    }
}

void CoolRun::totalStretchUpdate(float delta)
{
    m_totalStretch += m_velocity * delta;
    
    if (m_totalStretchForInt != (int)m_totalStretch/30)
    {
        m_totalStretchForInt = (int)m_totalStretch/30;
        
        string s;
        stringstream ss(s);
        ss << m_totalStretchForInt;
        m_stretchLab->setString(ss.str());
        this->addScore(1);
        this->addStretch(1);
    }
    
    string s;
    stringstream ss(s);
    ss << m_pageStretch;
    m_pageSLab->setString(ss.str());
    
}
void CoolRun::pageStretchUpdate(float delta)
{
    m_pageStretch += m_velocity * delta;
    if (m_pageStretch >= 1264)
    {
        m_pageStretch = 0.0f;
        this->loadNextPage();
        //log("Load Next Page ..........");
    }
}
void CoolRun::checkEvents()
{
    if (!m_curPage)
    {
        return;
    }
    __Array* events = m_curPage->getEvents();
    for (int i = 0; i < events->count(); ++i)
    {
        auto event = dynamic_cast<MissionEvent*>(events->getObjectAtIndex(i));
        if (m_pageStretch >= event->getStartPageStretch())
        {
            this->_eventHappened(event);
            
            events->removeObject(event);
            i--;
        }
    }
}

#pragma mark - load

void CoolRun::_loadMissionDataInterface(MissionDataInterface* _missionDataInterface, bool isFirstPage)
{
    auto _dirCollideObjs = _missionDataInterface->getDirectionCollideObjects();
    
    //log("_dirCollideObjs : %zd", _dirCollideObjs->count());
    m_dirCollideObjs->addObjectsFromArray(_dirCollideObjs);
    m_gPhysics->addPhysicNodesFromArray(_dirCollideObjs);
    this->_addChildren(_dirCollideObjs, isFirstPage);
    
    auto _simpleCollideObjs = _missionDataInterface->getSimpleCollideObjects();
    log("_simpleCollideObjs : %zd", _simpleCollideObjs->count());
    for (int i = 0; i < _simpleCollideObjs->count(); ++ i)
    {
        auto _obj = dynamic_cast<PhysicNode*>(_simpleCollideObjs->getObjectAtIndex(i));
        
        m_simpleCollideObjs->addObject(_obj);
        m_gPhysics->addPhysicNode(_obj);
        if (_obj->isGravityEffect())
        {
            m_gravityCollideObjs->addObject(_obj);
        }
        
        auto _cobj = dynamic_cast<CollideNode*>(_obj);
        _cobj->setGameController(this);
    }
    this->_addChildren(_simpleCollideObjs, isFirstPage);
    
    auto _bulletCollideObjs = _missionDataInterface->getBulletCollideObjects();
    
    m_bulletObjs->addObjectsFromArray(_bulletCollideObjs);
    m_gPhysics->addPhysicNodesFromArray(_bulletCollideObjs);
    this->_addChildren(_bulletCollideObjs, isFirstPage);
}

void CoolRun::_loadMissionInterface(MissionInterface* _missionInterface, bool isFirstPage)
{
    log("Mission");
    this->_loadMissionDataInterface(_missionInterface->getMissionObjects(), isFirstPage);
    log("Collection");
    this->_loadMissionDataInterface(_missionInterface->getMissionCollection(), isFirstPage);
}

void CoolRun::_loadMissionEvents(__Array* _events)
{
    m_events->addObjectsFromArray(_events);
}

void CoolRun::loadNextPage(bool isFirstPage)
{
    auto _page = m_mission->getNextMissionPage();
    
    if (isFirstPage)
    {
        m_curPage = _page;
        CC_SAFE_RETAIN(m_curPage);
    }
    else
    {
        if (m_nextPage)
        {
            CC_SAFE_RELEASE(m_curPage);
            m_curPage = m_nextPage;
            CC_SAFE_RETAIN(m_curPage);
        }
        CC_SAFE_RELEASE(m_nextPage);
        m_nextPage = _page;
        CC_SAFE_RETAIN(m_nextPage);
    }
    
    if (_page->isLastPage())
    {
        if (GameState::BOSS != m_gameState)
        {
            m_gameState = GameState::BOSS;
            this->showBossWarning();
        }
    }
    
    
    log("==========PAGE=========");
    this->_loadMissionInterface(_page->getMissionInterface(), isFirstPage);
    //this->_loadMissionEvents(_page->getEvents());
    
    //this->buildLand();
    this->_smoothLand();
}
void CoolRun::_addChildren(__Array *_nodes, bool isFirstPage)
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    PhysicNode* _node = NULL;
    Vec2 _pos = Vec2(0, 0);
    float _xv = 0.0f;
    for (int i = 0; i < _nodes->count(); ++ i)
    {
        _node = dynamic_cast<PhysicNode*>(_nodes->getObjectAtIndex(i));
        
        _pos = _node->getPosition();
        //log("org %f, %f", _pos.x, _pos.y);
        //_pos.x += origin.x;
        //_pos.y += origin.y;
        //log("org %f, %f", _pos.x, _pos.y);
        if (!_node->isScreenPos())
        {
            if (!isFirstPage)
            {
                _pos.x += 1264;
            }
        }
        else
        {
            _pos.x += origin.x + _node->getAlignX() * visibleSize.width;
            _pos.y += origin.y + _node->getAlignY() * visibleSize.height;
        }
        _node->setPosition(_pos);
        
        
        _xv = _node->getXV();
        //log("xv %f", _xv);
        _xv -= m_velocity;
        //log("xv %f", _xv);
        _node->setXV(_xv);
        
        this->addChild(_node);
    }
}

void CoolRun::_smoothLand()
{
    for (int i = 0; i < m_dirCollideObjs->count(); ++i)
    {
        auto land1 = dynamic_cast<Land*>(m_dirCollideObjs->getObjectAtIndex(i));
        auto pos1 = land1->getPosition();
        auto csize1 = land1->getContentSize();
        auto rect1 = PhysicHelp::countPhysicNodeRect(land1);
        if (land1->isLand())
        {
            land1->setDownIgnore(true);
        }

        for (int j = 0; j < m_dirCollideObjs->count(); ++j)
        {
            auto land2 = dynamic_cast<Land*>(m_dirCollideObjs->getObjectAtIndex(j));
            auto pos2 = land2->getPosition();
            auto csize2 = land2->getContentSize();
            
            if (land1 == land2)
            {
                continue;
            }
            
            auto rect2 = PhysicHelp::countPhysicNodeRect(land2);
            
            if (abs(rect1.origin.y + rect1.size.height - rect2.origin.y - rect2.size.height) > 4)
            {
                continue;
            }
            
            if (pos2.x >= pos1.x && pos1.x + csize1.width >= pos2.x)
            {
                land1->setRightIgnore(true);
                land2->setLeftIgnore(true);
            }
            else if (pos1.x >= pos2.x && pos2.x + csize2.width >= pos1.x)
            {
                land1->setLeftIgnore(true);
                land2->setRightIgnore(true);
            }
        }
    }
}


#pragma mark - check

void CoolRun::checkObjectsOut()
{
    this->_checkObjectsOut(m_dirCollideObjs);
    this->_checkObjectsOut(m_simpleCollideObjs);
    this->_checkObjectsOut(m_bulletObjs);
}
void CoolRun::_checkObjectsOut(__Array* _nodes)
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    PhysicNode* _node = NULL;
    Vec2 _pos = Vec2(0, 0);
    Vec2 _aPoint = Vec2(0, 0);
    Size _cSize = Size(0, 0);
    for (int i = 0; i < _nodes->count(); ++ i)
    {
        _node = dynamic_cast<PhysicNode*>(_nodes->getObjectAtIndex(i));
        
        _pos = _node->getPosition();
        _aPoint = _node->getAnchorPoint();
        _cSize = _node->getContentSize();
        
        bool isNeedMove = false;
        if (_pos.x < origin.x)
        {
            
            if (_pos.x + (1-_aPoint.x) * _cSize.width < origin.x)
            {
                isNeedMove = true;
            }
        }
        
        if (_pos.y < origin.y)
        {
            if (_pos.y + (1-_aPoint.y) * _cSize.height < origin.y)
            {
                isNeedMove = true;
            }
        }
        
        if (_nodes == m_bulletObjs)
        {
            if (_pos.x > 2528)
            {
                if (_pos.x + (1-_aPoint.x) * _cSize.width > 2528)
                {
                    isNeedMove = true;
                }
            }
        }
        
        if (_pos.y > origin.y + visibleSize.height)
        {
            if (_pos.y + (1-_aPoint.y) * _cSize.height > origin.x + visibleSize.height)
            {
                isNeedMove = true;
            }
        }
        
        
        if (isNeedMove)
        {
//            _node->removeFromParentAndCleanup(true);
//            _node->setParent(nullptr);
//            _nodes->removeObject(_node);
//            m_gPhysics->removePhysicNode(_node);
//            if (_node->isGravityEffect())
//            {
//                m_gravityCollideObjs->removeObject(_node);
//            }
            this->destory(_node);
            i --;
        }
        
    }
}

void CoolRun::checkObjectsDestoryed()
{
    this->_checkObjectsDestoryed(m_dirCollideObjs);
    this->_checkObjectsDestoryed(m_simpleCollideObjs);
    this->_checkObjectsDestoryed(m_bulletObjs);
}
void CoolRun::_checkObjectsDestoryed(__Array* _nodes)
{
    PhysicNode* _node = NULL;
    for (int i = 0; i < _nodes->count(); ++ i)
    {
        _node = dynamic_cast<PhysicNode*>(_nodes->getObjectAtIndex(i));
        
        if (_node->isDestoryed())
        {
            this->destory(_node);
            i--;
            continue;
        }
    }
}


#pragma mark - event

void CoolRun::_eventHappened(MissionEvent* _event)
{
    log("==========EVENT============");
    this->_loadMissionInterface(_event->getMissionInterface(), true);
}

#pragma mark - bullet

void CoolRun::addBullet(Bullet* bullet, const Vec2& startPos, const Vec2& endPos, float duration)
{
    bullet->setPosition(startPos);
    auto moveTo = MoveTo::create(duration, endPos);
    bullet->runAction(moveTo);
    this->addBullet(bullet);
}
void CoolRun::addBullet(Bullet* bullet)
{
    bullet->setGameController(this);
    this->addChild(bullet);
    m_bulletObjs->addObject(bullet);
    m_gPhysics->addPhysicNode(bullet);
}

#pragma mark - spider

void CoolRun::addSpider(Spider* spider)
{
    this->addChild(spider);
    spider->setGameController(this);               
    m_simpleCollideObjs->addObject(spider);
    m_gPhysics->addPhysicNode(spider);
    if (spider->isGravityEffect())
    {
        m_gravityCollideObjs->addObject(spider);
    }
}

#pragma mark - pop view

void CoolRun::addPauseMenu()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto layer = PopViewLayer::create();
    layer->setTag(kPauseViewTag);
    this->addChild(layer, ZORDER_POPVIEW);
    
    auto resumeBtn = MYButton::createWithFrameName("btn_resume.png", "btn_hl_resume.png");
    resumeBtn->addTouchEventListener(CC_CALLBACK_2(CoolRun::ResumeBtnCallback, this));
    resumeBtn->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2 + 100));
    resumeBtn->setAnchorPoint(Vec2(0.5, 0.5));
    resumeBtn->setTouchEnabled(true, MYButton::MYButtonType::ONEBYONE);
    layer->addChild(resumeBtn);
    
    auto giveUpBtn = MYButton::createWithFrameName("btn_giveup.png", "btn_hl_giveup.png");
    giveUpBtn->addTouchEventListener(CC_CALLBACK_2(CoolRun::GiveUpBtnCallback, this));
    giveUpBtn->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2 - 140));
    giveUpBtn->setAnchorPoint(Vec2(0.5, 0.5));
    giveUpBtn->setTouchEnabled(true, MYButton::MYButtonType::ONEBYONE);
    layer->addChild(giveUpBtn);
}
void CoolRun::addOverMenu()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto layer = PopViewLayer::create();
    layer->setTag(kOverViewTag);
    this->addChild(layer, ZORDER_POPVIEW);
    
    auto helpmeBtn = MYButton::createWithFrameName("btn_helpme.png", "btn_hl_helpme.png");
    helpmeBtn->addTouchEventListener(CC_CALLBACK_2(CoolRun::HelpMeBtnCallback, this));
    helpmeBtn->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2 + 100));
    helpmeBtn->setAnchorPoint(Vec2(0.5, 0.5));
    helpmeBtn->setTouchEnabled(true, MYButton::MYButtonType::ONEBYONE);
    layer->addChild(helpmeBtn);
    
    auto giveUpBtn = MYButton::createWithFrameName("btn_giveup.png", "btn_hl_giveup.png");
    giveUpBtn->addTouchEventListener(CC_CALLBACK_2(CoolRun::GiveUpBtnCallback, this));
    giveUpBtn->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2 - 100));
    giveUpBtn->setAnchorPoint(Vec2(0.5, 0.5));
    giveUpBtn->setTouchEnabled(true, MYButton::MYButtonType::ONEBYONE);
    layer->addChild(giveUpBtn);
}
void CoolRun::removePauseMenu()
{
    auto node = this->getChildByTag(kPauseViewTag);
    if (node)
    {
        node->removeFromParentAndCleanup(true);
    }
}
void CoolRun::removeOverMenu()
{
    auto node = this->getChildByTag(kOverViewTag);
    if (node)
    {
        node->removeFromParentAndCleanup(true);
    }
}

void CoolRun::ResumeBtnCallback(Ref* _btn, MYButton::TouchEventType _type)
{
    if (_type == MYButton::TouchEventType::ENDED)
    {
        this->removePauseMenu();
        this->resume();
        
    }
}
void CoolRun::GiveUpBtnCallback(Ref* _btn, MYButton::TouchEventType _type)
{
    if (_type == MYButton::TouchEventType::ENDED)
    {
        this->removePauseMenu();
        this->removeOverMenu();
        this->resume();
        
        auto scene = MenuLayer::createScene();
        Director::getInstance()->replaceScene(scene);
    }
}
void CoolRun::HelpMeBtnCallback(Ref* _btn, MYButton::TouchEventType _type)
{
    if (_type == MYButton::TouchEventType::ENDED)
    {
        this->removeOverMenu();
        this->addRunner();
        this->resume();
    }
}


#pragma mark - GameController

void CoolRun::pause()
{
    b_isPaused = true;
    Director::getInstance()->pause();
}
void CoolRun::resume()
{
    b_isPaused = false;
    Director::getInstance()->resume();
}
void CoolRun::dead(Runner* runner)
{
    m_runners->removeObject(runner);
    m_gPhysics->removePhysicNode(runner);
    m_gravityCollideObjs->removeObject(runner);
    runner->removeFromParentAndCleanup(true);
    if (m_runners->count() <= 0)
    {
        this->addOverMenu();
        this->pause();
    }
    
    for (int i = 0; i < m_runners->count(); ++ i)
    {
        Runner* runner = dynamic_cast<Runner*>(m_runners->getObjectAtIndex(i));
        runner->displaySpareNum((int)m_runners->count());
    }
}
void CoolRun::addScore(int score)
{
    m_score += score;
    
    string s;
    stringstream ss(s);
    ss << m_score;
    m_scoreView->setString(ss.str());
}
void CoolRun::addStretch(int stretch)
{
    m_stretch += stretch;
    
    string s;
    stringstream ss(s);
    ss << m_stretch;
    m_stretchView->setString(ss.str());
}
void CoolRun::addCoin(int num)
{
}
void CoolRun::destory(PhysicNode* _node)
{
    _node->removeFromParentAndCleanup(true);
    _node->setParent(nullptr);
    auto _type = _node->getCollideType();
    
    if (CollideType::kCollideTypeSimple == _type)
    {
        m_simpleCollideObjs->removeObject(_node);
    }
    else if(CollideType::kCollideTypeDirection == _type)
    {
        m_dirCollideObjs->removeObject(_node);
    }
    else if(CollideType::kCollideTypeBullet == _type)
    {
        m_bulletObjs->removeObject(_node);
    }

    
    m_gPhysics->removePhysicNode(_node);
    if (_node->isGravityEffect())
    {
        m_gravityCollideObjs->removeObject(_node);
    }
    
    _node = nullptr;
}

#pragma mark - Item
void CoolRun::spareRunner(Runner* runner)
{
    int count = runner->getSpareNum();
    
    for (int i = 0; i < count; ++ i)
    {
        auto pos = runner->getPosition();
        Runner *r = Runner::create();
        float inc_x = rand()%200 - 200;
        float inc_y = rand()%200;
        pos.x += inc_x;
        pos.y += inc_y;
        r->setPosition(pos);
        
        r->setGameController(this);
        this->addChild(r);
        
        m_gPhysics->addPhysicNode(r);
        m_gravityCollideObjs->addObject(r);
        
        m_runners->addObject(r);
    }
    
    for (int i = 0; i < m_runners->count(); ++ i)
    {
        Runner* runner = dynamic_cast<Runner*>(m_runners->getObjectAtIndex(i));
        runner->displaySpareNum(m_runners->count());
    }
}

void CoolRun::buildLand(Runner* runner)
{
//    auto runner = getLastPosRunner();
//    if (!runner)
//    {
//        return;
//    }
    int trackSpace = 400.0f;
    auto runnerPos = runner->getPosition();
    
    auto trackPos = runnerPos;
    
    while (trackPos.x - runnerPos.x < trackSpace)
    {
        auto firstLand = getLand(trackPos);
        if (!firstLand)
        {
            firstLand = Stone::create();
            firstLand->setCollideType(kCollideTypeDirection);
            firstLand->setCollideEffect(true);
            firstLand->setPosition(Vec2(trackPos.x-60, 0.0f));
            firstLand->setXV(-this->getVelocity());
            m_gPhysics->addPhysicNode(firstLand);
            m_dirCollideObjs->addObject(firstLand);
            this->addChild(firstLand);
            
            firstLand->setLeftIgnore(true);
            firstLand->setDownIgnore(true);
            
//            firstLand->setLocalZOrder(ZORDER_RUNNER);
            
            auto nextLand = this->getNextLand(trackPos, trackSpace);
            if (nextLand)
            {
                auto pos = nextLand->getPosition();
                firstLand->setContentSize(Size(pos.x - trackPos.x > 90 ? pos.x - trackPos.x + 60 : 90 + 60, 180));
                auto csize = nextLand->getContentSize();
                trackPos = Vec2(pos.x + csize.width - 30, 0.0f);
                
                firstLand->setRightIgnore(true);
            }
            else
            {
                firstLand->setContentSize(Size(trackSpace + 60, 180));
                trackPos = Vec2(trackSpace-30, 0.0f);
            }
            
            firstLand->setLand(true);
            
        }
        else
        {
            auto csize = firstLand->getContentSize();
            auto position = firstLand->getPosition();
            trackPos = Vec2(position.x + csize.width, 0);
        }
    }

    
    
//    
//    auto pos = firstLand->getPosition();
//    auto csize = firstLand->getContentSize();
//    
//    int index = 1;
//
//    while (pos.x < 2528 - m_pageStretch)
//    {
//
//        auto nextLand = getNextLand(firstLand);
//
//        if (!nextLand)
//        {
//            pos = firstLand->getPosition();
//            csize = firstLand->getContentSize();
//            
//            firstLand = Stone::create();
//            firstLand->setLand(true);
//            firstLand->setContentSize(Size(300, 180));
//            firstLand->setCollideType(kCollideTypeDirection);
//            firstLand->setCollideEffect(true);
//            firstLand->setPosition(Vec2(pos.x + csize.width - 60, 50.0f));
//            firstLand->setXV(-this->getVelocity());
//            m_gPhysics->addPhysicNode(firstLand);
//            m_dirCollideObjs->addObject(firstLand);
//            this->addChild(firstLand);
//            firstLand->setLocalZOrder(ZORDER_RUNNER);
//            
//            pos = firstLand->getPosition();
//            
//            firstLand->showTips(index);
//        }
//        else
//        {
//            pos = nextLand->getPosition();
//            firstLand = nextLand;
//            
//            firstLand->showTips(index);
//        }
//        
//        index ++;
//    
//    }
}

Runner* CoolRun::getLastPosRunner()
{
    Runner* runner = nullptr;
    for (int i = 0; i < m_runners->count(); ++ i)
    {
        Runner* _r = dynamic_cast<Runner*>(m_runners->getObjectAtIndex(i));
        if (!runner)
        {
            runner = _r;
        }
        else
        {
            auto lastPos = runner->getPosition();
            auto pos = _r->getPosition();
            if (pos.x < lastPos.x)
            {
                runner = _r;
            }
        }
    }
    return runner;
}
Land* CoolRun::getRunnerPosLand(Runner* runner)
{
    auto pos = runner->getPosition();
    Land* land = nullptr;
    for (int i = 0; i < m_dirCollideObjs->count(); ++ i)
    {
        Land* _stone = dynamic_cast<Land*>(m_dirCollideObjs->getObjectAtIndex(i));
        if (_stone->isLand())
        {
            auto rect = PhysicHelp::countPhysicNodeRect(_stone);
            if (rect.origin.x <= pos.x && rect.size.width > pos.x)
            {
                land = _stone;
            }
        }
    }
    return land;
}
Land* CoolRun::getMinPosLand()
{
    Land* minLand = nullptr;
    for (int i = 0; i < m_dirCollideObjs->count(); ++ i)
    {
        Land* _stone = dynamic_cast<Land*>(m_dirCollideObjs->getObjectAtIndex(i));
        if (_stone->isLand())
        {
            if (!minLand)
            {
                minLand = _stone;
            }
            else
            {
                auto minPos = minLand->getPosition();
                auto pos = _stone->getPosition();
                if (pos.x < minPos.x)
                {
                    minLand = _stone;
                }
            }
        }
        
    }
    return minLand;
}

Land* CoolRun::getNextLand(Land* stone)
{
    auto preRect = PhysicHelp::countPhysicNodeRect(stone);
    auto pos = stone->getPosition();
    for (int i = 0; i < m_dirCollideObjs->count(); ++ i)
    {
        Land* _stone = dynamic_cast<Land*>(m_dirCollideObjs->getObjectAtIndex(i));
        if (_stone->isLand() && _stone != stone)
        {
            auto nextRect = PhysicHelp::countPhysicNodeRect(_stone);
            if (preRect.origin.x + preRect.size.width >= nextRect.origin.x && nextRect.origin.x > preRect.origin.x)
            {
                return _stone;
            }
        }
    }
    return nullptr;
}

Land* CoolRun::getLand(const Vec2& pos)
{
    Land* land = nullptr;
    auto arr = __Array::create();
    for (int i = 0; i < m_dirCollideObjs->count(); ++ i)
    {
        Land* _stone = dynamic_cast<Land*>(m_dirCollideObjs->getObjectAtIndex(i));
        if (_stone->isLand())
        {
            auto _pos = _stone->getPosition();
            auto _csize = _stone->getContentSize();
//            auto rect = PhysicHelp::countPhysicNodeRect(_stone);
//            if (rect.origin.x <= pos.x && rect.origin.x + rect.size.width > pos.x)
//            {
//                arr->addObject(_stone);
//            }
            if (pos.x >= _pos.x && pos.x < _pos.x + _csize.width)
            {
                arr->addObject(_stone);
            }
        }
    }
    float max_x = 0;
    for (int i = 0; i < arr->count(); ++ i)
    {
        Land* _stone = dynamic_cast<Land*>(arr->getObjectAtIndex(i));
        auto rect = PhysicHelp::countPhysicNodeRect(_stone);
        if (rect.origin.x + rect.size.width > max_x)
        {
            land = _stone;
            max_x = rect.origin.x + rect.size.width;
        }
    }
    return land;
}

Land* CoolRun::getNextLand(const Vec2& pos, float space)
{
    float min_x = space;
    Land* nextLand = nullptr;
    for (int i = 0; i < m_dirCollideObjs->count(); ++ i)
    {
        Land* _stone = dynamic_cast<Land*>(m_dirCollideObjs->getObjectAtIndex(i));
        if (_stone->isLand())
        {
            auto nextPos = _stone->getPosition();
            if (nextPos.x >= pos.x)
            {
                auto x_def = nextPos.x - pos.x;
                if (x_def <= min_x)
                {
                    nextLand = _stone;
                    min_x = x_def;
                }
            }
        }
    }
    return nextLand;
}


void CoolRun::startFly()
{
    auto v = this->getVelocity();
    this->setVelocity(v+3200);
}
void CoolRun::endFly()
{
    auto v = this->getVelocity();
    this->setVelocity(v-3200);
}


