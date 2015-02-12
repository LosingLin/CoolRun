//
//  Enemy.h
//  CoolRun
//
//  Created by ManYou on 14-9-9.
//
//

#ifndef __CoolRun__Enemy__
#define __CoolRun__Enemy__

#include "cocos2d.h"
#include "Animal.h"
#include "editor-support/cocostudio/CocoStudio.h"

USING_NS_CC;
using namespace cocostudio;

class Enemy : public Animal
{
public:
    Enemy();
    ~Enemy();
    virtual bool init() override;
    CREATE_FUNC(Enemy);
    
    virtual void CollideTrackListener_CollideOnce(CollideDirection direction, PhysicNode *node);
    virtual void CollideTrackListener_CollideAll(CollideDirection direction);
    
    static Enemy* create(rapidjson::Value& _value);
    
    void movementEvent(Armature *armature, MovementEventType movementType, const std::string& movementID);
    void frameEvent(Bone *bone, const std::string& frameEventName, int originFrameIndex, int currentFrameIndex);
    
    virtual void trackCollideWithRunner(Runner* _runner) override;

private:
    Armature *m_armature;
    bool b_isAtk;
};

#endif /* defined(__CoolRun__Enemy__) */
