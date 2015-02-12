//
//  MissionCollection.h
//  CoolRun
//
//  Created by ManYou on 14-10-7.
//
//

#ifndef __CoolRun__MissionCollection__
#define __CoolRun__MissionCollection__

#include "cocos2d.h"
#include "MissionDataInterface.h"

USING_NS_CC;

class MissionCollection : public MissionDataInterface
{
public:
    MissionCollection();
    ~MissionCollection();
    virtual bool init() override;
    CREATE_FUNC(MissionCollection);
    static MissionCollection* create(rapidjson::Value& _value);
    virtual void loadJson(rapidjson::Value& _value) override;
    
    __Array* getCollections() { return m_collections; }
    void setCollections(__Array* cols);
private:
    void _fuckCollecions();
private:
    __Array* m_collections;
};

#endif /* defined(__CoolRun__MissionCollection__) */
