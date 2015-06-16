//
//  MYKeyBoardLayer.cpp
//  CoolRun
//
//  Created by ManYou on 15/6/13.
//
//

#include "MYKeyBoardLayer.h"
#include "ExitGameMenu.h"

#define kTag_exitGameMenu   678

MYKeyBoardLayer::MYKeyBoardLayer()
: MYLayer()
{
    
}
MYKeyBoardLayer::~MYKeyBoardLayer()
{
    
}

bool MYKeyBoardLayer::init()
{
    if (!MYLayer::init())
    {
        return false;
    }
    
    auto listener = EventListenerKeyboard::create();
//    listener->onKeyReleased =[&](EventKeyboard::KeyCode keyCode, Event* event)
//    {
//        if(keyCode == EventKeyboard::KeyCode::KEY_BACKSPACE)
//        {
//            Director::getInstance()->end();
//
//        }
//    };
    listener->onKeyReleased = CC_CALLBACK_2(MYKeyBoardLayer::keyBoardCallback, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
    
    return true;
}

void MYKeyBoardLayer::keyBoardCallback(EventKeyboard::KeyCode keyCode, Event* event)
{
    //log("keyBoardCallback ====== %d", keyCode);
    if (keyCode == EventKeyboard::KeyCode::KEY_BACKSPACE || keyCode == EventKeyboard::KeyCode::KEY_BACK)
    {
        this->showExitGameFrame();
    }
}

void MYKeyBoardLayer::showExitGameFrame()
{
    if (!this->getChildByTag(kTag_exitGameMenu))
    {
        auto _egm = ExitGameMenu::create();
        _egm->setTag(kTag_exitGameMenu);
        this->addChild(_egm);
    }
    
}