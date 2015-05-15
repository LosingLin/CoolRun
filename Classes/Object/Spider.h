//
//  Spider.h
//  CoolRun
//
//  Created by ManYou on 14/11/26.
//
//

#ifndef __CoolRun__Spider__
#define __CoolRun__Spider__

#include "cocos2d.h"
#include "Animal.h"
#include "editor-support/cocostudio/CocoStudio.h"
#include "AudioHelp.h"

USING_NS_CC;
using namespace cocostudio;

enum SpiderState
{
    kSpiderState_Unknown = 0,
    kSpiderState_Stand = 1,
    kSpiderState_Walk = 2,
    kSpiderState_Hurted = 3,
    kSpiderState_Attack = 4,
};
class Spider : public Animal
{
public:
    Spider();
    ~Spider();
    virtual bool init() override;
    CREATE_FUNC(Spider);
    
    virtual void setState(SpiderState state);
    SpiderState getState() { return m_state; }
    
    virtual void loadJson(rapidjson::Value& value) override;
    virtual void saveData(string* buffer) override;
    
    
    virtual void CollideTrackListener_CollideOnce(CollideDirection direction, PhysicNode *node);
    virtual void CollideTrackListener_CollideAll(CollideDirection direction);
    
    static Spider* create(rapidjson::Value& _value);
    
    virtual void movementEvent(Armature *armature, MovementEventType movementType, const std::string& movementID);
    virtual void frameEvent(Bone *bone, const std::string& frameEventName, int originFrameIndex, int currentFrameIndex);
    
    virtual void trackCollideWithRunner(Runner* _runner) override;
    virtual void trackCollideWithBullet(Bullet* bullet) override;
protected:
    Armature *m_armature;
    SpiderState m_state;
};

#endif /* defined(__CoolRun__Spider__) */
