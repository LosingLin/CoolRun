//
//  LogoScene.h
//  CoolRun
//
//  Created by ManYou on 15/6/12.
//
//

#ifndef __CoolRun__LogoScene__
#define __CoolRun__LogoScene__

#include "cocos2d.h"


USING_NS_CC;

class LogoLayer : public Layer
{
public:
    LogoLayer();
    ~LogoLayer();
    
    virtual bool init();
    CREATE_FUNC(LogoLayer);
    
    virtual void onEnter() override;
    virtual void onEnterTransitionDidFinish() override;
    
    static Scene* createScene();
    
    void showLogoEnd();
private:
    
};

#endif /* defined(__CoolRun__LogoScene__) */
