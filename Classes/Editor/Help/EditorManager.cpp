//
//  EditorManager.cpp
//  CoolRun
//
//  Created by ManYou on 15/5/14.
//
//

#include "EditorManager.h"
#include "GlobalDefined.h"

EditorManager* EditorManager::m_instance = nullptr;
#if (MY_RELEASE == 0)
EditorManager::EditorType EditorManager::m_editorType = EditorManager::EditorType::DEVELOPER;
#else
EditorManager::EditorType EditorManager::m_editorType = EditorManager::EditorType::PLAYER;
#endif

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