//
//  Collection.h
//  CoolRun
//
//  Created by ManYou on 14-10-7.
//
//

#ifndef __CoolRun__Collection__
#define __CoolRun__Collection__

#include "cocos2d.h"
#include "JsonHelp.h"

USING_NS_CC;

class PhysicNode;
class Collection : public Ref
{
public:
    Collection();
    ~Collection();
    virtual bool init();
    CREATE_FUNC(Collection);
    
    virtual void loadJson(rapidjson::Value& _value);
    virtual void saveData(string* buffer);
    
    void setJsonStr(const string& json);
    
    __Array* getCollection() { return m_collection; }
    
    PhysicNode* createEditorPhysicNode();
    
    void setCmIndex(int index) { m_cmIndex = index; }
    int getCmIndex() { return m_cmIndex; }
    
    void setIncX(float inc) { m_incX = inc; }
    int getIncX() { return m_incX; }
    
    void setIncY(float inc) { m_incY = inc; }
    int getIncY() { return m_incY; }
    
    static int getMatrixTotalNum();
private:
    string* m_jsonStr;
    __Array* m_collection;
    int m_cmIndex;
    float m_incX;
    float m_incY;
};

#endif /* defined(__CoolRun__Collection__) */
