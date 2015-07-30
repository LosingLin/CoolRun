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
#include "MYKeyBoardLayer.h"
#include "GameController.h"
#include "MYButton.h"
#include "PowerIcon.h"

#define ZORDER_STONE        0
#define ZORDER_BOX          5
#define ZORDER_COIN         6
#define ZORDER_SAW          6
#define ZORDER_JADE         7
#define ZORDER_ANIMAL       7
#define ZORDER_BULLET       8
#define ZORDER_ITEM         9
#define ZORDER_RUNNER       10


#define ZORDER_LEAVES       18
#define ZORDER_POWERBAR     19
#define ZORDER_WARNING      19
#define ZORDER_HEADMENU     20

#define ZORDER_POPVIEW      200
#define ZORDER_FRESHGUIDE   199

#define ZORDER_SYS          1000

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
class JadeView;
class HpBar;
class Leaves;
class BackgroundAudio;
class PowerIconBar;
class PowerIcon;
class Clouds;
class BoxData;
class CoolRun : public MYKeyBoardLayer, public GameController
{
public:
    enum class RunType
    {
        NORMAL,
        EDITOR
    };
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
    
    static Scene* createScene(Mission* mission, RunType _type = RunType::NORMAL);
    
    virtual bool init();
    virtual void update(float delta);
    void gameMain(float delta);
    void setUpdatING(bool flag);
    bool isUpdatING() { return b_isUpdatING; }
    virtual void onEnter();
    virtual void onEnterTransitionDidFinish();
    virtual void onExitTransitionDidStart();
    virtual void onExit();
    
    bool init(Mission* mission);
    static CoolRun* create(Mission* mission);
    CREATE_FUNC(CoolRun);
    
    void setRunType(RunType _type) { m_runType = _type; };
    RunType getRunType() { return m_runType; }
    void setMission(Mission* mission);
    
    void finishAddImage(Texture2D* texture);
    void lazyInit();
    
    bool onTouchBegan(Touch* touch, Event* event);
    void onTouchMoved(Touch* touch, Event* event);
    void onTouchEnded(Touch* touch, Event* event);
    
    void directionCollideTrack();
    void simpleCollideTrack();
    void bulletCollideTrack();
    void runnerPositionTrack();
    
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
    
    void addRunner(bool isReborn=true);
    void addSpiderAndHelp();
    void showBossWarning();
    void showBossWarningEnd();
    void addBoss();
    
    void hideController();
    void showController();
    void hideInfoView();
    void showInfoView();
    
    void actionCallback();
    void doorCloseCallback();
    
    //guide
    void showGuide();
    void hideGuide(Ref* _btn, MYButton::TouchEventType _type, Node* _guide);
    
    void setVelocity(int v, bool cloud=true);
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
    void addReviveMenu();
    void reviveMenu_GameOverCallback(Ref* _btn, MYButton::TouchEventType _type);
    void reviveMenu_ReviveCallback(Ref* _btn, MYButton::TouchEventType _type);
    void gameOverMenu_RetryCallback(Ref* _btn, MYButton::TouchEventType _type);
    
    void ResumeBtnCallback(Ref* _btn, MYButton::TouchEventType _type);
    void GiveUpBtnCallback(Ref* _btn, MYButton::TouchEventType _type);
    void HelpMeBtnCallback(Ref* _btn, MYButton::TouchEventType _type);
    
    //GameController
    void pause();
    void resume();
    void dead(Runner* runner);
    void addScore(int score);
    void addStretch(int stretch);
    void addJade(int jade);
    BoxData* openBox();
    void addBoxData(BoxData* _data);
    void showScore(int score, const Vec2& pos);
    void _showScoreEnd(Node* node);
    void loadNextMission();
    virtual void addCoin(int num);
    virtual void destory(PhysicNode* _node);
    void addBossHpBar(HpBar* bar);
    void removeBossHpBar(HpBar* bar);
    void addPowerIcon(PowerIcon::PowerType _type);
    void removePowerIcon(PowerIcon::PowerType _type);
    void updatePowerIcon(PowerIcon::PowerType _type, float _percentage);
    
    //Item
    void addRandomItem();
    
    void spareRunner(Runner* runner);
    void buildLand(Runner* runner, int trackSpace = 400);
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
    RunType m_runType;
    GameState m_gameState;
    
    int m_resCacheCount;
    int m_backUpVelocity;
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
    JadeView* m_jadeView;
    int m_jadeNum;
    
    
    Leaves* m_leaves;
    Clouds* m_clouds;
    
    int m_missionIndex;
    
    BackgroundAudio* m_bgAudio;
    PowerIconBar* m_powerBar;
    
    int m_reviveTimes;
    
    bool b_isUpdatING;
};

#endif /* defined(__CoolRun__CoolRunScene__) */
