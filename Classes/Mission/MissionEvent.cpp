//
//  MissionEvent.cpp
//  CoolRun
//
//  Created by ManYou on 14-10-3.
//
//

#include "MissionEvent.h"


MissionEvent::MissionEvent()
: Ref()
, m_interface(nullptr)
, m_startPageStretch(0.0f)
{
}
MissionEvent::~MissionEvent()
{
    CC_SAFE_RELEASE_NULL(m_interface);
}
bool MissionEvent::init()
{
    m_interface = MissionInterface::create();
    CC_SAFE_RETAIN(m_interface);
    
    return true;
}

void MissionEvent::loadJson(rapidjson::Value& _value)
{
    //interface
    m_interface->loadJson(_value);
    
    if (_value.HasMember("page_s"))
    {
        m_startPageStretch = JsonHelp::getFloat(_value["page_s"]);
    }
}

MissionEvent* MissionEvent::create(rapidjson::Value& _value)
{
    auto _event = MissionEvent::create();
    _event->loadJson(_value);
    return _event;
}