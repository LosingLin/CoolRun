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

USING_NS_CC;

enum PhysicNodeType
{
    kPhysicNodeUnknown = 0,
    kPhysicNodeStone = 1,
    kPhysicNodeCoin = 2,
    kPhysicNodeEnemy = 3,
    kPhysicNodeSpider = 4,
    kPhysicNodeSpiderKind = 5,
    kPhysicNodeSpiderPoison = 6,
    kPhysicNodeSpiderSpines = 7,
    kPhysicNodeBulletPoison = 8,
    kPhysicNodeBulletAlert = 9,
    kPhysicNodeItem = 10,
    kPhysicNodeItemSpare = 11,
    kPhysicNodeItemMagnet = 12,
    kPhysicNodeItemTimesCoin = 13,
    kPhysicNodeItemTimesJump = 14,
    kPhysicNodeItemDad = 15,
    kPhysicNodeItemLandBuild = 16,
    kPhysicNodeItemFly = 17,
    kPhysicNodeTypeCount = 18,
};

class PhysicNode;
class PhysicNodeFactory
{
public:
    ~PhysicNodeFactory();
    
    static PhysicNodeFactory* getInstance();
    void purgeInstance();
    
    PhysicNode* create(rapidjson::Value& _value);
    
private:
    PhysicNodeFactory();
    
    static PhysicNodeFactory* m_instance;
};

#endif /* defined(__CoolRun__PhysicNodeFactory__) */
