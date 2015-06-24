//
//  ResourceManager.cpp
//  CoolRun
//
//  Created by ManYou on 15/6/16.
//
//

#include "ResourceManager.h"

#define HDEXTESION "_hd"
#define SDEXTESION "_sd"

#define FILE_PLIST_EXT ".plist"
#define FILE_PNG_EXT ".png"
#define FILE_FNT_EXT ".fnt"

ResourceManager* ResourceManager::m_instance = nullptr;
ResourceManager::ResourceType ResourceManager::m_rType = ResourceManager::ResourceType::HD;

ResourceManager::ResourceManager()
: Ref()
{
    
}
ResourceManager::~ResourceManager()
{
    
}

ResourceManager* ResourceManager::getInstance()
{
    if (m_instance)
    {
        m_instance = new ResourceManager();
    }
    return m_instance;
}
void ResourceManager::purgeInstance()
{
    if (m_instance)
    {
        delete m_instance;
        m_instance = nullptr;
    }
}

const string ResourceManager::getPlistRes(const string& _name)
{
    return _name + getExtesion() + FILE_PLIST_EXT;
}
const string ResourceManager::getPngRes(const string& _name)
{
    return _name + getExtesion() + FILE_PNG_EXT;
}
const string ResourceManager::getFntRes(const string& _name)
{
    if (m_rType == ResourceType::SD)
    {
        return _name + getExtesion() + FILE_FNT_EXT;
    }
    else
    {
        return _name + FILE_FNT_EXT;
    }
}

string ResourceManager::getExtesion()
{
    switch (m_rType)
    {
        case ResourceType::HD :
        {
            return HDEXTESION;
        }
            break;
        case ResourceType::SD :
        {
            return SDEXTESION;
        }
            break;
            
        default:
            return HDEXTESION;
            break;
    }
}


void ResourceManager::removeBigSource()
{
    SpriteFrameCache* _spFrameCache = SpriteFrameCache::getInstance();
    _spFrameCache->removeSpriteFramesFromFile(this->getPlistRes("MainRes_01"));
    _spFrameCache->removeSpriteFramesFromFile(this->getPlistRes("MainRes_02"));
    _spFrameCache->removeSpriteFramesFromFile(this->getPlistRes("MainRes_03"));
    _spFrameCache->removeSpriteFramesFromFile(this->getPlistRes("background"));
    _spFrameCache->removeSpriteFramesFromFile(this->getPlistRes("background02"));
    _spFrameCache->removeSpriteFramesFromFile(this->getPlistRes("background03"));
    //SpriteFrameCache::getInstance()->removeUnusedSpriteFrames();
}
void ResourceManager::addBigSource()
{
    SpriteFrameCache* _spFrameCache = SpriteFrameCache::getInstance();
    _spFrameCache->addSpriteFramesWithFile(this->getPlistRes("MainRes_01"));
    _spFrameCache->addSpriteFramesWithFile(this->getPlistRes("MainRes_02"));
    _spFrameCache->addSpriteFramesWithFile(this->getPlistRes("MainRes_03"));
    _spFrameCache->addSpriteFramesWithFile(this->getPlistRes("background"));
    _spFrameCache->addSpriteFramesWithFile(this->getPlistRes("background02"));
    _spFrameCache->addSpriteFramesWithFile(this->getPlistRes("background03"));
}

