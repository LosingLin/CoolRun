//
//  MissionPage.cpp
//  CoolRun
//
//  Created by ManYou on 14-8-19.
//
//

#include "MissionPage.h"
#include "Base.h"
#include "PhysicNodeFactory.h"


MissionPage::MissionPage()
: Ref()
, m_interface(nullptr)
, m_events(nullptr)
, b_isLastPage(false)
{
}
MissionPage::~MissionPage()
{
    CC_SAFE_RELEASE_NULL(m_interface);
    CC_SAFE_RELEASE_NULL(m_events);
}
bool MissionPage::init()
{
    m_interface = MissionInterface::create();
    CC_SAFE_RETAIN(m_interface);
    
    CREATEANDRETAINARRAY(m_events);
    return true;
}

void MissionPage::loadJson(rapidjson::Value& _value)
{
    //interface
    m_interface->loadJson(_value);
    
    //events
    rapidjson::Value tVal;
    if (JsonHelp::getValueByKey(_value, tVal, "events"))
    {
        if (tVal.IsArray())
        {
            for (int i = 0; i < tVal.Size(); ++ i)
            {
                auto _event = MissionEvent::create(tVal[i]);
                m_events->addObject(_event);
            }
        }
    }
    else
    {
        log("mission has no objects");
    }
}

MissionPage* MissionPage::create(rapidjson::Value& _value)
{
    auto _missionPage = MissionPage::create();
    _missionPage->loadJson(_value);
    return _missionPage;
}