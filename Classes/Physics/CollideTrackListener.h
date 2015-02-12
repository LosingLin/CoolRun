//
//  CollideTrackListener.h
//  CoolRun
//
//  Created by ManYou on 14-8-12.
//
//

#ifndef __CoolRun__CollideTrackListener__
#define __CoolRun__CollideTrackListener__

#include "CollideTrack.h"

class CollideTrackListener
{
    virtual void CollideTrackListener_CollideOnce(CollideDirection direction, PhysicNode *node) = 0;
    virtual void CollideTrackListener_CollideAll(CollideDirection direction) = 0;
};

#endif /* defined(__CoolRun__CollideTrackListener__) */
