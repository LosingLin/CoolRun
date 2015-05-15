//
//  Coin.h
//  CoolRun
//
//  Created by ManYou on 14-8-12.
//
//

#ifndef __CoolRun__Coin__
#define __CoolRun__Coin__

#include "cocos2d.h"
#include "CollideNode.h"

USING_NS_CC;

class Coin : public CollideNode
{
public:
    Coin();
    ~Coin();
    virtual bool init();
    CREATE_FUNC(Coin);
    
    static Coin* create(rapidjson::Value& _value);
    
    virtual void onEnter();
    virtual void onExit();
    
    virtual void removeAllChildrenWithCleanup(bool clear) override;
    
    virtual void update(float delta);
    void acionDoneCallback();
    void times();
    
    void bePicked();
    void bePickedDone();
    
//    virtual bool collided(PhysicNode* _runner) override;
    virtual void trackCollideWithRunner(Runner* _runner) override;
private:
    Sprite *m_sp;
    bool b_isAnimating;
    int m_score;
    bool b_isTimed;
};

#endif /* defined(__CoolRun__Coin__) */
