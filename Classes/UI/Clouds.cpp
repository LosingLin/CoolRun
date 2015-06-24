//
//  Clouds.cpp
//  CoolRun
//
//  Created by ManYou on 15/5/28.
//
//

#include "Clouds.h"
#include "GlobalDefined.h"
#include "ResourceManager.h"

#define MAX_COUNT_CLOUD 28

Clouds::Clouds()
: Layer()
, m_count(0)
, m_velocity(0.0f)
, m_clouds(nullptr)
{
    
}
Clouds::~Clouds()
{
    CC_SAFE_RELEASE_NULL(m_clouds);
}

bool Clouds::init()
{
    if (!Layer::init())
    {
        return false;
    }
    
    CREATEANDRETAINARRAY(m_clouds);
    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile(
                                                             ResourceManager::getInstance()->getPlistRes("Clouds")
                                                             );
    
    
    return true;
}

void Clouds::onEnter()
{
    Layer::onEnter();
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    for (int i = 0; i < MAX_COUNT_CLOUD/2; ++ i)
    {
        this->buildClouds(origin.x - 60, origin.x + visibleSize.width + 100);
    }
    
    this->schedule(schedule_selector(Clouds::update), 0.5);
    
}
void Clouds::onExit()
{
    this->unschedule(schedule_selector(Clouds::update));
    Layer::onExit();
}


void Clouds::update(float delta)
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    this->buildClouds(visibleSize.width + 200, visibleSize.width + 800);
}

void Clouds::buildClouds(int min_x, int max_x)
{
    if (m_count < MAX_COUNT_CLOUD)
    {
        Size visibleSize = Director::getInstance()->getVisibleSize();
        Vec2 origin = Director::getInstance()->getVisibleOrigin();
        
        int start_max_x = max_x;
        int start_min_x = min_x;
        int start_max_y = visibleSize.height + 80;
        int start_min_y = 200;
        
        int r = 0;
        
        int index = 1 + rand()%6;
        char ca[80] = {'\0'};
        sprintf(ca, "cloud_%02d.png", index);
        auto cloud = Sprite::createWithSpriteFrameName(ca);
        
        auto pos = Vec2(0, 0);
        r = start_min_x + rand()%(start_max_x - start_min_x);
        pos.x = r;
        r = start_min_y + rand()%(start_max_y - start_min_y);
        pos.y = r;
        cloud->setPosition(pos);
        this->addChild(cloud);
        
        auto csize = cloud->getContentSize();
        if (m_velocity == 0)
        {
            m_velocity = 20.0f;
        }
        float time = (origin.x+csize.width+pos.x) / m_velocity;
        int time_inc = rand()%2 - 2;
        time += time_inc;
        
        float scale = (rand()%8 + 12) / 10;
        cloud->setScale(scale);
        
        int opacity = rand() % 105 + 150;
        cloud->setOpacity(opacity);
        
        int color = rand() % 105 + 150;
        cloud->setColor(Color3B(color, color, color));
        
        auto _moveTo = MoveTo::create(time, Vec2(origin.x-csize.width, pos.y));

        auto call = CallFunc::create(CC_CALLBACK_0(Clouds::actionOver, this, cloud));
        
        cloud->runAction(Sequence::create(_moveTo, call, NULL));
        
        m_count ++;
    }
}

void Clouds::actionOver(Sprite* leaf)
{
    leaf->removeFromParentAndCleanup(true);
    m_count--;
}