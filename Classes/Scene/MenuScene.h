//
//  MenuScene.h
//  CoolRun
//
//  Created by ManYou on 14-9-3.
//
//

#ifndef __CoolRun__MenuScene__
#define __CoolRun__MenuScene__

#include "cocos2d.h"
#include "MYButton.h"

//test
#include "editor-support/cocostudio/CocoStudio.h"
using namespace cocostudio;


USING_NS_CC;


class Home;
class CommonBackground;
class MenuLayer : public Layer
{
public:
    MenuLayer();
    ~MenuLayer();
    
    virtual bool init();
    CREATE_FUNC(MenuLayer);
    
    virtual void onEnter() override;
    virtual void onEnterTransitionDidFinish() override;
    
    static Scene* createScene();
    
    void startCallback(Ref* _ref, MYButton::TouchEventType _type);
    void editorCallback(Ref* _ref, MYButton::TouchEventType _type);
    void settingCallback(Ref* _ref, MYButton::TouchEventType _type);
    
    
    void movementEvent(Armature *armature, MovementEventType movementType, const std::string& movementID);
    void frameEvent(Bone *bone, const std::string& frameEventName, int originFrameIndex, int currentFrameIndex);
    
    void start();
private:
    Sprite* m_logo;
    Node* m_menu;
    Home* m_home;
    CommonBackground* m_comBg;
};

#endif /* defined(__CoolRun__MenuScene__) */
