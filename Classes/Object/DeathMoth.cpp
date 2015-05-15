//
//  DeathMoth.cpp
//  CoolRun
//
//  Created by ManYou on 15/3/24.
//
//

#include "DeathMoth.h"
#include "HpBar.h"
#include "Runner.h"
#include "SpiderFly.h"
#include "SpiderSpines.h"
#include "BossBullet.h"
#include "BossBulletNet.h"

DeathMoth::DeathMoth()
: Boss()
, m_atkSeq(AttackSequence::NONE)
, b_isHurting(false)
, m_shotIndex(0)
{
    
}
DeathMoth::~DeathMoth()
{
    this->destoryRes();
}

bool DeathMoth::init()
{
    if (!Boss::init())
    {
        return false;
    }
    
    m_armature = Armature::create("DeathMoth");
    auto csize = m_armature->getContentSize();
    //auto csize = Size(458, 576);
    this->setContentSize(csize);
    m_armature->setPosition(Vec2(csize.width/2, csize.height/2));
    this->addChild(m_armature);
    
    
    this->setGravityEffect(false);
    this->setCollideType(kCollideTypeSimple);
    this->setCollideEffect(true);
    
    this->setCollideRect(Rect(140, 320, 200, 100));
    
    this->debugShow();
    
    m_totalHp = 5.0f;
    m_curHp = 5.0f;
    
    this->play(kDeathMothPlayIndex_Stand);
    
    this->setScore(500);
    
    return true;
}

void DeathMoth::initRes()
{
    AudioHelp::preloadBossEft();
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("DeadthMoth.plist");
    ArmatureDataManager::getInstance()->addArmatureFileInfo("DeathMoth.ExportJson");
}
void DeathMoth::destoryRes()
{
    AudioHelp::unloadBossEft();
    SpriteFrameCache::getInstance()->removeSpriteFramesFromFile("DeadthMoth.plist");
    ArmatureDataManager::getInstance()->removeArmatureFileInfo("DeathMoth.ExportJson");
}

