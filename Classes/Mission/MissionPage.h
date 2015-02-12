//
//  MissionPage.h
//  CoolRun
//
//  Created by ManYou on 14-8-19.
//
//

#ifndef __CoolRun__MissionPage__
#define __CoolRun__MissionPage__

#include "cocos2d.h"
#include "JsonHelp.h"
#include "MissionInterface.h"
#include "MissionEvent.h"

USING_NS_CC;

class MissionPage : public Ref
{
public:
    MissionPage();
    ~MissionPage();
    virtual bool init();
    CREATE_FUNC(MissionPage);
    static MissionPage* create(rapidjson::Value& _value);
    virtual void loadJson(rapidjson::Value& _value);
    
    MissionInterface* getMissionInterface() { return m_interface; }
    
    __Array* getEvents() { return m_events; }
    
    bool isLastPage() { return b_isLastPage; }
    void setLastPage(bool flag) { b_isLastPage = flag; }
private:
    MissionInterface* m_interface;
    __Array* m_events;
    
    bool b_isLastPage;
};

#endif /* defined(__CoolRun__MissionPage__) */
