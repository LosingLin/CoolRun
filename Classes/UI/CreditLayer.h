//
//  CreditLayer.h
//  CoolRun
//
//  Created by ManYou on 15/5/19.
//
//

#ifndef __CoolRun__CreditLayer__
#define __CoolRun__CreditLayer__

#include "cocos2d.h"
#include "MYButton.h"

USING_NS_CC;
class NormalFrame;
class CreditLayer : public Layer
{
public:
    CreditLayer();
    ~CreditLayer();
    
    virtual bool init() override;
    CREATE_FUNC(CreditLayer);
    
    void addCloseCallback(MYButton::MYButtonCallback _callback) { m_callback = _callback; };
    void closeBtnCallback(Ref* _ref, MYButton::TouchEventType _type);
private:
    NormalFrame* m_bgFrame;
    MYButton::MYButtonCallback m_callback;
};

#endif /* defined(__CoolRun__CreditLayer__) */
