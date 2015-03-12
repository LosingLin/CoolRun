//
//  MYScene.h
//  CoolRun
//
//  Created by ManYou on 15/3/10.
//
//

#ifndef __CoolRun__MYScene__
#define __CoolRun__MYScene__

#include "cocos2d.h"

USING_NS_CC;

class MYScene : public Scene
{
public:
    MYScene();
    ~MYScene();
    
    CREATE_FUNC(MYScene);
    
    virtual void pause();
    virtual void resume();
    
    std::function<void(void)> scenePause;
    std::function<void(void)> sceneResume;
};

#endif /* defined(__CoolRun__MYScene__) */
