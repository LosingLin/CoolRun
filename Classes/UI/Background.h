//
//  Background.h
//  CoolRun
//
//  Created by ManYou on 14/10/21.
//
//

#ifndef __CoolRun__Background__
#define __CoolRun__Background__

#include "cocos2d.h"

USING_NS_CC;

class Background : public Layer
{
public:
    Background();
    ~Background();
    virtual bool init() override;
    CREATE_FUNC(Background);
    
    static Background* create(const std::string& framename01, const std::string& framename02);
    
    void updateBackGround(float delta);
    
    void setVelocity(float _velocity) { m_velocity = _velocity; } ;
    
    void addBackgound(const std::string& framename);
    
    Sprite* getMaxPositionSprite();
    
private:
    __Array* m_bgs;
    float m_velocity;
    int m_index;
};

#endif /* defined(__CoolRun__Background__) */
