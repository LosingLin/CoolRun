//
//  MissionDataInterface.cpp
//  CoolRun
//
//  Created by ManYou on 14-10-7.
//
//

#include "MissionDataInterface.h"
#include "Base.h"

MissionDataInterface::MissionDataInterface()
: Ref()
, m_dirColObjs(nullptr)
, m_simpleColObjs(nullptr)
, m_bulletColObjs(nullptr)
{
}

MissionDataInterface::~MissionDataInterface()
{
    CC_SAFE_RELEASE_NULL(m_dirColObjs);
    CC_SAFE_RELEASE_NULL(m_simpleColObjs);
}

bool MissionDataInterface::init()
{
    
    CREATEANDRETAINARRAY(m_dirColObjs);
    CREATEANDRETAINARRAY(m_simpleColObjs);
    CREATEANDRETAINARRAY(m_bulletColObjs);
    
    return true;
}