//
//  AudioHelp.cpp
//  CoolRun
//
//  Created by ManYou on 15/5/4.
//
//

#include "AudioHelp.h"
#include "MYUserDefaultManager.h"


#define CHECK_EFFECT_SWITCH if(MYUserDefaultManager::getInstance()->isEffectOff()) { return; }
#define CHECK_BGMUSIC_SWITCH if(MYUserDefaultManager::getInstance()->isMusicOff()) { return; }

void AudioHelp::preloadEft(const char* fpath)
{
    CHECK_EFFECT_SWITCH;
    SimpleAudioEngine::getInstance()->preloadEffect(fpath);
}
void AudioHelp::unloadEft(const char* fpath)
{
    CHECK_EFFECT_SWITCH;
    SimpleAudioEngine::getInstance()->unloadEffect(fpath);
}
void AudioHelp::playEft(const char* fpath)
{
    CHECK_EFFECT_SWITCH;
    SimpleAudioEngine::getInstance()->playEffect(fpath, false, 1);
}
void AudioHelp::addEftVol(float vol)
{
    CHECK_EFFECT_SWITCH;
    float _vol = SimpleAudioEngine::getInstance()->getEffectsVolume();
    SimpleAudioEngine::getInstance()->setEffectsVolume(_vol + vol);
}
void AudioHelp::pauseAllEft()
{
    CHECK_EFFECT_SWITCH;
    SimpleAudioEngine::getInstance()->pauseAllEffects();
}
void AudioHelp::resumeAllEft()
{
    CHECK_EFFECT_SWITCH;
    SimpleAudioEngine::getInstance()->resumeAllEffects();
}
void AudioHelp::stopAllEft()
{
    CHECK_EFFECT_SWITCH;
    SimpleAudioEngine::getInstance()->stopAllEffects();
}


void AudioHelp::preloadBgA(const char* fpath)
{
    CHECK_BGMUSIC_SWITCH;
    SimpleAudioEngine::getInstance()->preloadBackgroundMusic(fpath);
}
void AudioHelp::unloadBgA(const char* fpath)
{
    CHECK_BGMUSIC_SWITCH;
}
void AudioHelp::playBgA(const char* fpath)
{
    CHECK_BGMUSIC_SWITCH;
    SimpleAudioEngine::getInstance()->playBackgroundMusic(fpath, true);
}
void AudioHelp::stopAllBgA()
{
    CHECK_BGMUSIC_SWITCH;
    SimpleAudioEngine::getInstance()->stopBackgroundMusic();
}
void AudioHelp::pauseBgA()
{
    CHECK_BGMUSIC_SWITCH;
    SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}
void AudioHelp::resumeBgA()
{
    CHECK_BGMUSIC_SWITCH;
    SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
bool AudioHelp::isBgAPlaying()
{
    return SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying();
}

void AudioHelp::endAudio()
{
    SimpleAudioEngine::end();
}

#pragma mark - Special

void AudioHelp::playBeAttackedEft()
{
//    int r = rand()%4+1;
//    char name[20] = {'\0'};
//    sprintf(name, "beAtk_%02d.mp3", r);
//    AudioHelp::playEft(name);
    AudioHelp::playEft("beAtk_01.mp3");
}
void AudioHelp::playBePickedEft()
{
    int r = rand()%3 + 1;
    char name[20] = {'\0'};
    sprintf(name, "coin_%02d.mp3", r);
    AudioHelp::playEft(name);
}

void AudioHelp::preloadHomeEft()
{
    AudioHelp::preloadEft("door_close.mp3");
    AudioHelp::preloadEft("door_open.mp3");
    AudioHelp::preloadEft("help.mp3");
}
void AudioHelp::unloadHomeEft()
{
    AudioHelp::unloadEft("door_close.mp3");
    AudioHelp::unloadEft("door_open.mp3");
    AudioHelp::unloadEft("help.mp3");
}
void AudioHelp::preloadBossEft()
{
    AudioHelp::preloadEft("shoot_bullet.mp3");
    AudioHelp::preloadEft("shoot_net.mp3");
    AudioHelp::preloadEft("spit.mp3");
}
void AudioHelp::unloadBossEft()
{
    AudioHelp::unloadEft("shoot_bullet.mp3");
    AudioHelp::unloadEft("shoot_net.mp3");
    AudioHelp::unloadEft("spit.mp3");
}
void AudioHelp::preloadMainEft()
{
    AudioHelp::preloadBgA("day_min.mp3");
    AudioHelp::preloadBgA("boss_min.mp3");
    AudioHelp::preloadEft("warning.mp3");
    AudioHelp::preloadEft("coin_01.mp3");
    AudioHelp::preloadEft("coin_02.mp3");
    AudioHelp::preloadEft("coin_03.mp3");
    AudioHelp::preloadEft("beAtk_01.mp3");
    AudioHelp::preloadEft("runner_atk.mp3");
    AudioHelp::preloadEft("runner_rebound.mp3");
    AudioHelp::preloadEft("gameover.mp3");
}
void AudioHelp::unloadMainEft()
{
    AudioHelp::unloadBgA("day_min.mp3");
    AudioHelp::unloadBgA("boss_min.mp3");
    AudioHelp::unloadEft("warning.mp3");
    AudioHelp::unloadEft("coin_01.mp3");
    AudioHelp::unloadEft("coin_02.mp3");
    AudioHelp::unloadEft("coin_03.mp3");
    AudioHelp::unloadEft("beAtk_01.mp3");
    AudioHelp::unloadEft("runner_atk.mp3");
    AudioHelp::unloadEft("runner_rebound.mp3");
    AudioHelp::unloadEft("gameover.mp3");
}
void AudioHelp::preloadMenuEft()
{
    AudioHelp::preloadBgA("night_min.mp3");
}
void AudioHelp::unloadMenuEft()
{
    AudioHelp::unloadBgA("night_min.mp3");
}
void AudioHelp::preloadAppEft()
{
    AudioHelp::preloadEft("btn_click.mp3");
}
void AudioHelp::unloadAppEft()
{
    AudioHelp::unloadEft("btn_click.mp3");
}
