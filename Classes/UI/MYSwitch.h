//
//  MYSwitch.h
//  CoolRun
//
//  Created by ManYou on 15/5/16.
//
//

#ifndef __CoolRun__MYSwitch__
#define __CoolRun__MYSwitch__

#include "cocos2d.h"
#include "MYButton.h"

USING_NS_CC;

class MYSwitch : public Node
{
public:
    enum class MYSwitchStatus
    {
        ON,
        OFF
    };
    typedef std::function<void(Ref*, MYSwitch::MYSwitchStatus)> MYSwitchCallback;
public:
    MYSwitch();
    ~MYSwitch();
    
    virtual bool init() override;
    bool initWithFrameName(const char* onspn, const char* offspn);
    static MYSwitch* createWithFrameName(const char* onspn, const char* offspn);
    
    void setONSpriteWithFrameName(const char* spfn);
    void setOFFSpriteWithFrameName(const char* spfn);
    void setStatus(MYSwitchStatus status);
    
    void addSwitchCallback(MYSwitchCallback callback);
    void innerBtnCallback(Ref* _ref, MYButton::TouchEventType _type);
private:
    Sprite* m_onSp;
    Sprite* m_offSp;
    MYButton* m_innerBtn;
    MYSwitchStatus m_status;
    MYSwitchCallback m_callback;
};

#endif /* defined(__CoolRun__MYSwitch__) */
