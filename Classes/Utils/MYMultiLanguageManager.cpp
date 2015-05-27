//
//  MYMultiLanguageManager.cpp
//  CoolRun
//
//  Created by ManYou on 15/5/13.
//
//

#include "MYMultiLanguageManager.h"
#include "MYUserDefaultManager.h"

#define MULTILANGUAGEFILE "langauge"

MYMultiLanguageManager* MYMultiLanguageManager::m_instance = nullptr;
rapidjson::Document* MYMultiLanguageManager::m_doc = nullptr;

MYMultiLanguageManager::MYMultiLanguageManager()
: Ref()
{
    
}
MYMultiLanguageManager::~MYMultiLanguageManager()
{
    
}

const string MYMultiLanguageManager::getText(const char* key)
{
    if (!m_doc)
    {
        m_doc = new rapidjson::Document();
        string jsonstr = JsonHelp::readJsonFile(MULTILANGUAGEFILE, *m_doc);
    }
    auto currentLanguage = MYUserDefaultManager::getInstance()->getCurrentLanguage();
    auto l_key = this->getLanguageKey(currentLanguage);
    if ((*m_doc).HasMember(key))
    {
        if ((*m_doc)[key].HasMember(l_key.c_str()))
        {
            return (*m_doc)[key][l_key.c_str()].GetString();
        }
        else
        {
            return "LANGUGE.Err";
        }
    }
    else
    {
        return "Key.Err";
    }
}

const string MYMultiLanguageManager::getLanguageKey(MultiLanguageType type)
{
    switch (type)
    {
        case MultiLanguageType::ENGLISH:
        {
            return MULTI_LANGUAGE_ENGLISH;
        }
            break;
        case MultiLanguageType::CHINESE:
        {
            return MULTI_LANGUAGE_CHINESE;
        }
            break;
            
        default:
            break;
    }
    
    return MULTI_LANGUAGE_ENGLISH;
}


MYMultiLanguageManager::MultiLanguageType MYMultiLanguageManager::getCurrentLanguage()
{
    return MYUserDefaultManager::getInstance()->getCurrentLanguage();
}
void MYMultiLanguageManager::setCurrentLanguage(MYMultiLanguageManager::MultiLanguageType _type)
{
    MYUserDefaultManager::getInstance()->setCurrentLanguage(_type);
}

#pragma mark -

MYMultiLanguageManager* MYMultiLanguageManager::getInstance()
{
    if (!m_instance)
    {
        m_instance = new MYMultiLanguageManager();
    }
    return m_instance;
}
void MYMultiLanguageManager::purgeInstance()
{
    if (m_instance)
    {
        delete m_instance;
        m_instance = nullptr;
    }
    if (m_doc)
    {
        delete m_doc;
        m_doc = nullptr;
    }
}