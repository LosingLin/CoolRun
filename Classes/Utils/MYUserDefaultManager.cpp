//
//  MYUserDefaultManager.cpp
//  CoolRun
//
//  Created by ManYou on 15/5/13.
//
//

#include "MYUserDefaultManager.h"

MYUserDefaultManager* MYUserDefaultManager::m_instance = nullptr;

MYUserDefaultManager::MYUserDefaultManager()
: Ref()
{
    
}
MYUserDefaultManager::~MYUserDefaultManager()
{
    
}

bool MYUserDefaultManager::init()
{
    
    return true;
}

#pragma mark -

bool MYUserDefaultManager::isPlayedGuide()
{
    bool flag = UserDefault::getInstance()->getBoolForKey(IS_PLAYER_GUIDED);
    return flag;
}
void MYUserDefaultManager::setPlayedGuide(bool key)
{
    UserDefault::getInstance()->setBoolForKey(IS_PLAYER_GUIDED, key);
}

MYMultiLanguageManager::MultiLanguageType MYUserDefaultManager::getCurrentLanguage()
{
    auto str = UserDefault::getInstance()->getStringForKey(MULTI_LANGUAGE_FLAG);
    
    if (MULTI_LANGUAGE_CHINESE == str)
    {
        return MYMultiLanguageManager::MultiLanguageType::CHINESE;
    }
    else if ("" == str && MULTI_LANGUAGE_ENGLISH == str)
    {
        return MYMultiLanguageManager::MultiLanguageType::ENGLISH;
    }
    
    return MYMultiLanguageManager::MultiLanguageType::ENGLISH;
}
void MYUserDefaultManager::setCurrentLanguage(MYMultiLanguageManager::MultiLanguageType _type)
{
    switch (_type) {
        case MYMultiLanguageManager::MultiLanguageType::ENGLISH:
        {
            UserDefault::getInstance()->setStringForKey(MULTI_LANGUAGE_FLAG, MULTI_LANGUAGE_ENGLISH);
        }
            break;
        case MYMultiLanguageManager::MultiLanguageType::CHINESE:
        {
            UserDefault::getInstance()->setStringForKey(MULTI_LANGUAGE_FLAG, MULTI_LANGUAGE_CHINESE);
        }
            break;
            
        default:
            break;
    }
}

bool MYUserDefaultManager::isEffectOff()
{
    return UserDefault::getInstance()->getBoolForKey(IS_EFFECT_OFF, false);
}
void MYUserDefaultManager::setEffectOff(bool flag)
{
    UserDefault::getInstance()->setBoolForKey(IS_EFFECT_OFF, flag);
}
bool MYUserDefaultManager::isMusicOff()
{
    return UserDefault::getInstance()->getBoolForKey(IS_MUSIC_OFF, false);
}
void MYUserDefaultManager::setMusicOff(bool flag)
{
    UserDefault::getInstance()->setBoolForKey(IS_MUSIC_OFF, flag);
}

void MYUserDefaultManager::setHighScoreNormal(int score)
{
    int h_score = this->getHighScoreNormal();
    if (score > h_score)
    {
        UserDefault::getInstance()->setIntegerForKey(HIGH_SCORE_NORMAL, score);
    }
}
int MYUserDefaultManager::getHighScoreNormal()
{
    return UserDefault::getInstance()->getIntegerForKey(HIGH_SCORE_NORMAL);
}
void MYUserDefaultManager::setHighScoreNormalEditor(int score)
{
    int h_score = this->getHighScoreNormalEditor();
    if (score > h_score)
    {
        UserDefault::getInstance()->setIntegerForKey(HIGH_SCORE_NORMAL_ED, score);
    }
}
int MYUserDefaultManager::getHighScoreNormalEditor()
{
    return UserDefault::getInstance()->getIntegerForKey(HIGH_SCORE_NORMAL_ED);
}

