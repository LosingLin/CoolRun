//
//  GravityPhysic.h
//  CoolRun
//
//  Created by ManYou on 14-8-8.
//
//

#ifndef __CoolRun__GravityPhysic__
#define __CoolRun__GravityPhysic__

#include "cocos2d.h"

USING_NS_CC;
class PhysicNode;
class GravityPhysics : public Ref
{
public:
    GravityPhysics();
    ~GravityPhysics();
    virtual bool init();
    CREATE_FUNC(GravityPhysics);
    
    void setGravity(float g) { m_gravity = g; }
    float getGravity() { return m_gravity; }
    
    void addPhysicNode(PhysicNode *pNode);
    void removePhysicNode(PhysicNode *pNode);
    
    void addPhysicNodesFromArray(__Array* pNodes);
    
    void updatePhysicNodes(float delta);
    
private:
    float m_gravity;
    __Array *m_physicNodes;
};

#endif /* defined(__CoolRun__GravityPhysic__) */
