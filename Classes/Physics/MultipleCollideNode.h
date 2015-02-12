//
//  MultipleCollideNode.h
//  CoolRun
//
//  Created by ManYou on 14/10/27.
//
//

#ifndef __CoolRun__MultipleCollideNode__
#define __CoolRun__MultipleCollideNode__

#include "cocos2d.h"
#include "CollideNode.h"
#include "JsonHelp.h"
#include "CollideRect.h"

USING_NS_CC;
/*
 继承自CollideNode
 处理一些比较复杂的碰撞需求
 像一只蜘蛛的头不能踩， 肚子则可以踩..
 */
class MultipleCollideNode : public CollideNode
{
public:
    MultipleCollideNode();
    ~MultipleCollideNode();
    
    virtual bool init() override;
    CREATE_FUNC(MultipleCollideNode);
    
    virtual void loadJson(rapidjson::Value& _value) override;
    
    __Array* getMultiRects() { return m_multiRects; }
    const Rect getMultiRect(int index);
private:
    int m_rectIndex;
    __Array* m_multiRects;
    
};

#endif /* defined(__CoolRun__MultipleCollideNode__) */
