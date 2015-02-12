//
//  MissionInterface.h
//  CoolRun
//
//  Created by ManYou on 14-10-7.
//
//

#ifndef __CoolRun__MissionInterface__
#define __CoolRun__MissionInterface__

#include "cocos2d.h"
#include "JsonHelp.h"

USING_NS_CC;
class MissionObjects;
class MissionCollection;
class MissionInterface : public Ref
{
public:
    MissionInterface();
    ~MissionInterface();
    
    virtual bool init();
    CREATE_FUNC(MissionInterface);
    
    virtual void loadJson(rapidjson::Value& _value);
    
    MissionObjects* getMissionObjects() { return m_objs; }
    MissionCollection* getMissionCollection() { return m_collection; }
    
private:
    MissionObjects* m_objs;
    MissionCollection* m_collection;
};

#endif /* defined(__CoolRun__MissionInterface__) */
