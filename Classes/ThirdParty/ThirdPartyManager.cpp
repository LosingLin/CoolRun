//
//  ThirdPartyManager.cpp
//  CoolRun
//
//  Created by ManYou on 15/6/14.
//
//

#include "ThirdPartyManager.h"
#include "ReviveMenu.h"

ThirdPartyManager* ThirdPartyManager::m_instance = nullptr;

ThirdPartyManager::ThirdPartyManager()
: Ref()
, m_reviveMenu(nullptr)
{
    
}
ThirdPartyManager::~ThirdPartyManager()
{
    
}

ReviveMenu* ThirdPartyManager::getReviveMenu()
{
    return m_reviveMenu;
}

ThirdPartyManager* ThirdPartyManager::getInstance()
{
    if (!m_instance)
    {
        m_instance = new ThirdPartyManager();
    }
    return m_instance;
}
void ThirdPartyManager::purgeInstance()
{
    if (m_instance)
    {
        delete m_instance;
        m_instance = nullptr;
    }
}