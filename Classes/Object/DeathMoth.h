//
//  DeathMoth.h
//  CoolRun
//
//  Created by ManYou on 15/3/24.
//
//

#ifndef __CoolRun__DeathMoth__
#define __CoolRun__DeathMoth__

#include "Boss.h"

enum DeathMothPlayIndex
{
    kDeathMothPlayIndex_Fly = 0,
    kDeathMothPlayIndex_Stand = 1,
    kDeathMothPlayIndex_OpenMouth = 2,
    kDeathMothPlayIndex_Atk01 = 3,
    kDeathMothPlayIndex_Rush = 4,
    kDeathMothPlayIndex_Hurt = 5,
    kDeathMothPlayIndex_Dead = 6
};

class DeathMoth : public Boss
{
public:
    enum class AttackSequence
    {
        NONE,
        ATK_01,
        ATK_02,
        ATK_03,
        ATK_04,
        ATK_05
    };
public:
    DeathMoth();
    ~DeathMoth();
    
    virtual bool init();
    CREATE_FUNC(DeathMoth);
    
    virtual void initRes() override;
    virtual void destoryRes() override;
    virtual void play(int index) override;
    virtual void hurted() override;
    virtual void dead() override;
    
    virtual Bullet* createShotBullet(int index) override;
    virtual Spider* createBornSpider(int index) override;
    
    virtual void trackCollideWithRunner(Runner* _runner) override;
    //virtual void trackCollideWithBullet(Bullet* bullet) override;
    
    virtual void movementEvent(Armature *armature, MovementEventType movementType, const std::string& movementID) override;
    virtual void frameEvent(Bone *bone, const std::string& frameEventName, int originFrameIndex, int currentFrameIndex) override;
    
    void attkSequence(int index);
    void attkSequenceEnd();
private:
    AttackSequence m_atkSeq;
    bool b_isHurting;
    int m_shotIndex;
};

#endif /* defined(__CoolRun__DeathMoth__) */
