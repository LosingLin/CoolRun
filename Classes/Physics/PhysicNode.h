//
//  PhysicNode.h
//  CoolRun
//
//  Created by ManYou on 14-8-8.
//
//

#ifndef __CoolRun__PhysicNode__
#define __CoolRun__PhysicNode__

#include "cocos2d.h"
#include "Base.h"
#include "CollideTrack.h"
#include "CollideTrackListener.h"
#include "JsonHelp.h"
#include "PhysicNodeFactory.h"

USING_NS_CC;

class PhysicNode : public DrawableNode, public CollideTrackListener
{
public:
    PhysicNode();
    ~PhysicNode();
    
    virtual bool init();
    CREATE_FUNC(PhysicNode);
    
    virtual void loadJson(rapidjson::Value& _value);
    virtual void saveData(string* buffer);
    
    
    void setPhysicNodeType(PhysicNodeType type) { m_type = type; }
    PhysicNodeType getPhysicType() { return m_type; }
    
    void setXV(float xv) { m_velocityX = xv; }
    float getXV() { return m_velocityX; }
    void setYV(float yv) { m_velocityY = yv; }
    float getYV() { return m_velocityY; }
    void setXA(float xa) { m_aX = xa; }
    float getXA() { return m_aX; }
    void setYA(float ya) { m_aY = ya; }
    float getYA() { return m_aY; }
    
    bool isGravityEffect() { return b_isGravityEffect; }
    void setGravityEffect(bool flag) { b_isGravityEffect = flag; }
    
    bool isCollideEffect() { return b_isCollideEffect; }
    void setCollideEffect(bool flag) { b_isCollideEffect = flag; }
    
    bool isVelocityIgnore() { return b_isVelocityIgnore; }
    void setVelocityIgnore(bool flag) { b_isVelocityIgnore = flag; }
    
    bool isDestoryed() { return b_isDestoryed; }
    void setDestoryed(bool flag) { b_isDestoryed = flag; }
    
    bool isScreenPos() { return b_isScreenPos; }
    void setScreenPos(bool flag) { b_isScreenPos = flag; }
    
    float getAlignX() const { return m_align_x; }
    float getAlignY() const { return m_align_y; }
    void setAlignX(float alx);
    void setAlignY(float aly);
    
    void setForEditor(bool flag) { b_isForEditor = flag; }
    bool isForEditor() { return b_isForEditor; }
    
//    virtual void setPosition(const Vec2 &position) override;
//    virtual const Vec2& getPosition() const override;
    
    CollideType getCollideType() { return m_collideType; }
    void setCollideType(CollideType type) { m_collideType = type; }
    
    const Rect getCollideRect() { return m_collideRect; }
    void setCollideRect(const Rect& rect) { m_collideRect = rect; }
    
    virtual void CollideTrackListener_CollideOnce(CollideDirection direction, PhysicNode *node) {};
    virtual void CollideTrackListener_CollideAll(CollideDirection direction) {};
    
    virtual void beCllided() {};
    
    void debugShow();
    
private:
    float m_velocityX; //x 方向速度
    float m_velocityY; //y 方向速度
    float m_aX;     //x 方向加速度
    float m_aY;     //y 方向加速度
    bool b_isScreenPos; //是否是屏幕级位置
    float m_align_x; //相对屏幕宽的位置
    float m_align_y; //相对屏幕高的位置
    
    bool b_isGravityEffect; //是否受重力影响
    bool b_isVelocityIgnore; //是否忽略速度
    
    bool b_isCollideEffect; //是否受碰撞区域影响
    CollideType m_collideType; //碰撞类型
    Rect m_collideRect; //碰撞区域
    
    bool b_isDestoryed; //是否被销毁
    
    bool b_isForEditor; //是否用于编辑器
    PhysicNodeType m_type; //类型
//    Vec2 m_positionPN;
};

#endif /* defined(__CoolRun__PhysicNode__) */
