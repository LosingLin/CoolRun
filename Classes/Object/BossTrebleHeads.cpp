//
//  BossTrebleHeads.cpp
//  CoolRun
//
//  Created by ManYou on 15/3/16.
//
//

#include "BossTrebleHeads.h"
#include "Runner.h"
#include "BossBullet.h"
#include "SpiderKind.h"
#include "SpiderPoison.h"
#include "SpiderSpines.h"
#include "HpBar.h"

BossTrebleHeads::BossTrebleHeads()
: Boss()
, m_atkSeq(AttackSequence::NONE)
{
}
BossTrebleHeads::~BossTrebleHeads()
{
    this->destoryRes();
}

bool BossTrebleHeads::init()
{
    if (!Boss::init())
    {
        return false;
    }
    
    m_armature = Armature::create("Boss02");
    auto csize = m_armature->getContentSize();
    this->setContentSize(csize);
    m_armature->setPosition(Vec2(csize.width/2, csize.height/2));
    this->addChild(m_armature);
    
    this->setGravityEffect(true);
    this->setCollideType(kCollideTypeSimple);
    this->setCollideEffect(true);
    
    this->setCollideRect(Rect(60, 56, 320, 260));
    
    this->debugShow();
    
    m_totalHp = 8.0f;
    m_curHp = 8.0f;
    
    this->play(kBTHPlayIndex_Stand);
    
    this->setScore(1000);
    
    return true;
}

#pragma mark - Boss

void BossTrebleHeads::initRes()
{
    AudioHelp::preloadBossEft();
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("BossSpider.plist");
    ArmatureDataManager::getInstance()->addArmatureFileInfo("Boss02.ExportJson");
}
void BossTrebleHeads::destoryRes()
{
    AudioHelp::unloadBossEft();
    SpriteFrameCache::getInstance()->removeSpriteFramesFromFile("BossSpider.plist");
    ArmatureDataManager::getInstance()->removeArmatureFileInfo("Boss02.ExportJson");
}

void BossTrebleHeads::hurted()
{
    AudioHelp::playBeAttackedEft();
    
    m_curHp --;
    m_hpBar->setCurrentHp(m_curHp);
    
    this->play(kBTHPlayIndex_Hurt);
}
void BossTrebleHeads::dead()
{
    this->play(kBTHPlayIndex_Dead);
}

void BossTrebleHeads::play(int index)
{
    switch (index)
    {
        case kBTHPlayIndex_Walk:
        {
            m_armature->getAnimation()->play("walk");
            
        }
            break;
        case kBTHPlayIndex_Atk_01:
        {
            m_armature->getAnimation()->play("atk_01");
            
        }
            break;
        case kBTHPlayIndex_Atk_02:
        {
            m_armature->getAnimation()->play("atk_02");
        }
            break;
        case kBTHPlayIndex_Atk_03:
        {
            m_armature->getAnimation()->play("atk_03");
        }
            break;
        case kBTHPlayIndex_OpenMouth:
        {
            m_armature->getAnimation()->play("open_mouth");
        }
            break;
        case kBTHPlayIndex_Stand:
        {
            m_armature->getAnimation()->play("stand");
        }
            break;
        case kBTHPlayIndex_Hurt:
        {
            m_armature->getAnimation()->play("hurt");
        }
            break;
        case kBTHPlayIndex_Dead:
        {
            m_armature->getAnimation()->play("dead");
        }
            break;
        default:
        {
            m_armature->getAnimation()->play("walk");
        }
            break;
    }
    
    m_armature->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_3(BossTrebleHeads::movementEvent, this));
    m_armature->getAnimation()->setFrameEventCallFunc(CC_CALLBACK_4(BossTrebleHeads::frameEvent, this));
    
}

Bullet* BossTrebleHeads::createShotBullet(int index)
{
    auto _bul = BossBullet::create();
    return _bul;
}
Spider* BossTrebleHeads::createBornSpider(int index)
{
    Spider* spider = nullptr;
    if (AttackSequence::ATK_04 == m_atkSeq)
    {
        spider = SpiderKind::create();
        
    }
    else if (AttackSequence::ATK_06 == m_atkSeq)
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
    else if (AttackSequence::ATK_07 == m_atkSeq)
    {
        spider = SpiderPoison::create();
        auto spiderPoison = dynamic_cast<SpiderPoison*>(spider);
        spiderPoison->setAtkDirection(kCRDirectionRight);
    }
    return spider;
}


