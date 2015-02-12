//
//  MissionDataInterface.h
//  CoolRun
//
//  Created by ManYou on 14-10-7.
//
//

#ifndef __CoolRun__MissionDataInterface__
#define __CoolRun__MissionDataInterface__

#include "cocos2d.h"
#include "JsonHelp.h"

USING_NS_CC;

class MissionDataInterface : public Ref
{
public:
    MissionDataInterface();
    ~MissionDataInterface();
    virtual bool init();
    virtual void loadJson(rapidjson::Value& _value){};
    
    __Array* getDirectionCollideObjects() { return m_dirColObjs; }
    __Array* getSimpleCollideObjects() { return m_simpleColObjs; }
    __Array* getBulletCollideObjects() { return m_bulletColObjs; }
    
protected:
    __Array *m_dirColObjs;
    __Array *m_simpleColObjs;
    __Array *m_bulletColObjs;
};

#endif /* defined(__CoolRun__MissionDataInterface__) */
