//
//  SpiderKind.h
//  CoolRun
//
//  Created by ManYou on 14/11/26.
//
//

#ifndef __CoolRun__SpiderKind__
#define __CoolRun__SpiderKind__

#include "Spider.h"

class SpiderKind : public Spider
{
public:
    SpiderKind();
    ~SpiderKind();
    virtual bool init();
    CREATE_FUNC(SpiderKind);
    
    virtual void setState(SpiderState state) override;
    virtual void dead() override;
    
    virtual void movementEvent(Armature *armature, MovementEventType movementType, const std::string& movementID) override;
    virtual void frameEvent(Bone *bone, const std::string& frameEventName, int originFrameIndex, int currentFrameIndex) override;
    
    
    virtual void trackCollideWithRunner(Runner* _runner) override;
    virtual void trackCollideWithBullet(Bullet* bullet) override;
};


#endif /* defined(__CoolRun__SpiderKind__) */
