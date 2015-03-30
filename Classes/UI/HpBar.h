//
//  HpBar.h
//  CoolRun
//
//  Created by ManYou on 15/2/24.
//
//

#ifndef __CoolRun__HpBar__
#define __CoolRun__HpBar__

#include "cocos2d.h"

USING_NS_CC;

class HpBar : public Node
{
public:
    HpBar();
    ~HpBar();
    
    virtual bool init() override;
    bool init(float totalHp);
    static HpBar* create(float totalHp);
    
    
    void setCurrentHp(float hp);
    void barUpdate();
    void delayUpdate();
    void check();
    
    float getCurrentHp() { return m_currentHp; }
private:
    float m_totalHp;
    float m_currentHp;
    ProgressTimer* m_bg01;
    ProgressTimer* m_bg02;
};

#endif /* defined(__CoolRun__HpBar__) */
