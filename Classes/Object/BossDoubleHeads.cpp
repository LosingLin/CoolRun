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
#include "HpBar.h"
#include "ResourceManager.h"

BossDoubleHeads::BossDoubleHeads()
: Boss()
, m_atkSeq(AttackSequence::NONE)
{
}
BossDoubleHeads::~BossDoubleHeads()
{
    this->destoryRes();
}

bool BossDoubleHeads::init()
{
    if (!Boss::init())
    {
        return false;
    }
    m_armature = Armature::create("Boss01");
    auto csize = m_armature->getContentSize();
    //auto csize = Size(433, 342);
    this->setContentSize(csize);
    m_armature->setPosition(Vec2(csize.width/2, csize.height/2));
    this->addChild(m_armature);
    
    
    this->setGravityEffect(true);
    this->setCollideType(kCollideTypeSimple);
    this->setCollideEffect(true);
    
    this->setCollideRect(Rect(60, 56, 320, 260));
    
    this->debugShow();
    
    m_totalHp = 5.0f;
    m_curHp = 5.0f;
    
    this->play(kBDHPlayIndex_Stand);
    
    this->setScore(500);
    
    return true;
}

#pragma mark - Boss

void BossDoubleHeads::initRes()
{
    AudioHelp::preloadBossEft();
    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile(
                    ResourceManager::getInstance()->getPlistRes("BossSpider")
                                                             );
    ArmatureDataManager::getInstance()->addArmatureFileInfo("Boss01.ExportJson");
}
void BossDoubleHeads::destoryRes()
{
    AudioHelp::unloadBossEft();
    
    SpriteFrameCache::getInstance()->removeSpriteFramesFromFile(
                    ResourceManager::getInstance()->getPlistRes("BossSpider")
                                                                );
    ArmatureDataManager::getInstance()->removeArmatureFileInfo("Boss01.ExportJson");
}

void BossDoubleHeads::hurted()
{
    AudioHelp::playBeAttackedEft();
    
    m_curHp --;
    m_hpBar->setCurrentHp(m_curHp);
    
    this->play(kBDHPlayIndex_Hurt);
}
void BossDoubleHeads::dead()
{
    this->play(kBDHPlayIndex_Dead);
//    auto pos = this->getPosition();
//    auto csize = this->getContentSize();
//    pos.x += csize.width/2;
//    pos.y += csize.height/2;
//    m_gameController->showScore(this->getScore(), pos);
}

void BossDoubleHeads::play(int index)
{
    switch (index)
    {
        case kBDHPlayIndex_Walk:
        {
            m_armature->getAnimation()->play("walk");
            
        }
            break;
        case kBDHPlayIndex_Atk_01:
        {
            m_armature->getAnimation()->play("atk_01");
            
        }
            break;
        case kBDHPlayIndex_Atk_02:
        {
            m_armature->getAnimation()->play("atk_02");
        }
            break;
        case kBDHPlayIndex_Atk_03:
        {
            m_armature->getAnimation()->play("atk_03");
        }
            break;
        case kBDHPlayIndex_OpenMouth:
        {
            m_armature->getAnimation()->play("open_mouth");
        }
            break;
        case kBDHPlayIndex_Stand:
        {
            m_armature->getAnimation()->play("stand");
        }
            break;
        case kBDHPlayIndex_Hurt:
        {
            m_armature->getAnimation()->play("hurt");
        }
            break;
        case kBDHPlayIndex_Dead:
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
    
    m_armature->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_3(BossDoubleHeads::movementEvent, this));
    m_armature->getAnimation()->setFrameEventCallFunc(CC_CALLBACK_4(BossDoubleHeads::frameEvent, this));
    
}

Bullet* BossDoubleHeads::createShotBullet(int index)
{
    auto _bul = BossBullet::create();
    return _bul;
}
Spider* BossDoubleHeads::createBornSpider(int index)
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
    return spider;
}


#pragma mark - atk

