//
//  FreshGuideScene.h
//  CoolRun
//
//  Created by ManYou on 15/4/27.
//
//

#ifndef __CoolRun__FreshGuideScene__
#define __CoolRun__FreshGuideScene__

#include "cocos2d.h"
#include "MYButton.h"

USING_NS_CC;

class FreshGuideLayer : public Layer
{
public:
    FreshGuideLayer();
    ~FreshGuideLayer();
    virtual bool init();
    CREATE_FUNC(FreshGuideLayer);
    
    static Scene* createScene();
    
    virtual bool onTouchBegan(Touch *touch, Event *unusedEvent);
    virtual void onTouchMoved(Touch *touch, Event *unusedEvent);
    virtual void onTouchEnded(Touch *touch, Event *unusedEvent);
    virtual void onTouchCancelled(Touch *touch, Event *unusedEvent);
    
    void closeBtnCallback(Ref* _ref, MYButton::TouchEventType _type);
    void setCloseCallback(MYButton::MYButtonCallback callback);
private:
    MYButton* m_closeBtn;
};

#endif /* defined(__CoolRun__FreshGuideScene__) */
