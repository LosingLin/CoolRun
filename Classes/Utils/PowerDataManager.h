//
//  PowerDataManager.h
//  CoolRun
//
//  Created by ManYou on 15/6/24.
//
//

#ifndef __CoolRun__PowerDataManager__
#define __CoolRun__PowerDataManager__

#include "cocos2d.h"
#include "JsonHelp.h"
#include "Base.h"

USING_NS_CC;

class PowerDataManager : public Ref
{
public:
    static PowerDataManager* getInstance();
    static void purgeInstance();
    bool init();
    
    int getMaxLevel(PhysicNodeType type);
    float getNextLevelEffectAdd(PhysicNodeType type);
    int getNextLevelJadeExpend(PhysicNodeType type);
    
private:
    const string _findInfoValueTypeKey(PhysicNodeType type);
    void _findInfoValue(PhysicNodeType type, rapidjson::Value& _value);
private:
    PowerDataManager();
    ~PowerDataManager();
    
    static PowerDataManager* m_instance;
    static rapidjson::Document* m_doc;
};

#endif /* defined(__CoolRun__PowerDataManager__) */
