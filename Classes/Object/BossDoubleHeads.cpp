//
//  BossDoubleHeads.cpp
//  CoolRun
//
//  Created by ManYou on 15/1/15.
//
//

#include "BossDoubleHeads.h"
#include "Runner.h"
#include "BossBullet.h"
#include "SpiderKind.h"
#include "SpiderPoison.h"
#include "SpiderSpines.h"

BossDoubleHeads::BossDoubleHeads()
: Boss()
, m_atkSeq(AttackSequence::NONE)
{
}
BossDoubleHeads::~BossDoubleHeads()
{
}

bool BossDoubleHeads::init()
{
    if (!Boss::init())
    {
        return false;
    }
    
    m_armature = Armature::create("Boss01");
    auto csize = m_armature->getContentSize();
    this->setContentSize(csize);
    m_armature->setPosition(Vec2(csize.width/2, csize.height/2));
    this->addChild(m_armature);
    
    m_armature->getAnimation()->play("walk");
    
    this->setGravityEffect(true);
    this->setCollideType(kCollideTypeSimple);
    this->setCollideEffect(true);
    
    this->setCollideRect(Rect(60, 56, 320, 260));
    
    this->debugShow();
    
    return true;
}

#pragma mark - hurted

void BossDoubleHeads::hurted()
{
    this->setColor(Color3B::RED);
}
void BossDoubleHeads::dead()
{
    
}

#pragma mark -  atk

void BossDoubleHeads::atk(int index)
{
    switch (index)
    {
        case 1:
        {
            m_armature->getAnimation()->play("atk_01");
            
        }
            break;
        case 2:
        {
            m_armature->getAnimation()->play("atk_02");
        }
            break;
        case 3:
        {
            m_armature->getAnimation()->play("atk_03");
        }
            break;
        case 4:
        {
            m_armature->getAnimation()->play("open_mouth");
        }
            break;
        default:
        {
            m_armature->getAnimation()->play("walk");
        }
            break;
    }
    
    m_armature->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_3(BossDoubleHeads::movementEvent, this));
    m_armature->getAnimation()->setFrameEventCallFunc(CC_CALLBACK_4(BossDoubleHeads::frameEvent, this));
}

void BossDoubleHeads::shot(const Vec2& pos)
{
    auto _bullet = BossBullet::create();
    _bullet->setPosition(pos);
    auto v = m_gameController->getVelocity();
    _bullet->setXV(-v-260);
    m_gameController->addBullet(_bullet);
}

void BossDoubleHeads::bornSpider(const Vec2& pos)
{
    Spider* spider = nullptr;
    if (AttackSequence::ATK_03 == m_atkSeq)
    {
        spider = SpiderKind::create();
        
    }
    else if (AttackSequence::ATK_04 == m_atkSeq)
    {
        int r = rand()%2;
        if (0 == r)
        {
            spider = SpiderKind::create();
        }
        else
        {
            spider = SpiderSpines::create();
        }
    }
    else if (AttackSequence::ATK_05 == m_atkSeq)
    {
        spider = SpiderPoison::create();
        auto spiderPoison = dynamic_cast<SpiderPoison*>(spider);
        spiderPoison->setAtkDirection(kCRDirectionRight);
    }
    spider->setCollideEffect(true);
    spider->setGravityEffect(true);
    spider->setState(SpiderState::kSpiderState_Walk);
    spider->setPosition(pos);
    auto v = m_gameController->getVelocity();
    spider->setXV(-v-80);
    m_gameController->addSpider(spider);
    
}

void BossDoubleHeads::attkSequence(int index)
{
    log("attkSequence :%d", index);
    this->setAtking(true);
    switch (index)
    {
        case 0:
        {
            m_atkSeq = AttackSequence::ATK_01;
            auto delay = DelayTime::create(1.0f);
            auto call01 = CallFunc::create(CC_CALLBACK_0(BossDoubleHeads::atk, this, 1));
            auto delay01 = DelayTime::create(0.3f);
            auto call = CallFunc::create(CC_CALLBACK_0(BossDoubleHeads::attkSequenceEnd, this));
            this->runAction(Sequence::create(delay, call01, delay01, call, NULL));
        }
            break;
        case 1:
        {
            m_atkSeq = AttackSequence::ATK_02;
            auto delay = DelayTime::create(1.0f);
            auto call01 = CallFunc::create(CC_CALLBACK_0(BossDoubleHeads::atk, this, 1));
            auto delay01 = DelayTime::create(0.3f);
            auto call02 = CallFunc::create(CC_CALLBACK_0(BossDoubleHeads::atk, this, 2));
            auto delay02 = DelayTime::create(0.3f);
            auto call = CallFunc::create(CC_CALLBACK_0(BossDoubleHeads::attkSequenceEnd, this));
            this->runAction(Sequence::create(delay, call01, delay01, call02, delay02, call, NULL));

        }
            break;
        case 2:
        {
            m_atkSeq = AttackSequence::ATK_03;
            auto delay = DelayTime::create(1.4f);
            auto call00 = CallFunc::create(CC_CALLBACK_0(BossDoubleHeads::atk, this, 4));
            auto delay00 = DelayTime::create(0.3f);
            auto call01 = CallFunc::create(CC_CALLBACK_0(BossDoubleHeads::atk, this, 1));
            auto delay01 = DelayTime::create(0.3f);
            auto call02 = CallFunc::create(CC_CALLBACK_0(BossDoubleHeads::atk, this, 2));
            auto delay02 = DelayTime::create(0.3f);
            auto call03 = CallFunc::create(CC_CALLBACK_0(BossDoubleHeads::atk, this, 3));
            auto delay03 = DelayTime::create(0.3f);
            auto call = CallFunc::create(CC_CALLBACK_0(BossDoubleHeads::attkSequenceEnd, this));
            this->runAction(Sequence::create(delay, call00, delay00, call01, delay01, call02, delay02, call03, delay03, call, NULL));
        }
            break;
        case 3:
        {
            m_atkSeq = AttackSequence::ATK_04;
            auto delay = DelayTime::create(1.0f);
            auto call01 = CallFunc::create(CC_CALLBACK_0(BossDoubleHeads::atk, this, 4));
            auto delay01 = DelayTime::create(0.3f);
            auto call = CallFunc::create(CC_CALLBACK_0(BossDoubleHeads::attkSequenceEnd, this));
            this->runAction(Sequence::create(delay, call01, delay01, call, NULL));
        }
            break;
        case 4:
        {
            m_atkSeq = AttackSequence::ATK_05;
            auto delay = DelayTime::create(1.0f);
            auto call01 = CallFunc::create(CC_CALLBACK_0(BossDoubleHeads::atk, this, 4));
            auto delay01 = DelayTime::create(2.3f);
            auto call = CallFunc::create(CC_CALLBACK_0(BossDoubleHeads::attkSequenceEnd, this));
            this->runAction(Sequence::create(delay, call01, delay01, call, NULL));
        }
            break;
        default:
            break;
    }
}

