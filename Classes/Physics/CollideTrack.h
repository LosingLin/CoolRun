//
//  CollideTrack.h
//  CoolRun
//
//  Created by ManYou on 14-8-11.
//
//

#ifndef __CoolRun__CollideTrack__
#define __CoolRun__CollideTrack__

#include "cocos2d.h"

USING_NS_CC;
enum CollideType
{
    kCollideTypeUnknown = 0,
    kCollideTypeDirection = 1, //上下左右方向，较精细的碰撞检测
    kCollideTypeSimple = 2, //碰撞和不碰撞，简单的碰撞检测
    kCollideTypeBullet = 3, //子弹
};
enum CollideDirection
{
    kCollideDirectionUnknown = 0,
    kCollideDirectionUp = 1,
    kCollideDirectionDown = 2,
    kCollideDirectionLeft = 3,
    kCollideDirectionRight = 4,
    kCollideDirectionMiss = 5,
    kCollideDirectionTotal = 6,
};
namespace CollideTrackHelp
{
    //这里返回的方向是相对于rect1来说的 （方向参照物是rect1）
    CollideDirection trackCollideDirection(const Rect& rect1, const Rect& rect2);
    
    bool trackCollide(const Rect& rect1, const Rect& rect2);
    
    //这里的direction也是相对rect1来说的 （方向参照物是rect1）
    float trackDistance(const Rect& rect1, const Rect& rect2, CollideDirection direction);
    
    //检测是否靠近右边
    bool isNearRight(const Rect& rect1, const Rect& rect2, float distance, bool ignoreY = false);
};


class PhysicNode;
class Runner;
class CollideTrackListener;
class CollideTrack : public Ref
{
public:
    CollideTrack();
    ~CollideTrack();
    
    virtual bool init();
    CREATE_FUNC(CollideTrack);
    
    void addPhysicNode(PhysicNode *pNode);
    void removePhysicNode(PhysicNode *pNode);
    
    void collideTrackUpdate();
    void collideTrackPhysicNode(PhysicNode *node);
    
    void setCollideTrackListener(CollideTrackListener *listener);

    //这里返回的方向是相对于rect1来说的 （方向参照物是rect1）
    CollideDirection trackCollideDirection(const Rect& rect1, const Rect& rect2);
    
    bool trackCollide(const Rect& rect1, const Rect& rect2);
private:
    __Array *m_physicNodes;
    
    CollideTrackListener *m_ctListener;
};

#endif /* defined(__CoolRun__CollideTrack__) */
