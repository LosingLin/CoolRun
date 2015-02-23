//
//  PopViewLayer.h
//  CoolRun
//
//  Created by ManYou on 15/2/13.
//
//

#ifndef __CoolRun__PopViewLayer__
#define __CoolRun__PopViewLayer__

#include "cocos2d.h"

USING_NS_CC;

class PopViewLayer : public Layer
{
public:
    PopViewLayer();
    ~PopViewLayer();
    
    virtual bool init() override;
    CREATE_FUNC(PopViewLayer);
    
    virtual bool onTouchBegan(Touch *touch, Event *unusedEvent);
    virtual void onTouchMoved(Touch *touch, Event *unusedEvent);
    virtual void onTouchEnded(Touch *touch, Event *unusedEvent);
    virtual void onTouchCancelled(Touch *touch, Event *unusedEvent);
};

#endif /* defined(__CoolRun__PopViewLayer__) */
