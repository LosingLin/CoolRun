//
//  EditorManager.cpp
//  CoolRun
//
//  Created by ManYou on 15/5/14.
//
//

#include "EditorManager.h"

EditorManager* EditorManager::m_instance = nullptr;

EditorManager::EditorManager()
: Ref()
{
    
}
EditorManager::~EditorManager()
{
    
}

EditorManager* EditorManager::getInstance()
{
    if (!m_instance)
    {
        m_instance = new EditorManager();
    }
    
    return m_instance;
}
void EditorManager::purgeInstance()
{
    if (m_instance)
    {
        delete m_instance;
        m_instance = nullptr;
    }
}