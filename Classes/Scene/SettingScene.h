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
#include "MYKeyBoardLayer.h"
#include "extensions/cocos-ext.h"
#include "MYButton.h"
#include "MYSwitch.h"

USING_NS_CC;
USING_NS_CC_EXT;
class PopViewLayer;
class NormalFrame;
class SettingLayer : public MYKeyBoardLayer
{
public:
    SettingLayer();
    ~SettingLayer();
    virtual bool init();
    CREATE_FUNC(SettingLayer);
    
    static Scene* createScene();
    
    void switchBtnCallback(Ref* _ref, MYSwitch::MYSwitchStatus _status);
    void closeBtnCallback(Ref* _ref, MYButton::TouchEventType _type);
    void menuBtnCallback(Ref* _ref, MYButton::TouchEventType _type);
    void backMenuCallback(Ref* _ref, MYButton::TouchEventType _type);
    
    void updateMainFrame();
private:
    Layer* m_mainFrame;
    NormalFrame* m_normalFrame;
    MYSwitch* m_effectSwitch;
    MYSwitch* m_musicSwitch;
    MYButton* m_languageBtn;
    MYButton* m_creditBtn;
};

#endif /* defined(__CoolRun__SettingScene__) */
