//
//  Leaves.h
//  CoolRun
//
//  Created by ManYou on 15/4/22.
//
//

#ifndef __CoolRun__Leaves__
#define __CoolRun__Leaves__

#include "cocos2d.h"

USING_NS_CC;

class Leaves : public Layer
{
public:
    Leaves();
    ~Leaves();
    
    virtual bool init();
    CREATE_FUNC(Leaves);
    
    virtual void onEnter();
    virtual void onExit();
    virtual void update(float delta);
    
    void actionOver(Sprite* leaf);
    
    void setVelocity(float v) { m_velocity = v; };
private:
    int m_count;
    float m_velocity;
};

#endif /* defined(__CoolRun__Leaves__) */
