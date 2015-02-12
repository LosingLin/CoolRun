//
//  Stone.cpp
//  CoolRun
//
//  Created by ManYou on 14-8-8.
//
//

#include "Stone.h"
#include "Base.h"
#include "CoolRunScene.h"


Stone::Stone()
: Land()
, m_left(nullptr)
, m_right(nullptr)
, m_mids(nullptr)
{
}
Stone::~Stone()
{
    CC_SAFE_RELEASE_NULL(m_mids);
}
bool Stone::init()
{
    if (!Land::init()) {
        return false;
    }
    
    CREATEANDRETAINARRAY(m_mids);
    
    
//    auto sp = Sprite::create("land.png");
//    auto csize = sp->getContentSize();
//    sp->setPosition(Vec2(csize.width/2, csize.height/2));
//    this->addChild(sp);
//    
//    this->setContentSize(csize);
//    
//    this->setCollideRect(Rect(0, 0, csize.width, csize.height));
//    
//    this->debugShow();
    
    this->setLocalZOrder(ZORDER_STONE);
//    this->setLand(true);
    
    return true;
}

void Stone::onEnter()
{
    Land::onEnter();
    
}
void Stone::onExit()
{
    Land::onExit();
}

void Stone::setLand(bool flag)
{
    Land::setLand(flag);
    
//    if (this->isLand())
//    {
//        if (m_left)
//        {
//            m_left->setColor(Color3B::GREEN);
//        }
//    }

}

void Stone::setLeftIgnore(bool flag)
{
    Land::setLeftIgnore(flag);
    if (this->isLeftIgnore())
    {
        if (m_left)
        {
            m_left->setColor(Color3B::GREEN);
        }
    }
}
void Stone::setRightIgnore(bool flag)
{
    Land::setRightIgnore(flag);
    
    if (this->isRightIgnore())
    {
        if (m_right)
        {
            m_right->setColor(Color3B::GREEN);
        }
    }
}

void Stone::setContentSize(const Size& _size)
{
    PhysicNode::setContentSize(_size);
    
    //this->buildStoneWithScale("stone_left.png", 85, "stone_mid.png", 156, "stone_right.png", 85);
    //this->setCollideRect(Rect(40, 0, _size.width - 80, _size.height-64));
    
    this->buildStoneWithShare("wood01_left.png", 32, "wood01_mid.png", 32, "wood01_right.png", 82);
    this->setCollideRect(Rect(30, 0, _size.width - 60, _size.height/2 - 40));
    
    //this->buildStoneWithShare("wood02.png", 196);
    //this->setCollideRect(Rect(30, 0, _size.width - 60, _size.height/2 - 40));
    
    PhysicNode::setContentSize(Size(_size.width-30, _size.height));
    
    this->debugShow();
    
}

#pragma mark - build stone

void Stone::clearStone()
{
    if (m_left)
    {
        m_left->removeFromParentAndCleanup(true);
    }
    if (m_right)
    {
        m_right->removeFromParentAndCleanup(true);
    }
    
    for (int i = 0; i < m_mids->count(); ++ i)
    {
        auto sp = dynamic_cast<Sprite*>(m_mids->getObjectAtIndex(i));
        sp->removeFromParentAndCleanup(true);
    }
    m_mids->removeAllObjects();
}

void Stone::buildStoneBase(const string& leftFrameName, float leftSize, const string& midFrameName, float midSize, const string& rightFrameName, float rightSize)
{
    auto _size = this->getContentSize();
    
    //CCASSERT(_size.width >= leftSize+rightSize, "_size is too short");
    
    this->clearStone();

    m_left = Sprite::createWithSpriteFrameName(leftFrameName);
    m_left->setAnchorPoint(Vec2(0, 0));
    m_left->setPosition(Vec2::ZERO);
    this->addChild(m_left);
    

    m_right = Sprite::createWithSpriteFrameName(rightFrameName);
    m_right->setAnchorPoint(Vec2(1, 0));
    m_right->setPosition(Vec2(_size.width, 0));
    this->addChild(m_right);
    
    
}
void Stone::buildStoneWithScale(const string& leftFrameName, float leftSize, const string& midFrameName, float midSize, const string& rightFrameName, float rightSize)
{
    this->buildStoneBase(leftFrameName, leftSize, midFrameName, midSize, rightFrameName, rightSize);
    
    auto _size = this->getContentSize();
    auto length = _size.width - (leftSize+rightSize);
    auto index = 0;
    auto scaleSize = midSize*3/2;
    while (length > scaleSize)
    {
        auto sp = Sprite::createWithSpriteFrameName(midFrameName);
        sp->setAnchorPoint(Vec2::ZERO);
        sp->setPosition(Vec2(leftSize + index*midSize, 0));
        this->addChild(sp);
        m_mids->addObject(sp);
        ++ index;
        length -= midSize;
    }
    
    auto sp = Sprite::createWithSpriteFrameName(midFrameName);
    sp->setAnchorPoint(Vec2::ZERO);
    sp->setPosition(Vec2(leftSize + index*midSize, 0));
    sp->setScaleX(length/midSize);
    this->addChild(sp);
    m_mids->addObject(sp);
}
void Stone::buildStoneWithShare(const string& leftFrameName, float leftSize, const string& midFrameName, float midSize, const string& rightFrameName, float rightSize)
{
    this->buildStoneBase(leftFrameName, leftSize, midFrameName, midSize, rightFrameName, rightSize);
    
    auto _size = this->getContentSize();
    auto length = _size.width - (leftSize+rightSize);
    auto index = 0;
    int num = (length / midSize);
    //log("num : %d float : %f", num, length / midSize);
    float gap = (length / num - midSize)/2;
    while (num > 0)
    {
        auto sp = Sprite::createWithSpriteFrameName(midFrameName);
        sp->setAnchorPoint(Vec2::ZERO);
        sp->setPosition(Vec2(leftSize + gap + index*(gap*2+midSize), 0));
        this->addChild(sp);
        m_mids->addObject(sp);
        ++ index;
        -- num;
    }
}

void Stone::buildStoneWithShare(const string& frameName, float size)
{
    this->clearStone();
    
    auto _size = this->getContentSize();
    
    auto index = 0;
    int num = (_size.width / size);
    float gap = (_size.width / num - size)/2;
    while (num > 0)
    {
        auto sp = Sprite::createWithSpriteFrameName(frameName);
        sp->setAnchorPoint(Vec2::ZERO);
        sp->setPosition(Vec2(gap + index*(gap*2+size), 0));
        this->addChild(sp);
        m_mids->addObject(sp);
        ++ index;
        -- num;
    }
}


Stone* Stone::create(rapidjson::Value& _value)
{
    auto _stone = Stone::create();
    _stone->loadJson(_value);
    _stone->debugShow();
    return _stone;
}