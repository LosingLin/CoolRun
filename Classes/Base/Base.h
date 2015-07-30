//
//  Base.h
//  CoolRun
//
//  Created by ManYou on 14-8-8.
//
//

#ifndef CoolRun_Base_h
#define CoolRun_Base_h

#include "GlobalDefined.h"
#include "DrawableNode.h"

enum CRDirection
{
    kCRDirectionLeft = 1,
    kCRDirectionRight = 2,
    kCRDirectionUp = 3,
    kCRDirectionDown = 4,
};

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
    kPhysicNodeTreasureBox = 21,
    kPhysicNodeJade = 22,
    kPhysicNodeTypeCount = 23,
};

#endif
