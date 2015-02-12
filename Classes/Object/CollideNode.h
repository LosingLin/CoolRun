//
//  CollideNode.h
//  CoolRun
//
//  Created by ManYou on 14-9-9.
//
//

#ifndef __CoolRun__CollideNode__
#define __CoolRun__CollideNode__

#include "cocos2d.h"
#include "PhysicNode.h"
#include "CoolRunScene.h"
#include "PhysicHelp.h"

USING_NS_CC;
class Runner;
class Bullet;
class CollideNode : public PhysicNode
{
public:
    CollideNode();
    ~CollideNode();
    virtual bool init();
    CREATE_FUNC(CollideNode);
    
    void setGameController(CoolRun* _ctrl) { m_gameController = _ctrl; };
    
//    virtual bool collided(PhysicNode* _runner){ return false; };
//    virtual bool attacked(PhysicNode* _runner){ return false; };
    
    virtual void trackCollideWithRunner(Runner* _runner) {};
    virtual void trackCollideWithBullet(Bullet* bullet) {};
protected:
    CoolRun* m_gameController;

};

#endif /* defined(__CoolRun__CollideNode__) */
