//
//  Item.h
//  CoolRun
//
//  Created by ManYou on 14/12/20.
//
//

#ifndef __CoolRun__Item__
#define __CoolRun__Item__

#include "cocos2d.h"
#include "MultipleCollideNode.h"

class Item : public MultipleCollideNode
{
public:
    Item();
    ~Item();
    
    virtual bool init() override;
    CREATE_FUNC(Item);
    
    virtual void onEnter() override;
    virtual void onExit() override;
    virtual void update(float delta) override;
    
    virtual void loadJson(rapidjson::Value& _value) override;
    virtual void saveData(string* buffer) override;
    
    virtual void trackCollideWithRunner(Runner* _runner);
    virtual void trackCollideWithBullet(Bullet* bullet) {};
    
    void fly();
    virtual void active(Runner* _runner);
    
    void setFlyVelcity(float v) { m_flyVelcity = v; }
    float getFlyVelcity() { return m_flyVelcity; }
protected:
    Sprite* m_sp;
    Sprite* m_icon;
    float m_angle;
    float m_angleSpeed;
    float m_maxY;
    float m_orgY;
    
    bool b_isFlying;
    
    float m_flyVelcity;
private:
    
};

#endif /* defined(__CoolRun__Item__) */
