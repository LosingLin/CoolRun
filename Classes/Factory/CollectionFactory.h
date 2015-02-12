//
//  CollectionFacory.h
//  CoolRun
//
//  Created by ManYou on 14-10-7.
//
//

#ifndef __CoolRun__CollectionFactory__
#define __CoolRun__CollectionFactory__

#include "cocos2d.h"
#include "JsonHelp.h"
#include "Collection.h"

USING_NS_CC;

enum CollectionType
{
    kCollectionTypeUnknown = 0,
    kCollectionTypeCoin = 2,
};

class Collection;
class CollectionFactory
{
public:
    ~CollectionFactory();
    
    static CollectionFactory* getInstance();
    void purgeInstance();
    
    Collection* create(rapidjson::Value& _value);
private:
    CollectionFactory();
    
    static CollectionFactory* m_instance;
};

#endif /* defined(__CoolRun__CollectionFacory__) */
