//
//  CollectionFacory.cpp
//  CoolRun
//
//  Created by ManYou on 14-10-7.
//
//

#include "CollectionFactory.h"
#include "CollectionCoin.h"

CollectionFactory* CollectionFactory::m_instance = NULL;

CollectionFactory::CollectionFactory()
{
}
CollectionFactory::~CollectionFactory()
{
}

CollectionFactory* CollectionFactory::getInstance()
{
    if (!m_instance)
    {
        m_instance = new CollectionFactory();
    }
    return m_instance;
}
void CollectionFactory::purgeInstance()
{
    if (m_instance)
    {
        delete m_instance;
    }
}

Collection* CollectionFactory::create(rapidjson::Value& _value)
{
//    auto _collectionType = kCollectionTypeUnknown;
//    Collection* _collection = NULL;
//    if (_value.HasMember("c_type"))
//    {
//        _collectionType = (CollectionType)JsonHelp::getInt(_value["c_type"]);
//    }
//    switch (_collectionType)
//    {
//        case kCollectionTypeCoin:
//            _collection = CollectionCoin::create();
//            _collection->loadJson(_value);
//            break;
//            
//        default:
//            break;
//    }
    Collection* _collection = Collection::create();
    _collection->loadJson(_value);
    return _collection;
}