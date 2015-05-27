//
//  SelectLanguageLayer.h
//  CoolRun
//
//  Created by ManYou on 15/5/18.
//
//

#ifndef __CoolRun__SelectLanguageLayer__
#define __CoolRun__SelectLanguageLayer__

#include "cocos2d.h"
#include "MYButton.h"

USING_NS_CC;
class NormalFrame;
class SelectLanguageLayer : public Layer
{
public:
    SelectLanguageLayer();
    ~SelectLanguageLayer();
    
    virtual bool init() override;
    CREATE_FUNC(SelectLanguageLayer);
    
    void addCloseCallback(MYButton::MYButtonCallback _callback) { m_callback = _callback; };
    void selectDoneCallback(Ref* _ref, MYButton::TouchEventType _type);
    void closeBtnCallback(Ref* _ref, MYButton::TouchEventType _type);
private:
    NormalFrame* m_bgFrame;
    MYButton* m_enBtn;
    MYButton* m_chBtn;
    MYButton::MYButtonCallback m_callback;
};

#endif /* defined(__CoolRun__SelectLanguageLayer__) */
