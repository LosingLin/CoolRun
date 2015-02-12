//
//  Home.h
//  CoolRun
//
//  Created by ManYou on 14/11/6.
//
//

#ifndef __CoolRun__Home__
#define __CoolRun__Home__

#include "cocos2d.h"
#include "Land.h"

USING_NS_CC;
class Home : public Land
{
public:
    Home();
    ~Home();
    virtual bool init();
    CREATE_FUNC(Home);
    
    void openDoor();
    void closeDoor();
private:
    Sprite* m_door;
};

#endif /* defined(__CoolRun__Home__) */
