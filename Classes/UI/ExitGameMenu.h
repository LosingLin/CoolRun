//
//  ExitGameMenu.h
//  CoolRun
//
//  Created by ManYou on 15/6/13.
//
//

#ifndef __CoolRun__ExitGameMenu__
#define __CoolRun__ExitGameMenu__

#include "PopViewLayer.h"
#include "extensions/cocos-ext.h"
#include "MYButton.h"
#include "CoolRunScene.h"

USING_NS_CC_EXT;

class ExitGameMenu : public PopViewLayer
{
public:
    ExitGameMenu();
    ~ExitGameMenu();
    
    virtual bool init() override;
    CREATE_FUNC(ExitGameMenu);
    
    virtual void onEnter() override;
    
    void confirmCallback(Ref* _ref, MYButton::TouchEventType _type);
    void cancelCallback(Ref* _ref, MYButton::TouchEventType _type);

private:
    MYButton* m_confirmBtn;
    MYButton* m_cancelBtn;
    bool b_isPaused;
};

#endif /* defined(__CoolRun__ExitGameMenu__) */
