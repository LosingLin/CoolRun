//
//  AudioHelp.h
//  CoolRun
//
//  Created by ManYou on 15/5/4.
//
//

#ifndef __CoolRun__AudioHelp__
#define __CoolRun__AudioHelp__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

using namespace std;
using namespace CocosDenshion;

namespace AudioHelp
{
    void preloadEft(const char* fpath);
    void unloadEft(const char* fpath);
    void playEft(const char* fpath);
    void addEftVol(float vol);
    void pauseAllEft();
    void resumeAllEft();
    void stopAllEft();
    
    void preloadBgA(const char* fpath);
    void unloadBgA(const char* fpath);
    void playBgA(const char* fpath);
    void pauseBgA();
    void resumeBgA();
    bool isBgAPlaying();
    void stopAllBgA();
    
    void endAudio();
    
    //special
    void playBeAttackedEft();
    void playBePickedEft();
    
    void preloadHomeEft();
    void unloadHomeEft();
    void preloadBossEft();
    void unloadBossEft();
    void preloadMainEft();
    void unloadMainEft();
    void preloadMenuEft();
    void unloadMenuEft();
    void preloadAppEft();
    void unloadAppEft();
}

#endif /* defined(__CoolRun__AudioHelp__) */
