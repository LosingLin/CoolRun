//
//  MissionObjects.cpp
//  CoolRun
//
//  Created by ManYou on 14-10-3.
//
//

#include "MissionObjects.h"
#include "PhysicNode.h"
#include "PhysicNodeFactory.h"


MissionObjects::MissionObjects()
: MissionDataInterface()
{
}
MissionObjects::~MissionObjects()
{
}
bool MissionObjects::init()
{
    if (!MissionDataInterface::init())
    {
        return false;
    }
    
    return true;
}

void MissionObjects::loadJson(rapidjson::Value& _value)
{
    rapidjson::Value tVal;
    if (JsonHelp::getValueByKey(_value, tVal, "objects"))
    {
        
        if (tVal.IsArray())
        {
            for (int i = 0; i < tVal.Size(); ++ i)
            {
                auto _node = PhysicNodeFactory::getInstance()->create(tVal[i]);
                if (kCollideTypeDirection == _node->getCollideType())
                {
                    m_dirColObjs->addObject(_node);
                }
                else if (kCollideTypeSimple == _node->getCollideType())
                {
                    m_simpleColObjs->addObject(_node);
                }
                else if (kCollideTypeBullet == _node->getCollideType())
                {
                    m_bulletColObjs->addObject(_node);
                }
            }
        }
    }
    else
    {
        log("mission has no objects");
    }
}

MissionObjects* MissionObjects::create(rapidjson::Value& _value)
{
    auto _missionObjs = MissionObjects::create();
    _missionObjs->loadJson(_value);
    return _missionObjs;
}