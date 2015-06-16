//
//  Vungle.h
//  CoolRun
//
//  Created by ManYou on 15/6/13.
//
//

#ifndef CoolRun_Vungle_h
#define CoolRun_Vungle_h

void VungleStart();
void VunglePlayAd();
bool VungleIsCachedAdAvailable();

void VungleCallback_willShowAd();
void VungleCallback_willCloseAd();

#endif
