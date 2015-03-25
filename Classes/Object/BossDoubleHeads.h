//
//  BossDoubleHeads.h
//  CoolRun
//
//  Created by ManYou on 15/1/15.
//
//

#ifndef __CoolRun__BossDoubleHeads__
#define __CoolRun__BossDoubleHeads__

#include "Boss.h"

enum BossDoubleHeadsPlayIndex
{
    kBDHPlayIndex_Walk = 0,
    kBDHPlayIndex_Atk_01 = 1,
    kBDHPlayIndex_Atk_02 = 2,
    kBDHPlayIndex_Atk_03 = 3,
    kBDHPlayIndex_OpenMouth = 4,
    kBDHPlayIndex_Stand = 5,
    kBDHPlayIndex_Hurt = 6,
    kBDHPlayIndex_Dead = 7
};

class Spider;
class BossDoubleHeads : public Boss
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
    BossDoubleHeads();
    ~BossDoubleHeads();
    
    virtual bool init() override;
    CREATE_FUNC(BossDoubleHeads);
    
    virtual void trackCollideWithRunner(Runner* _runner) override;
    virtual void trackCollideWithBullet(Bullet* bullet) override;
    
    virtual void movementEvent(Armature *armature, MovementEventType movementType, const std::string& movementID) override;
    virtual void frameEvent(Bone *bone, const std::string& frameEventName, int originFrameIndex, int currentFrameIndex) override;
    
    
    virtual void initRes() override;
    virtual void destoryRes() override;
    virtual void hurted() override;
    virtual void dead() override;
    virtual void play(int index) override;
    
    virtual Bullet* createShotBullet(int index) override;
    virtual Spider* createBornSpider(int index) override;
    
    void attkSequence(int index);
    void attkSequenceEnd();
private:
    AttackSequence m_atkSeq;
};

#endif /* defined(__CoolRun__BossDoubleHeads__) */
