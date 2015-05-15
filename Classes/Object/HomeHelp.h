//
//  HomeHelp.h
//  CoolRun
//
//  Created by ManYou on 14/11/6.
//
//

#ifndef __CoolRun__HomeHelp__
#define __CoolRun__HomeHelp__

#include "cocos2d.h"
#include "Animal.h"

USING_NS_CC;

class HomeHelp : public Animal
{
public:
    HomeHelp();
    ~HomeHelp();
    virtual bool init();
    CREATE_FUNC(HomeHelp);
    
    virtual void CollideTrackListener_CollideOnce(CollideDirection direction, PhysicNode *node);
    virtual void CollideTrackListener_CollideAll(CollideDirection direction);
private:
    bool b_isAudioed;
};

#endif /* defined(__CoolRun__HomeHelp__) */
