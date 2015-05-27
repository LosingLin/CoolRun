//
//  SpiderPoison.cpp
//  CoolRun
//
//  Created by ManYou on 14/11/26.
//
//

#include "SpiderPoison.h"
#include "PoisonBullet.h"
#include "Runner.h"
#include "Bullet.h"

SpiderPoison::SpiderPoison()
: Spider()
, b_isAtking(false)
, m_atkDirection(kCRDirectionUp)
{
}
SpiderPoison::~SpiderPoison()
{
}
bool SpiderPoison::init()
{
    if (!Spider::init())
    {
        return false;
    }
    
    m_armature = Armature::create("SpiderPoison");
    m_armature->setScale(0.8f);
    this->addChild(m_armature);
    
    auto csize = m_armature->getContentSize() * 0.8f;
    this->setContentSize(csize);
    
    m_armature->setPosition(Vec2(csize.width / 2, csize.height / 2));
    
    this->setCollideRect(Rect(40, 44, csize.width * 0.8f, csize.height - 50));
    
    this->addRect(Rect(46, 50, 70, 80)); //头部
    this->addRect(Rect(120, 50, 100, 120)); //尾部
    
    this->debugShow();
    
    m_atkAlert = Sprite::createWithSpriteFrameName("spider_poison_alert.png");
    m_atkAlert->setAnchorPoint(Vec2(1, 0.5));
    m_atkAlert->setPosition(Vec2(180, 120));
    this->addChild(m_atkAlert);
    this->setAtkDirection(CRDirection::kCRDirectionUp);
    m_atkAlert->setOpacity(200);
    m_atkAlert->runAction(RepeatForever::create(Blink::create(0.5, 1)));
    
    this->setScore(5);
    
    return true;
}

void SpiderPoison::loadJson(rapidjson::Value& value)
{
    Spider::loadJson(value);
    
    CRDirection dir = kCRDirectionUp;
    
    if (value.HasMember("atk_dir")) {
        dir = (CRDirection)JsonHelp::getInt(value["atk_dir"]);
    }
    this->setAtkDirection(dir);
}

void SpiderPoison::saveData(string* buffer)
{
    Spider::saveData(buffer);
    
    string str = string();
    stringstream ss;
    ss << "\"atk_dir\":";
    ss << this->getAtkDirection();
    ss << ",";
    ss >> str;
    buffer->append(str);
}

void SpiderPoison::setState(SpiderState state)
{
    Spider::setState(state);
    switch (m_state) {
        case kSpiderState_Attack:
            m_armature->getAnimation()->play("attack");
            break;
        case kSpiderState_Stand:
            m_armature->getAnimation()->play("stand");
            break;
        case kSpiderState_Hurted:
            m_armature->getAnimation()->play("hurt");
            break;
        case kSpiderState_Walk:
            m_armature->getAnimation()->play("walk");
            break;
        default:
            break;
    }
    m_armature->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_3(SpiderPoison::movementEvent, this));
    m_armature->getAnimation()->setFrameEventCallFunc(CC_CALLBACK_4(SpiderPoison::frameEvent, this));
}

void SpiderPoison::dead()
{
    Spider::dead();
    this->setState(kSpiderState_Hurted);
    this->setCollideEffect(false);
}

void SpiderPoison::attack()
{
    b_isAtking = true;
    auto v = m_gameController->getVelocity();
    this->setXV(-v);
    
    auto bullet = PoisonBullet::create();
    bullet->setAtkDirection(m_atkDirection);
    auto pos = this->getPosition();
    
    switch (m_atkDirection)
    {
        case kCRDirectionUp:
        {
            bullet->setXV(-v);
            bullet->setYV(600);
            bullet->setPosition(Vec2(pos.x + 120, pos.y + 60));
            m_gameController->addBullet(bullet);
        }
            break;
        case kCRDirectionDown:
        {
            bullet->setXV(-v);
            bullet->setYV(-600);
            bullet->setPosition(Vec2(pos.x + 120, pos.y + 60));
            m_gameController->addBullet(bullet);
        }
            break;
        case kCRDirectionLeft:
        {
            bullet->setXV(-v-600);
            bullet->setPosition(Vec2(pos.x + 120, pos.y + 60));
            m_gameController->addBullet(bullet);
        }
            break;
        case kCRDirectionRight:
        {
            bullet->setXV(v+600);
            bullet->setPosition(Vec2(pos.x + 120, pos.y + 60));
            m_gameController->addBullet(bullet);
        }
            break;
        default:
            break;
    }
    
}