void DeathMoth::attkSequence(int index)
{
    this->setAtking(true);
    switch (index)
    {
        case 0:
        {
            m_atkSeq = AttackSequence::ATK_01;
            auto delay = DelayTime::create(1.0f);
            auto call01 = CallFunc::create(CC_CALLBACK_0(DeathMoth::play, this, kDeathMothPlayIndex_Fly));
            auto moveTo01 = MoveTo::create(0.4, Vec2(700, -240));
            auto call02 = CallFunc::create(CC_CALLBACK_0(DeathMoth::play, this, kDeathMothPlayIndex_OpenMouth));
            auto delay02 = DelayTime::create(0.3f);
            auto call03 = CallFunc::create(CC_CALLBACK_0(DeathMoth::play, this, kDeathMothPlayIndex_Fly));
            auto moveTo02 = MoveTo::create(0.2, Vec2(600, 160));
            auto delay03 = DelayTime::create(0.3f);
            auto call = CallFunc::create(CC_CALLBACK_0(DeathMoth::attkSequenceEnd, this));
            
            auto _vec = Vector<FiniteTimeAction*>();
            _vec.pushBack(delay);
            _vec.pushBack(call01);
            _vec.pushBack(moveTo01);
            _vec.pushBack(call02);
            _vec.pushBack(delay02);
            _vec.pushBack(call03);
            _vec.pushBack(moveTo02);
            _vec.pushBack(delay03);
            _vec.pushBack(call);
            this->runAction(Sequence::create(_vec));
        }
            break;
        case 1:
        {
            m_atkSeq = AttackSequence::ATK_02;
            auto delay = DelayTime::create(1.0f);
            auto call01 = CallFunc::create(CC_CALLBACK_0(DeathMoth::play, this, kDeathMothPlayIndex_Fly));
            auto moveTo01 = MoveTo::create(0.4, Vec2(700, -240));
            auto call02 = CallFunc::create(CC_CALLBACK_0(DeathMoth::play, this, kDeathMothPlayIndex_OpenMouth));
            auto delay02 = DelayTime::create(0.5f);
            auto call04 = CallFunc::create(CC_CALLBACK_0(DeathMoth::play, this, kDeathMothPlayIndex_OpenMouth));
            auto delay04 = DelayTime::create(0.5f);
            auto call05 = CallFunc::create(CC_CALLBACK_0(DeathMoth::play, this, kDeathMothPlayIndex_OpenMouth));
            auto delay05 = DelayTime::create(0.3f);
            auto call03 = CallFunc::create(CC_CALLBACK_0(DeathMoth::play, this, kDeathMothPlayIndex_Fly));
            auto moveTo02 = MoveTo::create(0.2, Vec2(600, 160));
            auto delay03 = DelayTime::create(0.3f);
            auto call = CallFunc::create(CC_CALLBACK_0(DeathMoth::attkSequenceEnd, this));
            
            auto _vec = Vector<FiniteTimeAction*>();
            _vec.pushBack(delay);
            _vec.pushBack(call01);
            _vec.pushBack(moveTo01);
            _vec.pushBack(call02);
            _vec.pushBack(delay02);
            _vec.pushBack(call04);
            _vec.pushBack(delay04);
            _vec.pushBack(call05);
            _vec.pushBack(delay05);
            _vec.pushBack(call03);
            _vec.pushBack(moveTo02);
            _vec.pushBack(delay03);
            _vec.pushBack(call);
            this->runAction(Sequence::create(_vec));
        }
            break;
        case 2:
        {
            m_atkSeq = AttackSequence::ATK_03;
            auto delay = DelayTime::create(1.0f);
            auto call01 = CallFunc::create(CC_CALLBACK_0(DeathMoth::play, this, kDeathMothPlayIndex_Fly));
            auto moveTo01 = MoveTo::create(0.4, Vec2(780, -40));
            auto call02 = CallFunc::create(CC_CALLBACK_0(DeathMoth::play, this, kDeathMothPlayIndex_Atk01));
            auto delay02 = DelayTime::create(0.3f);
            auto call03 = CallFunc::create(CC_CALLBACK_0(DeathMoth::play, this, kDeathMothPlayIndex_Fly));
            auto moveTo02 = MoveTo::create(0.2, Vec2(600, 160));
            auto delay03 = DelayTime::create(0.3f);
            auto call = CallFunc::create(CC_CALLBACK_0(DeathMoth::attkSequenceEnd, this));
            
            auto _vec = Vector<FiniteTimeAction*>();
            _vec.pushBack(delay);
            _vec.pushBack(call01);
            _vec.pushBack(moveTo01);
            _vec.pushBack(call02);
            _vec.pushBack(delay02);
            _vec.pushBack(call03);
            _vec.pushBack(moveTo02);
            _vec.pushBack(delay03);
            _vec.pushBack(call);
            this->runAction(Sequence::create(_vec));
        }
            break;
        case 3:
        {
            m_atkSeq = AttackSequence::ATK_04;
            auto delay = DelayTime::create(1.0f);
            auto call01 = CallFunc::create(CC_CALLBACK_0(DeathMoth::play, this, kDeathMothPlayIndex_Fly));
            auto moveTo01 = MoveTo::create(0.4, Vec2(780, -40));
            auto call02 = CallFunc::create(CC_CALLBACK_0(DeathMoth::play, this, kDeathMothPlayIndex_Atk01));
            auto delay02 = DelayTime::create(0.3f);
            auto moveTo03 = MoveTo::create(0.2, Vec2(700, 0));
            auto call04 = CallFunc::create(CC_CALLBACK_0(DeathMoth::play, this, kDeathMothPlayIndex_OpenMouth));
            auto delay04 = DelayTime::create(0.3f);
            auto call03 = CallFunc::create(CC_CALLBACK_0(DeathMoth::play, this, kDeathMothPlayIndex_Fly));
            auto moveTo02 = MoveTo::create(0.2, Vec2(600, 160));
            auto delay03 = DelayTime::create(0.3f);
            auto call = CallFunc::create(CC_CALLBACK_0(DeathMoth::attkSequenceEnd, this));
            
            auto _vec = Vector<FiniteTimeAction*>();
            _vec.pushBack(delay);
            _vec.pushBack(call01);
            _vec.pushBack(moveTo01);
            _vec.pushBack(call02);
            _vec.pushBack(delay02);
            _vec.pushBack(moveTo03);
            _vec.pushBack(call04);
            _vec.pushBack(delay04);
            _vec.pushBack(call03);
            _vec.pushBack(moveTo02);
            _vec.pushBack(delay03);
            _vec.pushBack(call);
            this->runAction(Sequence::create(_vec));
        }
            break;
        case 4:
        {
            m_atkSeq = AttackSequence::ATK_05;
            
            auto delay = DelayTime::create(1.0f);
            auto call01 = CallFunc::create(CC_CALLBACK_0(DeathMoth::play, this, kDeathMothPlayIndex_Fly));
            auto moveTo01 = MoveTo::create(0.2, Vec2(760, -40));
            auto call02 = CallFunc::create(CC_CALLBACK_0(DeathMoth::play, this, kDeathMothPlayIndex_Atk01));
            auto delay02 = DelayTime::create(0.3f);
            //auto call03 = CallFunc::create(CC_CALLBACK_0(DeathMoth::play, this, kDeathMothPlayIndex_Fly));
            auto moveTo02 = MoveTo::create(0.2, Vec2(600, 220));
            auto call04 = CallFunc::create(CC_CALLBACK_0(DeathMoth::play, this, kDeathMothPlayIndex_Rush));
            auto moveTo03 = MoveTo::create(1.6, Vec2(100, 220));
            auto call05 = CallFunc::create(CC_CALLBACK_0(DeathMoth::play, this, kDeathMothPlayIndex_Fly));
            auto moveTo04 = MoveTo::create(0.2, Vec2(600, 160));
            auto delay03 = DelayTime::create(0.3f);
            auto call = CallFunc::create(CC_CALLBACK_0(DeathMoth::attkSequenceEnd, this));
            
            auto _vec = Vector<FiniteTimeAction*>();
            _vec.pushBack(delay);
            _vec.pushBack(call01);
            _vec.pushBack(moveTo01);
            _vec.pushBack(call02);
            _vec.pushBack(delay02);
            //_vec.pushBack(call03);
            _vec.pushBack(moveTo02);
            _vec.pushBack(call04);
            _vec.pushBack(moveTo03);
            _vec.pushBack(call05);
            _vec.pushBack(moveTo04);
            _vec.pushBack(delay03);
            _vec.pushBack(call);
            this->runAction(Sequence::create(_vec));
        }
            break;
        default:
            break;
    }
}
void DeathMoth::attkSequenceEnd()
{
    this->setAtking(false);
    m_shotIndex = 0;
    if (AttackSequence::ATK_05 == m_atkSeq)
    {
        b_isHurting = false;
        if (m_curHp <= 0)
        {
            //this->setDestoryed(true);
            m_gameController->loadNextMission();
            
            this->addPlayerScore();
        }
    }
}

