//
//  Treasure.h
//  CoolRun
//
//  Created by ManYou on 15/7/1.
//
//

#ifndef __CoolRun__Treasure__
#define __CoolRun__Treasure__

#include "cocos2d.h"
#include "CollideNode.h"

USING_NS_CC;

class Treasure : public CollideNode
{
public:
    Treasure();
    ~Treasure();
    virtual bool init();
    CREATE_FUNC(Treasure);
    
    static Treasure* create(rapidjson::Value& _value);
    
    virtual void onEnter();
    virtual void onExit();
    
    virtual void times();
    
    virtual void bePicked();
    virtual void bePickedDone();
    
    //    virtual bool collided(PhysicNode* _runner) override;
    virtual void trackCollideWithRunner(Runner* _runner) override;
    
    bool isAnimating() { return b_isAnimating; }
    void setAnimating(bool flag) { b_isAnimating = flag; }
    int getScore() { return m_score; }
    void setScore(int score) { m_score = score; }
    bool isTimed() { return b_isTimed; }
    void setTimed(bool timed) { b_isTimed = timed; }
protected:
    Sprite* m_sp;
private:
    bool b_isAnimating;
    int m_score;
    bool b_isTimed;
};

#endif /* defined(__CoolRun__Treasure__) */
