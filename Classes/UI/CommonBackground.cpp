//
//  CommonBackground.cpp
//  CoolRun
//
//  Created by ManYou on 15/5/19.
//
//

#include "CommonBackground.h"
#include "Background.h"
#include "Leaves.h"


CommonBackground::CommonBackground()
: Layer()
, m_awayBG(nullptr)
, m_farBG(nullptr)
, m_midBG(nullptr)
{
    
}
CommonBackground::~CommonBackground()
{
    
}

bool CommonBackground::init()
{
    if (!Layer::init())
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    float scale = 1264.0/1024.0;
    
    auto bg = Sprite::createWithSpriteFrameName("bg.png");
    bg->setScale(scale);
    bg->setAnchorPoint(Vec2::ZERO);
    bg->setOpacity(20);
    this->addChild(bg);
    
    m_awayBG = Background::create("bg05_01.png", "bg05_02.png");
    //m_awayBG->setVelocity(m_velocity*0.2f);
    m_awayBG->setPosition(Vec2(0, 0));
    this->addChild(m_awayBG);
    
    auto cover = Sprite::createWithSpriteFrameName("bg_cover.png");
    cover->setScale(scale);
    cover->setAnchorPoint(Vec2::ZERO);
    cover->setOpacity(40);
    this->addChild(cover);
    
    m_farBG = Background::create("bg03_01.png", "bg03_02.png");
    //m_farBG->setVelocity(m_velocity*0.4f);
    m_farBG->setPosition(Vec2(0, 0));
    this->addChild(m_farBG);
    
    cover = Sprite::createWithSpriteFrameName("bg_cover.png");
    cover->setScale(scale);
    cover->setAnchorPoint(Vec2::ZERO);
    cover->setOpacity(60);
    this->addChild(cover);
    
    m_midBG = Background::create("bg04_01.png", "bg04_02.png");
    //m_midBG->setVelocity(m_velocity*0.8f);
    m_midBG->setPosition(Vec2(0, 0));
    this->addChild(m_midBG);
    
    
    return true;
}