#pragma mark - atk

void BossTrebleHeads::attkSequence(int index)
{
    log("attkSequence :%d", index);
    this->setAtking(true);
    switch (index)
    {
        case 0:
        {
            m_atkSeq = AttackSequence::ATK_01;
            auto delay = DelayTime::create(1.0f);
            auto call01 = CallFunc::create(CC_CALLBACK_0(BossTrebleHeads::play, this, kBTHPlayIndex_Atk_01));
            auto delay01 = DelayTime::create(0.3f);
            auto call = CallFunc::create(CC_CALLBACK_0(BossTrebleHeads::attkSequenceEnd, this));
            this->runAction(Sequence::create(delay, call01, delay01, call, NULL));
        }
            break;
        case 1:
        {
            m_atkSeq = AttackSequence::ATK_02;
            auto delay = DelayTime::create(1.0f);
            auto call01 = CallFunc::create(CC_CALLBACK_0(BossTrebleHeads::play, this, kBTHPlayIndex_Atk_02));
            auto delay01 = DelayTime::create(0.3f);
            auto call = CallFunc::create(CC_CALLBACK_0(BossTrebleHeads::attkSequenceEnd, this));
            this->runAction(Sequence::create(delay, call01, delay01, call, NULL));
            
        }
            break;
        case 2:
        {
            m_atkSeq = AttackSequence::ATK_03;
            auto delay = DelayTime::create(1.0f);
            auto call00 = CallFunc::create(CC_CALLBACK_0(BossTrebleHeads::jump, this, 560.0f));
            auto delay00 = DelayTime::create(0.1f);
            auto call001 = CallFunc::create(CC_CALLBACK_0(BossTrebleHeads::jumpEnd, this));
            auto call01 = CallFunc::create(CC_CALLBACK_0(BossTrebleHeads::play, this, kBTHPlayIndex_Atk_03));
            auto delay01 = DelayTime::create(0.3f);
            auto call = CallFunc::create(CC_CALLBACK_0(BossTrebleHeads::attkSequenceEnd, this));
            this->runAction(Sequence::create(delay, call00, delay00, call001, call01, delay01, call, NULL));
            
        }
            break;
        case 3:
        {
            m_atkSeq = AttackSequence::ATK_04;
            auto delay = DelayTime::create(1.4f);
            auto call00 = CallFunc::create(CC_CALLBACK_0(BossTrebleHeads::play, this, kBTHPlayIndex_OpenMouth));
            auto delay00 = DelayTime::create(0.3f);
            auto call01 = CallFunc::create(CC_CALLBACK_0(BossTrebleHeads::play, this, kBTHPlayIndex_Atk_01));
            auto delay01 = DelayTime::create(0.3f);
            auto call02 = CallFunc::create(CC_CALLBACK_0(BossTrebleHeads::play, this, kBTHPlayIndex_Atk_02));
            auto delay02 = DelayTime::create(0.3f);
            auto call = CallFunc::create(CC_CALLBACK_0(BossTrebleHeads::attkSequenceEnd, this));
            this->runAction(Sequence::create(delay, call00, delay00, call01, delay01, call02, delay02, call, NULL));
        }
            break;
        case 4:
        {
            m_atkSeq = AttackSequence::ATK_05;
            auto delay = DelayTime::create(1.0f);
            auto call00 = CallFunc::create(CC_CALLBACK_0(BossTrebleHeads::jump, this, 560.0f));
            auto delay00 = DelayTime::create(0.1f);
            auto call001 = CallFunc::create(CC_CALLBACK_0(BossTrebleHeads::jumpEnd, this));
            auto call01 = CallFunc::create(CC_CALLBACK_0(BossTrebleHeads::play, this, kBTHPlayIndex_Atk_03));
            auto delay01 = DelayTime::create(0.3f);
            auto call02 = CallFunc::create(CC_CALLBACK_0(BossTrebleHeads::jump, this, 660.0f));
            auto delay02 = DelayTime::create(0.1f);
            auto call002 = CallFunc::create(CC_CALLBACK_0(BossTrebleHeads::jumpEnd, this));
            auto call03 = CallFunc::create(CC_CALLBACK_0(BossTrebleHeads::play, this, kBTHPlayIndex_Atk_03));
            auto delay03 = DelayTime::create(0.3f);
            auto call = CallFunc::create(CC_CALLBACK_0(BossTrebleHeads::attkSequenceEnd, this));
            this->runAction(Sequence::create(delay, call00, delay00, call001, call01, delay01, call02, delay02, call002, call03, delay03, call, NULL));
            
        }
            break;
        case 5:
        {
            m_atkSeq = AttackSequence::ATK_06;
            auto delay = DelayTime::create(1.0f);
            auto call01 = CallFunc::create(CC_CALLBACK_0(BossTrebleHeads::play, this, kBTHPlayIndex_OpenMouth));
            auto delay01 = DelayTime::create(0.3f);
            auto call = CallFunc::create(CC_CALLBACK_0(BossTrebleHeads::attkSequenceEnd, this));
            this->runAction(Sequence::create(delay, call01, delay01, call, NULL));
        }
            break;
        case 6:
        {
            m_atkSeq = AttackSequence::ATK_07;
            auto delay = DelayTime::create(1.0f);
            auto call01 = CallFunc::create(CC_CALLBACK_0(BossTrebleHeads::play, this, kBTHPlayIndex_OpenMouth));
            auto delay01 = DelayTime::create(2.3f);
            auto call = CallFunc::create(CC_CALLBACK_0(BossTrebleHeads::attkSequenceEnd, this));
            this->runAction(Sequence::create(delay, call01, delay01, call, NULL));
        }
            break;
        default:
            break;
    }
}