void SpiderPoison::attackDone()
{
    this->setDestoryed(true);
}

void SpiderPoison::setAtkDirection(CRDirection direction)
{
    m_atkDirection = direction;
//    Bone* bellyNormal = m_armature->getBone("belly_normal");
//    Bone* bellyHurted = m_armature->getBone("belly_hurted");
    switch (m_atkDirection)
    {
        case kCRDirectionRight:
        {
            m_atkAlert->setRotation(180);
        }
            break;
        case kCRDirectionUp:
        {
            m_atkAlert->setRotation(90);
        }
            break;
        case kCRDirectionLeft:
        {
            m_atkAlert->setRotation(0);
        }
            break;
        case kCRDirectionDown:
        {
            m_atkAlert->setRotation(-90);
        }
            break;
            
        default:
            break;
    }
    
}

#pragma mark - bone callback
void SpiderPoison::movementEvent(Armature *armature, MovementEventType movementType, const std::string& movementID)
{
    if (MovementEventType::COMPLETE == movementType)
    {
        if("hurt" == movementID)
        {
            this->attack();
            this->setDestoryed(true);
        }
        
    }
}
void SpiderPoison::frameEvent(Bone *bone, const std::string& frameEventName, int originFrameIndex, int currentFrameIndex)
{
}

#pragma mark - collide

void SpiderPoison::trackCollideWithRunner(Runner* _runner)
{
    //Spider::trackCollideWithRunner(_runner);
    
    if (!this->isCollideEffect() || this->isDestoryed())
    {
        return;
    }
    
    //处理与玩家的碰撞
    if (!b_isAtking)
    {
        auto rect1 = PhysicHelp::countPhysicNodeRect(this);
        auto headRect = PhysicHelp::countPhysicNodeRect(this, this->getMultiRect(0));
        auto tailRect = PhysicHelp::countPhysicNodeRect(this, this->getMultiRect(1));
        
        if (_runner->isAtk())
        {
            auto rect2 = PhysicHelp::countPhysicNodeRect(_runner, _runner->getAtkRect());
            
            bool isAtked = CollideTrackHelp::trackCollide(tailRect, rect2);
            bool isAtked02 = CollideTrackHelp::trackCollide(headRect, rect2);
            
            if (isAtked || isAtked02)
            {
                AudioHelp::playBeAttackedEft();
                
                this->dead();
                return;
            }
            
        }
        
        auto rect2 = PhysicHelp::countPhysicNodeRect(_runner);
        
        if (_runner->isCollidedWithTrueBody(headRect))
        {
            if (_runner->isDad() || _runner->isRebornING())
            {
                this->dead();
            }
            else
            {
                m_gameController->dead(_runner);
            }
            return;
        }
        
        CollideDirection dir = _runner->getDirectionWithTrueBody(tailRect);
        
        if (kCollideDirectionUp == dir)
        {
            _runner->rebound();
            
            this->dead();
        }
        else if (kCollideDirectionMiss != dir)
        {
            if (_runner->isDad() || _runner->isRebornING())
            {
                this->dead();
            }
            else
            {
                m_gameController->dead(_runner);
            }
            
//            this->setCollideEffect(false);
        }
    }
    else
    {
//        CCASSERT(m_bullet, "m_bullet can't be null");
//        auto bulletPos = m_bullet->getPosition();
//        auto bulletSize = m_bullet->getContentSize();
//        auto bulletRect = Rect(bulletPos.x - bulletSize.width/2, bulletPos.y - bulletSize.height/2, bulletSize.width, bulletSize.height);
//        
//        auto rect1 = PhysicHelp::countPhysicNodeRect(this, bulletRect);
//        auto rect2 = PhysicHelp::countPhysicNodeRect(_runner);
//        
//        bool isAtked = CollideTrackHelp::trackCollide(rect1, rect2);
//        if (isAtked)
//        {
//            
//            m_gameController->dead(_runner);
//            
//            this->setDestoryed(true);
//            
//            //SHOW_RECT(bulletRect);
//        }
    }
}

void SpiderPoison::trackCollideWithBullet(Bullet* bullet)
{
    auto rect1 = PhysicHelp::countPhysicNodeRect(bullet);
    auto rect2 = PhysicHelp::countPhysicNodeRect(this);
    
    bool isCollided = CollideTrackHelp::trackCollide(rect1, rect2);
    if (isCollided)
    {
        AudioHelp::playBeAttackedEft();
        
        this->dead();
        bullet->setDestoryed(true);
    }
}