void BossDoubleHeads::attkSequence(int index)
{
    //log("attkSequence :%d", index);
    this->setAtking(true);
    
    switch (index)
    {
        case 0:
        {
            m_atkSeq = AttackSequence::ATK_01;
            auto delay = DelayTime::create(1.0f);
            auto call01 = CallFunc::create(CC_CALLBACK_0(BossDoubleHeads::play, this, kBDHPlayIndex_Atk_01));
            auto delay01 = DelayTime::create(0.3f);
            auto call = CallFunc::create(CC_CALLBACK_0(BossDoubleHeads::attkSequenceEnd, this));
            this->runAction(Sequence::create(delay, call01, delay01, call, NULL));
        }
            break;
        case 1:
        {
            m_atkSeq = AttackSequence::ATK_02;
            auto delay = DelayTime::create(1.0f);
            auto call01 = CallFunc::create(CC_CALLBACK_0(BossDoubleHeads::play, this, kBDHPlayIndex_Atk_01));
            auto delay01 = DelayTime::create(0.3f);
            auto call02 = CallFunc::create(CC_CALLBACK_0(BossDoubleHeads::play, this, kBDHPlayIndex_Atk_02));
            auto delay02 = DelayTime::create(0.3f);
            auto call = CallFunc::create(CC_CALLBACK_0(BossDoubleHeads::attkSequenceEnd, this));
            this->runAction(Sequence::create(delay, call01, delay01, call02, delay02, call, NULL));

        }
            break;
        case 2:
        {
            m_atkSeq = AttackSequence::ATK_03;
            auto delay = DelayTime::create(1.4f);
            auto call00 = CallFunc::create(CC_CALLBACK_0(BossDoubleHeads::play, this, kBDHPlayIndex_OpenMouth));
            auto delay00 = DelayTime::create(0.3f);
            auto call01 = CallFunc::create(CC_CALLBACK_0(BossDoubleHeads::play, this, kBDHPlayIndex_Atk_01));
            auto delay01 = DelayTime::create(0.3f);
            auto call02 = CallFunc::create(CC_CALLBACK_0(BossDoubleHeads::play, this, kBDHPlayIndex_Atk_02));
            auto delay02 = DelayTime::create(0.3f);
            auto call03 = CallFunc::create(CC_CALLBACK_0(BossDoubleHeads::play, this, kBDHPlayIndex_Atk_03));
            auto delay03 = DelayTime::create(0.3f);
            auto call = CallFunc::create(CC_CALLBACK_0(BossDoubleHeads::attkSequenceEnd, this));
            this->runAction(Sequence::create(delay, call00, delay00, call01, delay01, call02, delay02, call03, delay03, call, NULL));
        }
            break;
        case 3:
        {
            m_atkSeq = AttackSequence::ATK_04;
            auto delay = DelayTime::create(1.0f);
            auto call01 = CallFunc::create(CC_CALLBACK_0(BossDoubleHeads::play, this, kBDHPlayIndex_OpenMouth));
            auto delay01 = DelayTime::create(0.3f);
            auto call = CallFunc::create(CC_CALLBACK_0(BossDoubleHeads::attkSequenceEnd, this));
            this->runAction(Sequence::create(delay, call01, delay01, call, NULL));
        }
            break;
        case 4:
        {
            m_atkSeq = AttackSequence::ATK_05;
            auto delay = DelayTime::create(1.0f);
            auto call01 = CallFunc::create(CC_CALLBACK_0(BossDoubleHeads::play, this, kBDHPlayIndex_OpenMouth));
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
    if(MovementEventType::COMPLETE == movementType)
    {
        if ("dead" == movementID)
        {
            m_gameController->loadNextMission();
            
            auto pos = this->getPosition();
            auto csize = this->getContentSize();
            pos.x += csize.width/2;
            pos.y += csize.height/2;
            m_gameController->showScore(this->getScore(), pos);
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
                this->play(kBDHPlayIndex_Walk);
            }
        }
    }
}

void BossDoubleHeads::frameEvent(Bone *bone, const std::string& frameEventName, int originFrameIndex, int currentFrameIndex)
{
    if ("atk_01_shot" == frameEventName)
    {
        //log("BOSS == atk_01_shot");
        auto pos = this->getPosition();
        pos.x += 280;
        pos.y += 100;
        this->shot(pos, -260);
    }
    else if("atk_01_end" == frameEventName)
    {
        //log("BOSS == atk_01_end");
        this->play(kBDHPlayIndex_Walk);
    }
    else if ("atk_02_shot" == frameEventName)
    {
        auto pos = this->getPosition();
        pos.x += 280;
        pos.y += 180;
        this->shot(pos, -260);
    }
    else if("atk_02_end" == frameEventName)
    {
        
        this->play(kBDHPlayIndex_Walk);
    }
    else if ("atk_03_shot" == frameEventName)
    {
        auto pos = this->getPosition();
        pos.x += 280;
        pos.y += 280;
        this->shot(pos, -260);
    }
    else if("atk_03_end" == frameEventName)
    {
        
        this->play(kBDHPlayIndex_Walk);
    }
    else if ("open_mouth" == frameEventName)
    {
        auto pos = this->getPosition();
        pos.x += -20;
        pos.y += 80;
        this->bornSpider(pos, -80);
    }
    else if("open_mouth_end" == frameEventName)
    {
        
        this->play(kBDHPlayIndex_Walk);
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
            
            this->play(kBDHPlayIndex_Walk);
            
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

