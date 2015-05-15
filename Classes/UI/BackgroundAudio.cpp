//
//  BackgroundAudio.cpp
//  CoolRun
//
//  Created by ManYou on 15/5/5.
//
//

#include "BackgroundAudio.h"
#include "AudioHelp.h"

BackgroundAudio::BackgroundAudio()
: Layer()
, m_type(BGAType::NULLTYPE)
{
    
}
BackgroundAudio::~BackgroundAudio()
{
    
}

bool BackgroundAudio::init()
{
    if (!Layer::init())
    {
        return false;
    }
    
    
    return true;
}

void BackgroundAudio::onEnter()
{
    Layer::onEnter();
    
    //this->schedule(schedule_selector(BackgroundAudio::update), 0.1);
    
    
}
void BackgroundAudio::onExit()
{
    //this->unschedule(schedule_selector(BackgroundAudio::update));
    Layer::onExit();
}

void BackgroundAudio::setBGAType(BGAType _type)
{
    if (m_type != _type)
    {
        m_type = _type;
        AudioHelp::stopAllBgA();
        switch (m_type)
        {
            case BGAType::DAY:
            {
                AudioHelp::playBgA("day_min.mp3");
            }
                break;
            case BGAType::NIGHT:
            {
                AudioHelp::playBgA("night_min.mp3");
            }
                break;
            case BGAType::BOSS:
            {
                AudioHelp::playBgA("boss_min.mp3");
            }
                break;
            default:
                break;
        }
    }
}