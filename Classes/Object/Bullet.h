//
//  Bullet.h
//  CoolRun
//
//  Created by ManYou on 14/12/5.
//
//

#ifndef __CoolRun__Bullet__
#define __CoolRun__Bullet__

#include "cocos2d.h"
#include "MultipleCollideNode.h"
#include "ActionHelp.h"

class Bullet : public MultipleCollideNode
{
public:
    Bullet();
    ~Bullet();
    
    virtual bool init() override;
    CREATE_FUNC(Bullet);
    
    virtual void loadJson(rapidjson::Value& _value) override;
    virtual void saveData(string* buffer) override;
    
    virtual void beingDestoryed();
    
    void setRunnerHurt(bool flag) { b_isRunnerHurt = flag; }
    void setAnimalHurt(bool flag) { b_isAnimalHurt = flag; }
    bool isRunnerHurt() { return b_isRunnerHurt; }
    bool isAnimalHurt() { return b_isAnimalHurt; }
    void setAtkable(bool flag) { b_isAtkable = flag; }
    bool isAtkable() { return b_isAtkable; }
protected:
    bool b_isRunnerHurt;
    bool b_isAnimalHurt;
    bool b_isAtkable;
    ParticleSystemQuad* m_particleSys;
private:
};

#endif /* defined(__CoolRun__Bullet__) */
