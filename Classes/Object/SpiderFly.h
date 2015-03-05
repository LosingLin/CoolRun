//
//  SpiderFly.h
//  CoolRun
//
//  Created by ManYou on 15/3/4.
//
//

#ifndef __CoolRun__SpiderFly__
#define __CoolRun__SpiderFly__

#include "Spider.h"

class SpiderFly : public Spider
{
public:
    SpiderFly();
    ~SpiderFly();
    virtual bool init();
    CREATE_FUNC(SpiderFly);
    
    virtual void setState(SpiderState state) override;
    virtual void dead() override;
    
    virtual void movementEvent(Armature *armature, MovementEventType movementType, const std::string& movementID) override;
    virtual void frameEvent(Bone *bone, const std::string& frameEventName, int originFrameIndex, int currentFrameIndex) override;
    
    
    virtual void trackCollideWithRunner(Runner* _runner) override;
    virtual void trackCollideWithBullet(Bullet* bullet) override;
};

#endif /* defined(__CoolRun__SpiderFly__) */
