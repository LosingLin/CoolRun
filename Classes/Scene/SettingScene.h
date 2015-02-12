//
//  SettingScene.h
//  CoolRun
//
//  Created by ManYou on 14-9-5.
//
//

#ifndef __CoolRun__SettingScene__
#define __CoolRun__SettingScene__

#include "cocos2d.h"

USING_NS_CC;

class SettingLayer : public Layer
{
public:
    SettingLayer();
    ~SettingLayer();
    virtual bool init();
    CREATE_FUNC(SettingLayer);
    
    static Scene* createScene();
};

#endif /* defined(__CoolRun__SettingScene__) */
