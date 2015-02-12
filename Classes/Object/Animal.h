//
//  Animal.h
//  CoolRun
//
//  Created by ManYou on 14/11/26.
//
//

#ifndef __CoolRun__Animal__
#define __CoolRun__Animal__

#include "cocos2d.h"
#include "MultipleCollideNode.h"

USING_NS_CC;
class Bullet;
class Animal : public MultipleCollideNode
{
public:
    Animal();
    ~Animal();
    virtual bool init();
    CREATE_FUNC(Animal);
    

    
    virtual void CollideTrackListener_CollideOnce(CollideDirection direction, PhysicNode *node) override;
    virtual void CollideTrackListener_CollideAll(CollideDirection direction) override;
};

#endif /* defined(__CoolRun__Animal__) */
