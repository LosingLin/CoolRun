//
//  MissionInterface.cpp
//  CoolRun
//
//  Created by ManYou on 14-10-7.
//
//

#include "MissionInterface.h"
#include "MissionObjects.h"
#include "MissionCollection.h"


MissionInterface::MissionInterface()
: Ref()
, m_objs(nullptr)
, m_collection(nullptr)
{
}
MissionInterface::~MissionInterface()
{
    CC_SAFE_RELEASE_NULL(m_objs);
    CC_SAFE_RELEASE_NULL(m_collection);
}

bool MissionInterface::init()
{
    m_objs = MissionObjects::create();
    CC_SAFE_RETAIN(m_objs);
    m_collection = MissionCollection::create();
    CC_SAFE_RETAIN(m_collection);
    
    return true;
}

void MissionInterface::loadJson(rapidjson::Value& _value)
{
    //objects
    m_objs->loadJson(_value);
    //collection
    m_collection->loadJson(_value);
}