void BossDoubleHeads::attkSequenceEnd()
{
    this->setAtking(false);
}

void BossDoubleHeads::movementEvent(Armature *armature, MovementEventType movementType, const std::string& movementID)
{
    
}
void BossDoubleHeads::frameEvent(Bone *bone, const std::string& frameEventName, int originFrameIndex, int currentFrameIndex)
{
    if ("atk_01_shot" == frameEventName)
    {
        log("BOSS == atk_01_shot");
        auto pos = this->getPosition();
        pos.x += 280;
        pos.y += 100;
        this->shot(pos);
    }
    else if("atk_01_end" == frameEventName)
    {
        log("BOSS == atk_01_end");
        
        this->atk(-1);
    }
    else if ("atk_02_shot" == frameEventName)
    {
        auto pos = this->getPosition();
        pos.x += 280;
        pos.y += 180;
        this->shot(pos);
    }
    else if("atk_02_end" == frameEventName)
    {
        
        this->atk(-1);
    }
    else if ("atk_03_shot" == frameEventName)
    {
        auto pos = this->getPosition();
        pos.x += 280;
        pos.y += 280;
        this->shot(pos);
    }
    else if("atk_03_end" == frameEventName)
    {
        
        this->atk(-1);
    }
    else if ("open_mouth" == frameEventName)
    {
        auto pos = this->getPosition();
        pos.x += -20;
        pos.y += 80;
        this->bornSpider(pos);
    }
    else if("open_mouth_end" == frameEventName)
    {
        
        this->atk(-1);
    }
}

#pragma mark - update

void BossDoubleHeads::trackCollideWithRunner(Runner* _runner)
{
    auto rect1 = PhysicHelp::countPhysicNodeRect(this);
    auto rect2 = PhysicHelp::countPhysicNodeRect(_runner);
    
    auto pos1 = Vec2(rect1.origin.x + rect1.size.width/2, rect1.origin.y + rect1.size.height/2);
    auto pos2 = Vec2(rect2.origin.x + rect2.size.width/2, rect2.origin.y + rect2.size.height/2);
    
    auto x_dis = pos1.x - pos2.x;
    //auto y_dis = pos1.y - pos2.y;
    
    if (!this->isReady())
    {
//        Size visibleSize = Director::getInstance()->getVisibleSize();
//        Vec2 origin = Director::getInstance()->getVisibleOrigin();
//        
//        auto csize = this->getContentSize();
//        
//        auto dis = origin.x + visibleSize.width - csize.width;
//        
//        auto pos = this->getPosition();
        if (x_dis <= 600)
        {
            this->setXV(0.0f);
            this->setReady(true);
        }
    }
    if (x_dis <= 600)
    {
        auto pos = this->getPosition();
        pos.x += 1;
        this->setPosition(pos);
    }
    
    if (this->isReady() && !this->isAtking())
    {
        m_atkIndex ++;
        
        int atk_num = 0;
//        if (m_atkIndex % 4 == 0)
//        {
//            atk_num = 4;
//        }
//        else
//        {
//            atk_num = rand()%4;
//        }
        if (m_atkIndex <= 5)
        {
            atk_num = rand() % 4;
        }
        else
        {
            atk_num = rand() % 5;
        }
        this->attkSequence(atk_num);
    }
}

void BossDoubleHeads::trackCollideWithBullet(Bullet* bullet)
{
    auto rect1 = PhysicHelp::countPhysicNodeRect(this);
    auto rect2 = PhysicHelp::countPhysicNodeRect(bullet);
    
    auto isCollide = CollideTrackHelp::trackCollide(rect1, rect2);
    if (isCollide)
    {
        this->hurted();
        bullet->setDestoryed(true);
    }
}