void MYUserDefaultManager::setOwnJade(int num)
{
    UserDefault::getInstance()->setIntegerForKey(OWN_JADE, num);
}
int MYUserDefaultManager::getOwnJade()
{
    return UserDefault::getInstance()->getIntegerForKey(OWN_JADE, 0);
}
void MYUserDefaultManager::addOwnJade(int num)
{
    int before = this->getOwnJade();
    this->setOwnJade(before + num);
}

#pragma mark - power

int MYUserDefaultManager::getPowerLevel(PhysicNodeType _type)
{
    switch (_type)
    {
        case kPhysicNodeItemSpare:
        {
            return UserDefault::getInstance()->getIntegerForKey(POWER_CURLV_SPARE, 0);
        }
            break;
        case kPhysicNodeItemMagnet:
        {
            return UserDefault::getInstance()->getIntegerForKey(POWER_CURLV_MAGNET, 0);
        }
            break;
        case kPhysicNodeItemTimesCoin:
        {
            return UserDefault::getInstance()->getIntegerForKey(POWER_CURLV_TIMESCOIN, 0);
        }
            break;
        case kPhysicNodeItemTimesJump:
        {
            return UserDefault::getInstance()->getIntegerForKey(POWER_CURLV_TIMESJUMP, 0);
        }
            break;
        case kPhysicNodeItemDad:
        {
            return UserDefault::getInstance()->getIntegerForKey(POWER_CURLV_DAD, 0);
        }
            break;
        case kPhysicNodeItemLandBuild:
        {
            return UserDefault::getInstance()->getIntegerForKey(POWER_CURLV_LANDBUILD, 0);
        }
            break;
        case kPhysicNodeItemFly:
        {
            return UserDefault::getInstance()->getIntegerForKey(POWER_CURLV_FLY, 0);
        }
            break;
            
        default:
        {
            CCASSERT(false, "PhysicNodeType error!");
        }
            break;
    }
}
void MYUserDefaultManager::setPowerLevel(PhysicNodeType _type, int level)
{
    switch (_type)
    {
        case kPhysicNodeItemSpare:
        {
            UserDefault::getInstance()->setIntegerForKey(POWER_CURLV_SPARE, level);
        }
            break;
        case kPhysicNodeItemMagnet:
        {
            UserDefault::getInstance()->setIntegerForKey(POWER_CURLV_MAGNET, level);
        }
            break;
        case kPhysicNodeItemTimesCoin:
        {
            UserDefault::getInstance()->setIntegerForKey(POWER_CURLV_TIMESCOIN, level);
        }
            break;
        case kPhysicNodeItemTimesJump:
        {
            UserDefault::getInstance()->setIntegerForKey(POWER_CURLV_TIMESJUMP, level);
        }
            break;
        case kPhysicNodeItemDad:
        {
            UserDefault::getInstance()->setIntegerForKey(POWER_CURLV_DAD, level);
        }
            break;
        case kPhysicNodeItemLandBuild:
        {
            UserDefault::getInstance()->setIntegerForKey(POWER_CURLV_LANDBUILD, level);
        }
            break;
        case kPhysicNodeItemFly:
        {
            UserDefault::getInstance()->setIntegerForKey(POWER_CURLV_FLY, level);
        }
            break;
            
        default:
        {
            CCASSERT(false, "PhysicNodeType error!");
        }
            break;
    }
}
void MYUserDefaultManager::addPowerLevel(PhysicNodeType _type, int level)
{
    int befLv = this->getPowerLevel(_type);
    this->setPowerLevel(_type, level);
}

