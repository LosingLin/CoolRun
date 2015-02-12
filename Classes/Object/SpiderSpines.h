//
//  SpiderSpines.h
//  CoolRun
//
//  Created by ManYou on 14/11/26.
//
//

#ifndef __CoolRun__SpiderSpines__
#define __CoolRun__SpiderSpines__

#include "Spider.h"

class SpiderSpines : public Spider
{
public:
    SpiderSpines();
    ~SpiderSpines();
    virtual bool init();
    CREATE_FUNC(SpiderSpines);
    
    virtual void setState(SpiderState state) override;
    virtual void dead() override;
    
    virtual void movementEvent(Armature *armature, MovementEventType movementType, const std::string& movementID) override;
    virtual void frameEvent(Bone *bone, const std::string& frameEventName, int originFrameIndex, int currentFrameIndex) override;
    
    
    virtual void trackCollideWithRunner(Runner* _runner) override;
    virtual void trackCollideWithBullet(Bullet* bullet) override;
};


#endif /* defined(__CoolRun__SpiderSpines__) */
