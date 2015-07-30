//
//  MYUserDefaultManager.h
//  CoolRun
//
//  Created by ManYou on 15/5/13.
//
//

#ifndef __CoolRun__MYUserDefaultManager__
#define __CoolRun__MYUserDefaultManager__

#include "cocos2d.h"
#include "MYMultiLanguageManager.h"
#include "Base.h"

//UserDefault
#define IS_PLAYER_GUIDED "is_player_guided"
#define MULTI_LANGUAGE_FLAG "current_language"
#define IS_EFFECT_OFF "is_effect_off"
#define IS_MUSIC_OFF "is_music_off"
#define HIGH_SCORE_NORMAL "high_score_normal"
#define HIGH_SCORE_NORMAL_ED "high_score_normal_ed"

//UserData
#define OWN_JADE "own_jade"
#define POWER_CURLV_SPARE       "power_curlv_spare"
#define POWER_CURLV_MAGNET      "power_curlv_magnet"
#define POWER_CURLV_TIMESCOIN   "power_curlv_timescoin"
#define POWER_CURLV_TIMESJUMP   "power_curlv_timejump"
#define POWER_CURLV_DAD         "power_curlv_dad"
#define POWER_CURLV_LANDBUILD   "power_curlv_landbuild"
#define POWER_CURLV_FLY         "power_curlv_fly"


USING_NS_CC;
using namespace std;

class MYUserDefaultManager : public Ref
{
private:
    MYUserDefaultManager();
    ~MYUserDefaultManager();
public:
    virtual bool init();
    
    static MYUserDefaultManager* getInstance();
    static void purgeInstance();
    
    bool isPlayedGuide();
    void setPlayedGuide(bool key);
    
    MYMultiLanguageManager::MultiLanguageType getCurrentLanguage();
    void setCurrentLanguage(MYMultiLanguageManager::MultiLanguageType _type);
    
    bool isEffectOff();
    void setEffectOff(bool flag);
    bool isMusicOff();
    void setMusicOff(bool flag);
    
    void setHighScoreNormal(int score);
    int getHighScoreNormal();
    
    void setHighScoreNormalEditor(int score);
    int getHighScoreNormalEditor();
    
    void setOwnJade(int num);
    int getOwnJade();
    void addOwnJade(int num);
    
    //power
    int getPowerLevel(PhysicNodeType _type);
    void setPowerLevel(PhysicNodeType _type, int level);
    void addPowerLevel(PhysicNodeType _type, int level = 1);
    
    /*
    void setPowerLevelSpare(int level);
    int getPowerLevelSpare();
    void addPowerLevelSpare(int level = 1);
    
    void setPowerLevelMagnet(int level);
    int getPowerLevelMagnet();
    void addPowerLevelMagnet(int level = 1);
    
    void setPowerLevelTimesCoin(int level);
    int getPowerLevelTimesCoin();
    void addPowerLevelTimesCoin(int level = 1);
    
    void setPowerLevelTimesJump(int level);
    int getPowerLevelTimesJump();
    void addPowerLevelTimesJump(int level = 1);
    
    void setPowerLevelDad(int level);
    int getPowerLevelDad();
    void addPowerLevelDad(int level = 1);
    
    void setPowerLevelLandBuild(int level);
    int getPowerLevelLandBuild();
    void addPowerLevelLandBuild(int level = 1);
    
    void setPowerLevelFly(int level);
    int getPowerLevelFly();
    void addPowerLevelFly(int level = 1);
     */
private:
    static MYUserDefaultManager* m_instance;
};

#endif /* defined(__CoolRun__MYUserDefaultManager__) */
