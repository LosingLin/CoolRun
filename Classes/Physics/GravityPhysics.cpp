//
//  GravityPhysic.cpp
//  CoolRun
//
//  Created by ManYou on 14-8-8.
//
//

#include "GravityPhysics.h"
#include "PhysicNode.h"

GravityPhysics::GravityPhysics()
: Ref()
, m_gravity(0)
, m_physicNodes(NULL)
{
    
}
GravityPhysics::~GravityPhysics()
{
    CC_SAFE_RELEASE_NULL(m_physicNodes);
}

bool GravityPhysics::init()
{
    m_physicNodes = __Array::create();
    CC_SAFE_RETAIN(m_physicNodes);
    
    return true;
}

void GravityPhysics::addPhysicNode(PhysicNode *pNode)
{
    m_physicNodes->addObject(pNode);
}
void GravityPhysics::removePhysicNode(PhysicNode *pNode)
{
    m_physicNodes->removeObject(pNode);
}

void GravityPhysics::addPhysicNodesFromArray(__Array* pNodes)
{
    m_physicNodes->addObjectsFromArray(pNodes);
}

void GravityPhysics::updatePhysicNodes(float delta)
{
    //log("GravityPhysics::updatePhysicNodes %f", delta);
    PhysicNode *pNode = NULL;
    float yv = 0.0f;
    float xv = 0.0f;
    float xa = 0.0f;
    float ya = 0.0f;
    
    float y_dis = m_gravity * delta * 10;
    
    Vec2 pos = Vec2(0, 0);
    for (int i = 0; i < m_physicNodes->count(); ++ i) {
        pNode = dynamic_cast<PhysicNode*>(m_physicNodes->getObjectAtIndex(i));
        
        if (pNode->isVelocityIgnore())
        {
            continue;
        }
        
        yv = pNode->getYV();
        xv = pNode->getXV();
        xa = pNode->getXA();
        ya = pNode->getYA();
        
        pos = pNode->getPosition();
        
        if (pNode->isGravityEffect()) {
            
            ya += y_dis;
            
            //pNode->setYA(ya);
        }
        
        yv = (yv + ya);
        xv = (xv + xa);
        //log("ya : %f", ya * delta);
        pos.y += (yv * delta);
        pos.x += (xv * delta);
        //log("pos.y : %f", pos.y);
        pNode->setYV(yv);
        pNode->setXV(xv);
        pNode->setPosition(pos);
        
        
    }
}