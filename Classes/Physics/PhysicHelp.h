//
//  PhysicHelp.h
//  CoolRun
//
//  Created by ManYou on 14-8-12.
//
//

#ifndef __CoolRun__PhysicHelp__
#define __CoolRun__PhysicHelp__

#include "cocos2d.h"

USING_NS_CC;

class PhysicNode;
namespace PhysicHelp
{
    //交换x方向上的速度和加速度
    void exchangePhysicNode_XV_XA(PhysicNode *node1, PhysicNode *node2);
    //交换y方向上的速度和加速度
    void exchangePhysicNode_YV_YA(PhysicNode *node1, PhysicNode *node2);
    
    //计算相对于node位置的rect
    const Rect countPhysicNodeRect(PhysicNode *node);
    
    //计算rect相对于node位置的rect
    const Rect countPhysicNodeRect(PhysicNode *node, const Rect& rect);
    
    //调试用的
    void showTips(const char* tips, Node *parent, const Vec2& pos);
    void showTipsOver(Node *node, Node *label);
}

#endif /* defined(__CoolRun__PhysicHelp__) */
