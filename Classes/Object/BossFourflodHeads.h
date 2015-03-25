//
//  BossFourflodHeads.h
//  CoolRun
//
//  Created by ManYou on 15/3/16.
//
//

#ifndef __CoolRun__BossFourflodHeads__
#define __CoolRun__BossFourflodHeads__

#include "Boss.h"

enum BossFourflodHeadsPlayIndex
{
    kBFHPlayIndex_Walk = 0,
    kBFHPlayIndex_Atk_01 = 1,
    kBFHPlayIndex_Atk_02 = 2,
    kBFHPlayIndex_Atk_03 = 3,
    kBFHPlayIndex_OpenMouth = 4,
    kBFHPlayIndex_Stand = 5,
    kBFHPlayIndex_Hurt = 6,
    kBFHPlayIndex_Dead = 7
};

class Spider;
class BossFourflodHeads : public Boss
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
        ATK_07,
        ATK_08
    };
public:
    BossFourflodHeads();
    ~BossFourflodHeads();
    
    virtual bool init() override;
    CREATE_FUNC(BossFourflodHeads);
    
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
    
    void jump(float yv = 560.0f);
    void jumpEnd();
private:
    AttackSequence m_atkSeq;
};

#endif /* defined(__CoolRun__BossFourflodHeads__) */
