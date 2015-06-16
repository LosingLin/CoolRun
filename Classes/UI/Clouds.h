//
//  Clouds.h
//  CoolRun
//
//  Created by ManYou on 15/5/28.
//
//

#ifndef __CoolRun__Clouds__
#define __CoolRun__Clouds__

#include "cocos2d.h"

USING_NS_CC;

class Clouds : public Layer
{
public:
    Clouds();
    ~Clouds();
    
    virtual bool init();
    CREATE_FUNC(Clouds);
    
    virtual void onEnter();
    virtual void onExit();
    virtual void update(float delta);
    
    void actionOver(Sprite* leaf);
    
    void setVelocity(float v) { m_velocity = v; };
    
    void buildClouds(int min_x, int max_x);
private:
    int m_count;
    float m_velocity;
    __Array* m_clouds;
};

#endif /* defined(__CoolRun__Clouds__) */
