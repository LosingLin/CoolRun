//
//  Runner.h
//  CoolRun
//
//  Created by ManYou on 14-8-7.
//
//

#ifndef __CoolRun__Runner__
#define __CoolRun__Runner__

#include "cocos2d.h"
#include "CollideNode.h"
#include "editor-support/cocostudio/CocoStudio.h"


using namespace cocostudio;

USING_NS_CC;

enum RunnerState
{
    kRunnerState_Unknown = 0,
    kRunnerState_Running = 1,
    kRunnerState_JumpUp = 2,
    kRunnerState_JumpUp2 = 3,
    kRunnerState_JumpDown = 4,
    kRunnerState_Crouch = 5,
    kRunnerState_Count = 6,
};

class Bullet;
class Runner : public CollideNode
{
public:
    Runner();
    ~Runner();
    
    enum class ItemState
    {
        
    };
    
    CREATE_FUNC(Runner);
    
    virtual bool init();
    
    void setRunnerState(RunnerState);
    RunnerState getRunnerState() { return m_state; }
    
    virtual void onEnter() override;
    virtual void onEnterTransitionDidFinish() override;
    virtual void update(float delta);
    void itemUpdate(float delta);
    
    virtual void CollideTrackListener_CollideOnce(CollideDirection direction, PhysicNode *node);
    virtual void CollideTrackListener_CollideAll(CollideDirection direction);
    
    virtual void trackCollideWithBullet(Bullet* bullet);
    bool isCollidedWithTrueBody(const Rect& rect);
    CollideDirection getDirectionWithTrueBody(const Rect& rect);
    
    void setJumpCount(int count) { m_jumpCount = count; }
    int getJumpCount() { return m_jumpCount; }
    void addJumpCount() { m_jumpCount++; }
    
    
    const Rect getAtkRect() { return m_attckRect; }
    void setAtkRect(const Rect& rect) { m_attckRect = rect; }
    bool isAtk() { return b_isAtk; }
    void setAtk(bool flag) { b_isAtk = flag; }
    bool isDad() { return b_isDad; }
    void setDad(bool flag) { b_isDad = flag; }
    bool isIgnoreLand() { return b_isIgnoreLand; }
    void setIgnoreLand(bool flag) { b_isIgnoreLand = flag; }
    
    void rebound();
    void jump();
    void attack();
    void attackOver(Node* _sword);
    
    //Item
    void initItemData();
    void clearAllItemBuffers();
    
    int getSpareNum() { return item_spareNum; }
    void displaySpareNum(int num);
    
    void setMagnetING(bool flag) { item_isMagnetING = flag; }
    bool isMagnetING() { return item_isMagnetING; }
    void setMagnetDistance(float dis) { item_magnetDistance = dis; }
    float getMagnetDistance() { return item_magnetDistance; };
    void setMagnetLastTime(float time) { item_magnetLastTime = time; }
    float getMagnetLastTime() { return item_magnetLastTime; }
    void startMagnet();
    void endMagnet();
    
    void setTimesCoinING(bool flag) { item_isTimesCoinING = flag; }
    bool isTimesCoinING() { return item_isTimesCoinING; }
    void setTimesCoinDistance(float dis) { item_timesCoinDistance = dis; }
    float getTimesCoinDistance() { return item_timesCoinDistance; }
    void setTimesCoinLastTime(float time) { item_timesCoinLastTime = time; }
    float getTimesCoinLastTime() { return item_timesCoinLastTime; }
    void startTimesCoin();
    void endTimesCoin();
    
    void setTimesJumpING(bool flag) { item_isTimesJumpING = flag; }
    bool isTimesJumpING() { return item_isTimesJumpING; }
    void setTimesJumpTimes(int times) { item_timesJumpTimes = times; }
    int getTimesJumpTimes() { return item_timesJumpTimes; }
    void setTimesJumpLastTime(float time) { item_timesJumpLastTime = time; }
    float getTimesJumpLastTime() { return item_timesJumpLastTime; }
    void startTimesJump();
    void endTimesJump();
    
    void setDadING(bool flag) { item_isDadING = flag; this->setDad(flag); }
    bool isDadING() { return item_isDadING; }
    void setDadLastTime(float time) { item_dadLastTime = time; }
    float getDadLastTime() { return item_dadLastTime; }
    void startDad();
    void endDad();
    
    void setLandBuildING(bool flag) { item_isLandBuildING = flag; }
    bool isLandBuildING() { return item_isLandBuildING; }
    void setBuildLandLastTime(float time) { item_buildLandLastTime = time; }
    float getBuildLandLastTime() { return item_buildLandLastTime; };
    void startLandBuild();
    void endLandBuild();
    
    void setFlyING(bool flag) { item_isFlyING = flag; };
    bool isFlyING() { return item_isFlyING; }
    void setFlyLastTime(float time) { item_flyLastTime = time; }
    float getFlyLastTime() { return item_flyLastTime; }
    void startFly();
    void endFly();
    void endFlyEffect();
    
    void setRebornING(bool flag) { item_isRebornING = flag; }
    bool isRebornING() { return item_isRebornING; }
    void startReborn();
    void endReborn();
    
    const Vec2 getIconPosition();
private:
    //Item
    int item_spareNum;
    int item_currentSpareNum;
    Label* item_spareNumLab;
    Sprite* item_spareIcon;
    
    bool item_isMagnetING;
    float item_magnetDistance;
    float item_magnetLastTime;
    float item_magnetCurrentTime;
    Sprite* item_magnetIcon;
    
    bool item_isTimesCoinING;
    float item_timesCoinDistance;
    float item_timesCoinLastTime;
    float item_timesCoinCurrentTime;
    Sprite* item_timesCoinIcon;
    
    bool item_isTimesJumpING;
    int item_timesJumpTimes;
    float item_timesJumpLastTime;
    float item_timesJumpCurrentTime;
    Sprite* item_timesJumpIcon;
    
    bool item_isDadING;
    float item_dadLastTime;
    float item_dadCurrentTime;
    Sprite* item_dadIcon;
    
    bool item_isLandBuildING;
    float item_buildLandLastTime;
    float item_buildLandCurrentTime;
    Sprite* item_buildLandIcon;
    
    bool item_isFlyING;
    bool item_isEndFlyING;
    float item_flyLastTime;
    float item_flyCurrentTime;
    Sprite* item_flyIcon;
    
    bool item_isRebornING;
    float item_rebornLastTime;
    float item_rebornCurrentTime;
    
private:
    RunnerState m_state;
    int m_jumpCount;
    __Array *m_actions;
    Rect m_attckRect;
    
    Rect m_headRect;
    Rect m_bodyRect;
    Rect m_legRect;
    
    bool b_isAtk;
    bool b_isDad; //无敌
    
    bool b_isIgnoreLand; //忽略地形
    
    Armature *m_armature;
};

#endif /* defined(__CoolRun__Runner__) */
