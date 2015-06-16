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
    kPhysicNodeSaw = 3,
    kPhysicNodeEnemy = 4,
    kPhysicNodeSpider = 5,
    kPhysicNodeSpiderKind = 6,
    kPhysicNodeSpiderPoison = 7,
    kPhysicNodeSpiderSpines = 8,
    kPhysicNodeSpiderFly = 9,
    kPhysicNodeBulletPoison = 10,
    kPhysicNodeBulletAlertPoison = 11,
    kPhysicNodeBulletAlertNet = 12,
    kPhysicNodeItem = 13,
    kPhysicNodeItemSpare = 14,
    kPhysicNodeItemMagnet = 15,
    kPhysicNodeItemTimesCoin = 16,
    kPhysicNodeItemTimesJump = 17,
    kPhysicNodeItemDad = 18,
    kPhysicNodeItemLandBuild = 19,
    kPhysicNodeItemFly = 20,
    kPhysicNodeTypeCount = 21,
};

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
