//
//  Vungle_iOS.m
//  CoolRun
//
//  Created by ManYou on 15/6/13.
//
//

#import <Foundation/Foundation.h>
#include "Vungle.h"
#import "VungleImp.h"
#include "cocos2d.h"
#include "AudioHelp.h"
#include "ThirdPartyManager.h"
#include "ReviveMenu.h"
#include "ResourceManager.h"

USING_NS_CC;

void VungleStart()
{
    [[VungleImp getInstance] startApp];
}
void VunglePlayAd()
{
    [[VungleImp getInstance] playAd];
}

bool VungleIsCachedAdAvailable()
{
    return [[VungleImp getInstance] isCachedAdAvailable];
}

void VungleCallback_willShowAd()
{
    ResourceManager::getInstance()->removeBigSource();
    
    Director::getInstance()->pause();
    AudioHelp::pauseAllEft();
    AudioHelp::pauseBgA();
    
    auto menu = ThirdPartyManager::getInstance()->getReviveMenu();
    if (menu)
    {
        menu->AdLoadingDone(false);
    }
}
void VungleCallback_willCloseAd()
{
    ResourceManager::getInstance()->addBigSource();
    
    Director::getInstance()->resume();
    AudioHelp::resumeAllEft();
    AudioHelp::resumeBgA();
    auto menu = ThirdPartyManager::getInstance()->getReviveMenu();
    if (menu)
    {
        menu->revive();
    }
}