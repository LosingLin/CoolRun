//
//  BossTrebleHeads.h
//  CoolRun
//
//  Created by ManYou on 15/3/16.
//
//

#ifndef __CoolRun__BossTrebleHeads__
#define __CoolRun__BossTrebleHeads__

#include "Boss.h"

enum BossTrebleHeadsPlayIndex
{
    kBTHPlayIndex_Walk = 0,
    kBTHPlayIndex_Atk_01 = 1,
    kBTHPlayIndex_Atk_02 = 2,
    kBTHPlayIndex_Atk_03 = 3,
    kBTHPlayIndex_OpenMouth = 4,
    kBTHPlayIndex_Stand = 5,
    kBTHPlayIndex_Hurt = 6,
    kBTHPlayIndex_Dead = 7
};

class Spider;
class BossTrebleHeads : public Boss
{
public:
    enum class AttackSequence
    {
        NONE,
        ATK_01,
        ATK_02,
        ATK_03,
        ATK_04,
        ATK_05,
        ATK_06,
        ATK_07
    };
public:
    BossTrebleHeads();
    ~BossTrebleHeads();
    
    virtual bool init() override;
    CREATE_FUNC(BossTrebleHeads);
    
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
    
    void jump(float yv);
    void jumpEnd();
private:
    AttackSequence m_atkSeq;
};


#endif /* defined(__CoolRun__BossTrebleHeads__) */
