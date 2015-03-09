//
//  CoolRunScene.h
//  CoolRun
//
//  Created by ManYou on 14-8-7.
//
//

#ifndef __CoolRun__CoolRunScene__
#define __CoolRun__CoolRunScene__

#include "cocos2d.h"
#include "GameController.h"
#include "MYButton.h"

#define ZORDER_STONE        0
#define ZORDER_COIN         1
#define ZORDER_RUNNER       2
#define ZORDER_ANIMAL       3
#define ZORDER_BULLET       4
#define ZORDER_ITEM         5
#define ZORDER_WARNING      6

#define ZORDER_HEADMENU     10

#define ZORDER_POPVIEW     100

USING_NS_CC;
class Runner;
class GravityPhysics;
class CollideTrack;
class Mission;
class MissionPage;
class MissionInterface;
class MissionDataInterface;
class MissionEvent;
class Background;
class Home;
class HomeHelp;
class SpiderPoison;
class Bullet;
class Land;
class Spider;
class Score;
class Stretch;
class CoolRun : public Layer, public GameController
{
public:
    enum class GameState
    {
        HOME,
        ATTACK,
        RUN,
        RUNNING,
        BOSS
    };
public:
    CoolRun();
    ~CoolRun();
    
    static Scene* createScene(Mission* mission);
    
    virtual bool init();
    virtual void update(float delta);
    void gameMain(float delta);
    virtual void onEnter();
    virtual void onEnterTransitionDidFinish();
    virtual void onExitTransitionDidStart();
    virtual void onExit();
    
    bool init(Mission* mission);
    static CoolRun* create(Mission* mission);
    CREATE_FUNC(CoolRun);
    
    void setMission(Mission* mission);
    
    void finishAddImage(Texture2D* texture);
    void lazyInit();
    
    bool onTouchBegan(Touch* touch, Event* event);
    void onTouchMoved(Touch* touch, Event* event);
    void onTouchEnded(Touch* touch, Event* event);
    
    void directionCollideTrack();
    void simpleCollideTrack();
    void bulletCollideTrack();
    
    void backGroundUpdate(float delta);
    void totalStretchUpdate(float delta);
    void pageStretchUpdate(float delta);
    void loadNextPage(bool isFirstPage = false);
    void checkEvents();
    
    void checkObjectsOut();
    void checkObjectsDestoryed();
    
    void SkillBtnCallback(Ref* _btn, MYButton::TouchEventType _type);
    void JumpBtnCallback(Ref* _btn, MYButton::TouchEventType _type);
    void PacBtnCallback(Ref* _btn, MYButton::TouchEventType _type);
    
    void addRunner();
    void addSpiderAndHelp();
    void showBossWarning();
    void showBossWarningEnd();
    void addBoss();
    
    void hideController();
    void showController();
    
    void actionCallback();
    void doorCloseCallback();
    
    void setVelocity(int v);
    int getVelocity() { return m_velocity; }
    
    //Bullet
    void addBullet(Bullet* bullet, const Vec2& startPos, const Vec2& endPos, float duration);
    void addBullet(Bullet* bullet);
    
    //Spider
    void addSpider(Spider* spider);
    
    //popLayer
    void addPauseMenu();
    void addOverMenu();
    void removePauseMenu();
    void removeOverMenu();
    
    void ResumeBtnCallback(Ref* _btn, MYButton::TouchEventType _type);
    void GiveUpBtnCallback(Ref* _btn, MYButton::TouchEventType _type);
    void HelpMeBtnCallback(Ref* _btn, MYButton::TouchEventType _type);
    
    //GameController
    void pause();
    void resume();
    void dead(Runner* runner);
    void addScore(int score);
    void addStretch(int stretch);
    void loadNextMission();
    virtual void addCoin(int num);
    virtual void destory(PhysicNode* _node);
    
    //Item
    void spareRunner(Runner* runner);
    void buildLand(Runner* runner);
    Runner* getLastPosRunner();
    Land* getRunnerPosLand(Runner* runner);
    Land* getMinPosLand();
    Land* getNextLand(Land* stone);
    Land* getLand(const Vec2& pos);
    Land* getNextLand(const Vec2& pos, float space);
    
    void startFly();
    void endFly();
    
private:
    void _eventHappened(MissionEvent* _event);
    void _checkObjectsOut(__Array* _nodes);
    void _checkObjectsDestoryed(__Array* _nodes);
    void _addChildren(__Array* _nodes, bool isFirstPage);
    
    void _loadMissionDataInterface(MissionDataInterface* _missionDataInterface, bool isFirstPage = false);
    void _loadMissionInterface(MissionInterface* _missionInterface, bool isFirstPage = false);
    void _loadMissionEvents(__Array* _events);
    
    
    void _setVelocity(__Array* _nodes, int vc);
    void _smoothLand();
private:
    GameState m_gameState;
    
    int m_resCacheCount;
    int m_velocity;
    
    Background *m_awayBG;
    Background *m_farBG;
    Background *m_midBG;
    
    __Array *m_runners;
    
    MYButton *m_pacBtn;
    MYButton *m_jumpBtn;
    MYButton *m_atkBtn;
    
    bool b_isPaused;
    
    GravityPhysics *m_gPhysics;
    CollideTrack *m_cTrack;
    
    __Array *m_gravityCollideObjs;
    __Array *m_dirCollideObjs;
    __Array *m_simpleCollideObjs;
    __Array *m_bulletObjs;
    
    Mission  *m_mission;
    MissionPage  *m_nextPage; 
    MissionPage *m_curPage;
    
    __Array *m_events;
    
    Label *m_stretchLab;
    Label *m_pageSLab;
    float m_totalStretch; //总路程
    int m_totalStretchForInt; //总路程
    float m_pageStretch; //屏路程
    
    Home* m_home;
    HomeHelp* m_help;
    SpiderPoison* m_enemy;
    
    Score* m_scoreView;
    int m_score;
    Stretch* m_stretchView;
    int m_stretch;
};

#endif /* defined(__CoolRun__CoolRunScene__) */
