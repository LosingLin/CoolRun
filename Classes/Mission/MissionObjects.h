//
//  MissionObjects.h
//  CoolRun
//
//  Created by ManYou on 14-10-3.
//
//

#ifndef __CoolRun__MissionObjects__
#define __CoolRun__MissionObjects__

#include "cocos2d.h"
#include "MissionDataInterface.h"

USING_NS_CC;

class MissionObjects : public MissionDataInterface
{
public:
    MissionObjects();
    ~MissionObjects();
    virtual bool init() override;
    CREATE_FUNC(MissionObjects);
    static MissionObjects* create(rapidjson::Value& _value);
    virtual void loadJson(rapidjson::Value& _value) override;
};

#endif /* defined(__CoolRun__MissionObjects__) */
