//
//  ReviveMenu.h
//  CoolRun
//
//  Created by ManYou on 15/6/2.
//
//

#ifndef __CoolRun__ReviveMenu__
#define __CoolRun__ReviveMenu__

#include "PopViewLayer.h"
#include "extensions/cocos-ext.h"
#include "MYButton.h"

USING_NS_CC_EXT;

class ADLoadingLayer;
class ReviveMenu : public PopViewLayer
{
public:
    ReviveMenu();
    ~ReviveMenu();
    
    virtual bool init() override;
    CREATE_FUNC(ReviveMenu);
    
    virtual void onEnter() override;
    
    void addGameOverCallback(MYButton::MYButtonCallback call) { m_gameOverCallback = call; };
    void addReviveCallback(MYButton::MYButtonCallback call) { m_reviveCallback = call; }
    
    void watchVideoCallback(Ref* _ref, MYButton::TouchEventType _type);
    void progressDone();

    void showAdLoading();
    void AdLoadingDone(bool needResume = true);
    void revive();
private:
    MYButton* m_videoBtn;
    MYButton::MYButtonCallback m_gameOverCallback;
    MYButton::MYButtonCallback m_reviveCallback;
    ProgressTimer* m_proTimer;
    ADLoadingLayer* m_adLoadingLayer;
};

#endif /* defined(__CoolRun__ReviveMenu__) */