/*
void MYUserDefaultManager::setPowerLevelSpare(int level)
{
    UserDefault::getInstance()->setIntegerForKey(POWER_CURLV_SPARE, level);
}
int MYUserDefaultManager::getPowerLevelSpare()
{
    return UserDefault::getInstance()->getIntegerForKey(POWER_CURLV_SPARE, 0);
}
void MYUserDefaultManager::addPowerLevelSpare(int level)
{
    int befLv = this->getPowerLevelSpare();
    this->setPowerLevelSpare(befLv + level);
}

void MYUserDefaultManager::setPowerLevelMagnet(int level)
{
    UserDefault::getInstance()->setIntegerForKey(POWER_CURLV_MAGNET, level);
}
int MYUserDefaultManager::getPowerLevelMagnet()
{
    return UserDefault::getInstance()->getIntegerForKey(POWER_CURLV_MAGNET, 0);
}
void MYUserDefaultManager::addPowerLevelMagnet(int level)
{
    int befLv = this->getPowerLevelMagnet();
    this->setPowerLevelMagnet(befLv + level);
}

void MYUserDefaultManager::setPowerLevelTimesCoin(int level)
{
    UserDefault::getInstance()->setIntegerForKey(POWER_CURLV_TIMESCOIN, level);
}
int MYUserDefaultManager::getPowerLevelTimesCoin()
{
    return UserDefault::getInstance()->getIntegerForKey(POWER_CURLV_TIMESCOIN, 0);
}
void MYUserDefaultManager::addPowerLevelTimesCoin(int level)
{
    int befLv = this->getPowerLevelTimesCoin();
    this->setPowerLevelTimesCoin(befLv + level);
}

void MYUserDefaultManager::setPowerLevelTimesJump(int level)
{
    UserDefault::getInstance()->setIntegerForKey(POWER_CURLV_TIMESJUMP, level);
}
int MYUserDefaultManager::getPowerLevelTimesJump()
{
    return UserDefault::getInstance()->getIntegerForKey(POWER_CURLV_TIMESJUMP, 0);
}
void MYUserDefaultManager::addPowerLevelTimesJump(int level)
{
    int befLv = this->getPowerLevelTimesJump();
    this->setPowerLevelTimesJump(befLv + level);
}

void MYUserDefaultManager::setPowerLevelDad(int level)
{
    UserDefault::getInstance()->setIntegerForKey(POWER_CURLV_DAD, level);
}
int MYUserDefaultManager::getPowerLevelDad()
{
    return UserDefault::getInstance()->getIntegerForKey(POWER_CURLV_DAD, 0);
}
void MYUserDefaultManager::addPowerLevelDad(int level)
{
    int befLv = this->getPowerLevelDad();
    this->setPowerLevelDad(befLv + level);
}

void MYUserDefaultManager::setPowerLevelLandBuild(int level)
{
    UserDefault::getInstance()->setIntegerForKey(POWER_CURLV_LANDBUILD, level);
}
int MYUserDefaultManager::getPowerLevelLandBuild()
{
    return UserDefault::getInstance()->getIntegerForKey(POWER_CURLV_LANDBUILD, 0);
}
void MYUserDefaultManager::addPowerLevelLandBuild(int level)
{
    int befLv = this->getPowerLevelLandBuild();
    this->setPowerLevelLandBuild(befLv + level);
}

void MYUserDefaultManager::setPowerLevelFly(int level)
{
    UserDefault::getInstance()->setIntegerForKey(POWER_CURLV_FLY, level);
}
int MYUserDefaultManager::getPowerLevelFly()
{
    return UserDefault::getInstance()->getIntegerForKey(POWER_CURLV_FLY, 0);
}
void MYUserDefaultManager::addPowerLevelFly(int level)
{
    int befLv = this->getPowerLevelFly();
    this->setPowerLevelFly(befLv + level);
}
*/

#pragma mark -

MYUserDefaultManager* MYUserDefaultManager::getInstance()
{
    if (!m_instance)
    {
        m_instance = new MYUserDefaultManager();
    }
    return m_instance;
}
void MYUserDefaultManager::purgeInstance()
{
    if (m_instance)
    {
        delete m_instance;
        m_instance = nullptr;
    }
}