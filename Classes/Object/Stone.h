//
//  Stone.h
//  CoolRun
//
//  Created by ManYou on 14-8-8.
//
//

#ifndef __CoolRun__Stone__
#define __CoolRun__Stone__

#include "cocos2d.h"
#include "Land.h"

USING_NS_CC;
using namespace std;
class Stone : public Land
{
public:
    Stone();
    ~Stone();
    virtual bool init();
    CREATE_FUNC(Stone);
    
    virtual void onEnter() override;
    virtual void onExit() override;
    
    virtual void setContentSize(const Size& _size) override;
    virtual void setLand(bool flag) override;
    virtual void setLeftIgnore(bool flag) override;
    virtual void setRightIgnore(bool flag) override;
    
    static Stone* create(rapidjson::Value& _value);
    
private:
    
    void clearStone();
    
    void buildStoneBase(const string& leftFrameName, float leftSize, const string& midFrameName, float midSize, const string& rightFrameName, float rightSize);
    void buildStoneWithScale(const string& leftFrameName, float leftSize, const string& midFrameName, float midSize, const string& rightFrameName, float rightSize);
    void buildStoneWithShare(const string& leftFrameName, float leftSize, const string& midFrameName, float midSize, const string& rightFrameName, float rightSize);
    void buildStoneWithShare(const string& frameName, float size);
private:
    Sprite* m_left;
    Sprite* m_right;
    __Array* m_mids;
};

#endif /* defined(__CoolRun__Stone__) */
