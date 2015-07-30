//
//  GameOverMenu.h
//  CoolRun
//
//  Created by ManYou on 15/6/2.
//
//

#ifndef __CoolRun__GameOverMenu__
#define __CoolRun__GameOverMenu__

#include "PopViewLayer.h"
#include "extensions/cocos-ext.h"
#include "MYButton.h"
#include "CoolRunScene.h"

USING_NS_CC_EXT;

class GameOverMenu : public PopViewLayer
{
public:
    GameOverMenu();
    ~GameOverMenu();
    
    virtual bool init() override;
    CREATE_FUNC(GameOverMenu);
    
    bool init(CoolRun::RunType type);
    static GameOverMenu* create(CoolRun::RunType type);
    
    virtual void onEnter() override;
    
    void retryCallback(Ref* _ref, MYButton::TouchEventType _type);
    void homeCallback(Ref* _ref, MYButton::TouchEventType _type);
    
    void addRetryCallback(MYButton::MYButtonCallback call) { m_retryCallback = call; };
    void addHomeCallback(MYButton::MYButtonCallback call) { m_homeCallback = call; }
    
    void setFinalScore(int score, int jade, CoolRun::RunType _type);
private:
    MYButton* m_retryBtn;
    MYButton* m_homeBtn;
    Label* m_finalDis;
    Label* m_highDis;
    
    Label* m_jadeNum;
    Label* m_jadeNum_Ext;
    
    Sprite* m_newRecordSp;
    bool b_isNewRecord;
    
    MYButton::MYButtonCallback m_retryCallback;
    MYButton::MYButtonCallback m_homeCallback;
};

#endif /* defined(__CoolRun__GameOverMenu__) */