void DeathMoth::play(int index)
{
    switch (index)
    {
        case kDeathMothPlayIndex_Fly:
        {
            m_armature->getAnimation()->play("fly");
        }
            break;
        case kDeathMothPlayIndex_Stand:
        {
            m_armature->getAnimation()->play("stand");
        }
            break;
        case kDeathMothPlayIndex_OpenMouth:
        {
            m_armature->getAnimation()->play("open_mouth");
        }
            break;
        case kDeathMothPlayIndex_Atk01:
        {
            m_armature->getAnimation()->play("atk01");
        }
            break;
        case kDeathMothPlayIndex_Rush:
        {
            m_armature->getAnimation()->play("rush");
        }
            break;
        case kDeathMothPlayIndex_Hurt:
        {
            m_armature->getAnimation()->play("hurt");
        }
            break;
        case kDeathMothPlayIndex_Dead:
        {
            m_armature->getAnimation()->play("dead");
        }
            break;
            
        default:
            break;
    }
    
    m_armature->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_3(DeathMoth::movementEvent, this));
    m_armature->getAnimation()->setFrameEventCallFunc(CC_CALLBACK_4(DeathMoth::frameEvent, this));
}

void DeathMoth::hurted()
{
    this->stopAllActions();
    auto call01 = CallFunc::create(CC_CALLBACK_0(DeathMoth::play, this, kDeathMothPlayIndex_Hurt));
    //auto delay01 = DelayTime::create(0.3f);
    auto moveTo = MoveTo::create(0.2, Vec2(600, 160));
    auto call = CallFunc::create(CC_CALLBACK_0(DeathMoth::attkSequenceEnd, this));
    
    auto _vec = Vector<FiniteTimeAction*>();
    _vec.pushBack(call01);
    //_vec.pushBack(delay01);
    _vec.pushBack(moveTo);
    _vec.pushBack(call);
    this->runAction(Sequence::create(_vec));
}
void DeathMoth::dead()
{
    this->stopAllActions();
    this->setCollideEffect(false);
    this->setGravityEffect(true);
    auto call01 = CallFunc::create(CC_CALLBACK_0(DeathMoth::play, this, kDeathMothPlayIndex_Dead));
    auto call = CallFunc::create(CC_CALLBACK_0(DeathMoth::attkSequenceEnd, this));
    
    auto _vec = Vector<FiniteTimeAction*>();
    _vec.pushBack(call01);
    _vec.pushBack(call);
    this->runAction(Sequence::create(_vec));
}

