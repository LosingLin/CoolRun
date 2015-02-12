//
//  VillageScene.h
//  CoolRun
//
//  Created by ManYou on 14-9-5.
//
//

#ifndef __CoolRun__VillageScene__
#define __CoolRun__VillageScene__

#include "cocos2d.h"
#include "MYButton.h"

USING_NS_CC;

class Runner;
class Villager;
class VillageLayer : public Layer
{
public:
    VillageLayer();
    ~VillageLayer();
    virtual bool init();
    
    virtual void onEnter() override;
    virtual void onExit() override;
    
    CREATE_FUNC(VillageLayer);
    static Scene* createScene();
    
    void villagerTouchCallback(Ref* _ref, MYButton::TouchEventType _type, Villager* _villager);
    
    void runnerMove(const Vec2& _loc, const std::function<void()> &func);
    void runnerMoveEnd();
    void runnerTalk(Villager* _villager);
    
    bool onTouchBegan(Touch* touch, Event* event);
    void onTouchMoved(Touch* touch, Event* event);
    void onTouchEnded(Touch* touch, Event* event);
    
private:
    Runner* m_runner;
};

#endif /* defined(__CoolRun__VillageScene__) */
