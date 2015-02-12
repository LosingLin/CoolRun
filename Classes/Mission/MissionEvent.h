//
//  MissionEvent.h
//  CoolRun
//
//  Created by ManYou on 14-10-3.
//
//

#ifndef __CoolRun__MissionEvent__
#define __CoolRun__MissionEvent__

#include "cocos2d.h"
#include "JsonHelp.h"
#include "MissionInterface.h"

USING_NS_CC;

class MissionEvent : public Ref
{
public:
    MissionEvent();
    ~MissionEvent();
    virtual bool init();
    CREATE_FUNC(MissionEvent);
    
    static MissionEvent* create(rapidjson::Value& _value);
    
    virtual void loadJson(rapidjson::Value& _value);
    
    MissionInterface* getMissionInterface() { return m_interface; }
    
    float getStartPageStretch() { return m_startPageStretch; }
private:
    MissionInterface* m_interface;
    float m_startPageStretch;
};

#endif /* defined(__CoolRun__MissionEvent__) */
