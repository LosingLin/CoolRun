//
//  ResourceManager.h
//  CoolRun
//
//  Created by ManYou on 15/6/16.
//
//

#ifndef __CoolRun__ResourceManager__
#define __CoolRun__ResourceManager__

#include "cocos2d.h"

USING_NS_CC;
using namespace std;

class ResourceManager : public Ref
{
public:
    enum class ResourceType
    {
        HD,
        SD
    };
    static ResourceManager* getInstance();
    static void purgeInstance();
    
    void setResourceType(ResourceType _type) { m_rType = _type; }
    ResourceType getResourceType() { return m_rType; }
    
    const string getPlistRes(const string& _name);
    const string getPngRes(const string& _name);
    const string getFntRes(const string& _name);
    
    //source
    void removeBigSource();
    void addBigSource();
private:
    string getExtesion();
private:
    ResourceManager();
    ~ResourceManager();
    
    static ResourceManager* m_instance;
    static ResourceType m_rType;
};

#endif /* defined(__CoolRun__ResourceManager__) */