void BossTrebleHeads::attkSequenceEnd()
{
    this->setAtking(false);
}

void BossTrebleHeads::jump(float yv)
{
    this->play(kBTHPlayIndex_Stand);
    this->setYV(yv);
}
void BossTrebleHeads::jumpEnd()
{
    this->play(kBTHPlayIndex_Walk);
}

void BossTrebleHeads::movementEvent(Armature *armature, MovementEventType movementType, const std::string& movementID)
{
    if(MovementEventType::COMPLETE == movementType)
    {
        if ("dead" == movementID)
        {
            m_gameController->loadNextMission();
            
            this->addPlayerScore();
            this->setDestoryed(true);
        }
        else if ("hurt" == movementID)
        {
            if (m_curHp <=0 && !this->isDestoryed())
            {
                this->dead();
            }
            else
            {
                this->play(kBTHPlayIndex_Walk);
            }
        }
    }
}

void BossTrebleHeads::frameEvent(Bone *bone, const std::string& frameEventName, int originFrameIndex, int currentFrameIndex)
{
    if ("atk_03_shot01" == frameEventName || "atk_02_shot01" == frameEventName) //上面子弹发射
    {
        auto pos = this->getPosition();
        pos.x += 280;
        pos.y += 320;
        this->shot(pos, -260);
        
    }
    else if ("atk_01_shot01" == frameEventName || "atk_02_shot02" == frameEventName)  //中间子弹发射
    {
        auto pos = this->getPosition();
        pos.x += 280;
        pos.y += 190;
        this->shot(pos, -260);
    }
    else if ("atk_01_shot02" == frameEventName || "atk_03_shot02" == frameEventName) //下面子弹发射
    {
        auto pos = this->getPosition();
        pos.x += 280;
        pos.y += 60;
        this->shot(pos, -260);
    }
    else if ("open_mouth" == frameEventName)
    {
        auto pos = this->getPosition();
        pos.x += -20;
        pos.y += 80;
        this->bornSpider(pos, -80);
    }
    else if("atk_01_end01" == frameEventName || "atk_01_end02" == frameEventName ||
            "atk_02_end01" == frameEventName || "atk_02_end02" == frameEventName ||
            "atk_03_end01" == frameEventName || "atk_03_end02" == frameEventName ||
            "open_mouth_end" == frameEventName)
    {
        this->play(kBTHPlayIndex_Walk);
    }
}

#pragma mark - update

void BossTrebleHeads::trackCollideWithRunner(Runner* _runner)
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
            this->play(kBTHPlayIndex_Walk);
            
            m_hpBar = HpBar::create(m_totalHp);
            m_gameController->addBossHpBar(m_hpBar);
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
        if (m_atkIndex <= 7)
        {
            atk_num = rand() % 6;
        }
        else
        {
            atk_num = rand() % 7;
        }
        //atk_num = 1;
        this->attkSequence(atk_num);
    }
}

void BossTrebleHeads::trackCollideWithBullet(Bullet* bullet)
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