Bullet* DeathMoth::createShotBullet(int index)
{
    Bullet* _bul = nullptr;
    if(index == 1)
    {
        _bul = BossBulletNet::create();
    }
    else
    {
        _bul = BossBullet::create();
    }
    return _bul;
}

Spider* DeathMoth::createBornSpider(int index)
{
    Spider* sp = nullptr;
    if(AttackSequence::ATK_03 == m_atkSeq)
    {
        sp = SpiderSpines::create();
    }
    else
    {
        sp = SpiderFly::create();
    }
    
    sp->setState(SpiderState::kSpiderState_Walk);
    return sp;
}


void DeathMoth::movementEvent(Armature *armature, MovementEventType movementType, const std::string& movementID)
{
    
}
void DeathMoth::frameEvent(Bone *bone, const std::string& frameEventName, int originFrameIndex, int currentFrameIndex)
{
    if ("atk01_begin" == frameEventName)
    {
        auto pos = this->getPosition();
        pos.x += -80;
        pos.y += 80;
        this->bornSpider(pos, -180);
    }
    if ("open_mouth_begin" == frameEventName)
    {
        if (AttackSequence::ATK_01 == m_atkSeq)
        {
            auto pos = this->getPosition();
            pos.x += 60;
            pos.y += 320;
            this->shot(pos, -260, 0);
        }
        else if (AttackSequence::ATK_02 == m_atkSeq)
        {
            auto pos = this->getPosition();
            pos.x += 60;
            pos.y += 320;
            this->shot(pos, -260, m_shotIndex);
            
            m_shotIndex ++;
        }
        else if (AttackSequence::ATK_04 == m_atkSeq)
        {
            auto pos = this->getPosition();
            pos.x += 60;
            pos.y += 320;
            this->shot(pos, -260, 0);
        }
    }
    else if ("atk01_end" == frameEventName || "open_mouth_end" == frameEventName || "hurt_end" == frameEventName)
    {
        this->play(kDeathMothPlayIndex_Fly);
    }
}


#pragma mark - update

void DeathMoth::trackCollideWithRunner(Runner* _runner)
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
        if (x_dis <= 500)
        {
            
            this->setXV(0.0f);
            this->setReady(true);
            
            this->play(kDeathMothPlayIndex_Stand);
            
            m_hpBar = HpBar::create(m_totalHp);
            m_gameController->addBossHpBar(m_hpBar);
        }
    }
    if (x_dis <= 500)
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
        //atk_num = 4;
        this->attkSequence(atk_num);
        
    }
    
    if (this->isAtking() && AttackSequence::ATK_05 == m_atkSeq && b_isHurting == false)
    {
        auto crect = PhysicHelp::countPhysicNodeRect(this);
        if (_runner->isAtk())
        {
            auto atkRect = PhysicHelp::countPhysicNodeRect(_runner, _runner->getAtkRect());
            if (CollideTrackHelp::trackCollide(crect, atkRect))
            {
                b_isHurting = true;
                
                AudioHelp::playBeAttackedEft();
                
                m_curHp --;
                m_hpBar->setCurrentHp(m_curHp);
                
                if (m_curHp <= 0 && !this->isDestoryed())
                {
                    this->dead();
                }
                else
                {
                    this->hurted();
                }
                return;
            }
        }
        else
        {
            auto rRect = PhysicHelp::countPhysicNodeRect(_runner);
            if (CollideTrackHelp::trackCollide(crect, rRect))
            {
                m_gameController->dead(_runner);
                return;
            }
        }
    }
}
