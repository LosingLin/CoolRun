//
//  Leaves.cpp
//  CoolRun
//
//  Created by ManYou on 15/4/22.
//
//

#include "Leaves.h"


Leaves::Leaves()
: Layer()
, m_count(0)
, m_velocity(0.0f)
{
    
}
Leaves::~Leaves()
{
    
}

bool Leaves::init()
{
    if (!Layer::init())
    {
        return false;
    }
    
    
    return true;
}

void Leaves::onEnter()
{
    Layer::onEnter();
    
    this->schedule(schedule_selector(Leaves::update), 0.1);
    
    
}
void Leaves::onExit()
{
    //this->unschedule(schedule_selector(Leaves::update));
    
    Layer::onExit();
}


void Leaves::update(float delta)
{
    int max_count = 36;
    if (m_count < max_count)
    {
        Size visibleSize = Director::getInstance()->getVisibleSize();
        Vec2 origin = Director::getInstance()->getVisibleOrigin();
        
        int start_max_x = visibleSize.width + 100;
        int start_min_x = 200;
        int start_max_y = visibleSize.height + 50;
        int start_min_y = 500;
        
        int dis_max_x = 700;
        int dis_min_x = 400;
        int dis_max_y = 700;
        int dis_min_y = 200;
        
        int fall_time_max = 4;
        int fall_time_min = 1;
        
        int rotation_max = 360;
        int rotation_min = 30;
        
        int scale_max = 20;
        int scale_min = 4;
        
        int r = 0;
        
        int index = 1 + rand()%10;
        char ca[80] = {'\0'};
        sprintf(ca, "Leaves_%02d.png", index);
        auto leaf = Sprite::createWithSpriteFrameName(ca);
        
        auto pos = Vec2(0, 0);
        r = start_min_x + rand()%(start_max_x - start_min_x);
        pos.x = r;
        r = start_min_y + rand()%(start_max_y - start_min_y);
        pos.y = r;
        leaf->setPosition(pos);
        this->addChild(leaf);
        
        int move_x = dis_min_x + rand()%(dis_max_x - dis_min_x);
        int move_y = dis_min_y + rand()%(dis_max_y - dis_min_y);
        
        int time = fall_time_min + rand()%(fall_time_max - fall_time_min);
        
        
        int angle = rotation_min + rand()%(rotation_max - rotation_min);
        float scale = (scale_min + rand()%(scale_max - scale_min))/10;
        
        auto _moveTo = MoveTo::create(time, Vec2(pos.x-(move_x + m_velocity*time), pos.y-move_y));
        auto _rotation = RotateTo::create(time, angle);
        auto _scaleTo = ScaleTo::create(time, scale);
        auto _fadeOut = FadeOut::create(time);
        
        //auto fadeIn = FadeIn::create(0.1);
        auto _spawn = Spawn::create(_moveTo, _rotation, _scaleTo, _fadeOut, NULL);
        auto call = CallFunc::create(CC_CALLBACK_0(Leaves::actionOver, this, leaf));
        
        leaf->runAction(Sequence::create(_spawn, call, NULL));
        
        m_count ++;
    }
}

void Leaves::actionOver(Sprite* leaf)
{
    leaf->removeFromParentAndCleanup(true);
    m_count--;
}