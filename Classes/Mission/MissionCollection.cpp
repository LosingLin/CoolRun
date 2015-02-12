//
//  MissionCollection.cpp
//  CoolRun
//
//  Created by ManYou on 14-10-7.
//
//

#include "MissionCollection.h"
#include "PhysicNode.h"
#include "CollectionFactory.h"


MissionCollection::MissionCollection()
: MissionDataInterface()
, m_collections(nullptr)
{
}
MissionCollection::~MissionCollection()
{
}
bool MissionCollection::init()
{
    if (!MissionDataInterface::init())
    {
        return false;
    }
    CREATEANDRETAINARRAY(m_collections);
    
    return true;
}

void MissionCollection::loadJson(rapidjson::Value& _value)
{
    rapidjson::Value tVal;
    if (JsonHelp::getValueByKey(_value, tVal, "collections"))
    {
        if (tVal.IsArray())
        {
            for (int i = 0; i < tVal.Size(); ++ i)
            {
                auto _collection = CollectionFactory::getInstance()->create(tVal[i]);
                m_collections->addObject(_collection);
                
            }
            this->_fuckCollecions();
        }
    }
    else
    {
        log("mission has no objects");
    }
}

void MissionCollection::setCollections(__Array* cols)
{
    if (m_collections)
    {
        m_collections->removeAllObjects();
        m_dirColObjs->removeAllObjects();
        m_simpleColObjs->removeAllObjects();
        m_bulletColObjs->removeAllObjects();
    }
    m_collections = cols;
    CC_SAFE_RETAIN(m_collections);
    this->_fuckCollecions();
}
void MissionCollection::_fuckCollecions()
{
    for (int i = 0; i < m_collections->count(); ++ i)
    {
        auto _collection = dynamic_cast<Collection*>(m_collections->getObjectAtIndex(i));
        auto _arr = _collection->getCollection();
        for (int j = 0; j < _arr->count(); ++ j)
        {
            auto _node = dynamic_cast<PhysicNode*>(_arr->getObjectAtIndex(j));
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

MissionCollection* MissionCollection::create(rapidjson::Value& _value)
{
    auto _missionObjs = MissionCollection::create();
    _missionObjs->loadJson(_value);
    return _missionObjs;
}