//
//  PhysicNodeFactory.h
//  CoolRun
//
//  Created by ManYou on 14-8-15.
//
//

#ifndef __CoolRun__PhysicNodeFactory__
#define __CoolRun__PhysicNodeFactory__

#include "cocos2d.h"
#include "JsonHelp.h"
#include "Base.h"

USING_NS_CC;

class PhysicNode;
class Item;
class PhysicNodeFactory
{
public:
    ~PhysicNodeFactory();
    
    static PhysicNodeFactory* getInstance();
    void purgeInstance();
    
    PhysicNode* create(rapidjson::Value& _value);
    
    Item* createRandomItem();
private:
    PhysicNodeFactory();
    
    static PhysicNodeFactory* m_instance;
};

#endif /* defined(__CoolRun__PhysicNodeFactory__) */
