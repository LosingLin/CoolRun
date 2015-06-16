//
//  ThirdPartyManager.h
//  CoolRun
//
//  Created by ManYou on 15/6/14.
//
//

#ifndef __CoolRun__ThirdPartyManager__
#define __CoolRun__ThirdPartyManager__

#include "cocos2d.h"

USING_NS_CC;
class ReviveMenu;
class ThirdPartyManager : public Ref
{
public:
    static ThirdPartyManager* getInstance();
    static void purgeInstance();
    
    void setReviveMenu(ReviveMenu* _menu) { m_reviveMenu = _menu; }
    ReviveMenu* getReviveMenu();
private:
    ThirdPartyManager();
    ~ThirdPartyManager();
    
    static ThirdPartyManager* m_instance;
    ReviveMenu* m_reviveMenu;
};

#endif /* defined(__CoolRun__ThirdPartyManager__) */
