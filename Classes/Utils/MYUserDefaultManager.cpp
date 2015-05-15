//
//  MYUserDefaultManager.cpp
//  CoolRun
//
//  Created by ManYou on 15/5/13.
//
//

#include "MYUserDefaultManager.h"

MYUserDefaultManager* MYUserDefaultManager::m_instance = nullptr;

MYUserDefaultManager::MYUserDefaultManager()
: Ref()
{
    
}
MYUserDefaultManager::~MYUserDefaultManager()
{
    
}

bool MYUserDefaultManager::init()
{
    
    return true;
}

#pragma mark -

bool MYUserDefaultManager::isPlayedGuide()
{
    bool flag = UserDefault::getInstance()->getBoolForKey(IS_PLAYER_GUIDED);
    return flag;
}
void MYUserDefaultManager::setPlayedGuide(bool key)
{
    UserDefault::getInstance()->setBoolForKey(IS_PLAYER_GUIDED, key);
}

MYMultiLanguageManager::MultiLanguageType MYUserDefaultManager::getCurrentLanguage()
{
    auto str = UserDefault::getInstance()->getStringForKey(MULTI_LANGUAGE_FLAG);
    
    if (MULTI_LANGUAGE_CHINESE == str)
    {
        return MYMultiLanguageManager::MultiLanguageType::CHINESE;
    }
    else if ("" == str && MULTI_LANGUAGE_ENGLISH == str)
    {
        return MYMultiLanguageManager::MultiLanguageType::ENGLISH;
    }
    
    return MYMultiLanguageManager::MultiLanguageType::ENGLISH;
}
void MYUserDefaultManager::setCurrentLanguage(MYMultiLanguageManager::MultiLanguageType _type)
{
    switch (_type) {
        case MYMultiLanguageManager::MultiLanguageType::ENGLISH:
        {
            UserDefault::getInstance()->setStringForKey(MULTI_LANGUAGE_FLAG, MULTI_LANGUAGE_ENGLISH);
        }
            break;
        case MYMultiLanguageManager::MultiLanguageType::CHINESE:
        {
            UserDefault::getInstance()->setStringForKey(MULTI_LANGUAGE_FLAG, MULTI_LANGUAGE_CHINESE);
        }
            break;
            
        default:
            break;
    }
}

#pragma mark -

MYUserDefaultManager* MYUserDefaultManager::getInstance()
{
    if (!m_instance)
    {
        m_instance = new MYUserDefaultManager();
    }
    return m_instance;
}
void MYUserDefaultManager::purgeInstance()
{
    if (m_instance)
    {
        delete m_instance;
        m_instance = nullptr;
    }
}