//
//  GameController.h
//  CoolRun
//
//  Created by ManYou on 14-9-9.
//
//

#ifndef __CoolRun__GameController__
#define __CoolRun__GameController__

#include "cocos2d.h"
#include "PhysicNode.h"

USING_NS_CC;

class GameController
{
    virtual void addCoin(int num) = 0;
    virtual void destory(PhysicNode* _node) = 0;
};

#endif /* defined(__CoolRun__GameController__) */
