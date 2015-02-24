//
//  Boss.h
//  CoolRun
//
//  Created by ManYou on 15/1/15.
//
//

#ifndef __CoolRun__Boss__
#define __CoolRun__Boss__

#include "cocos2d.h"
#include "Animal.h"
#include "editor-support/cocostudio/CocoStudio.h"

USING_NS_CC;
using namespace cocostudio;

class HpBar;
class Boss : public Animal
{
public:
    Boss();
    ~Boss();
    
    virtual bool init() override;
    CREATE_FUNC(Boss);
    
    bool isReady() { return b_isReady; }
    void setReady(bool flag) { b_isReady = flag; }
    
    bool isAtking() { return b_isAtking; }
    void setAtking(bool flag) { b_isAtking = flag; }
    
    virtual void hurted() {};
    virtual void dead() {};
    
    virtual void movementEvent(Armature *armature, MovementEventType movementType, const std::string& movementID){};
    virtual void frameEvent(Bone *bone, const std::string& frameEventName, int originFrameIndex, int currentFrameIndex){};
    
protected:
    HpBar* m_hpBar;
    Armature* m_armature;
    bool b_isReady;
    bool b_isAtking;
    int m_atkIndex;
    float m_totalHp;
    float m_curHp;
};

#endif /* defined(__CoolRun__Boss__) */
