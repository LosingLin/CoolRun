//
//  PowerDataManager.cpp
//  CoolRun
//
//  Created by ManYou on 15/6/24.
//
//

#include "PowerDataManager.h"
#include "MYUserDefaultManager.h"

#define POWERDATAFILENAME   "power_data"

//
#define DEFAULTINFOHEAD "default"
#define SPAREINFOHEAD "spare"
#define MAGNETINFOHEAD "magnet"
#define TIMESCOININFOHEAD "timescoin"
#define TIMESJUMPINFOHEAD "timesjump"
#define DADINFOHEAD "dad"
#define LANDBUILDINFOHEAD   "landbuild"
#define FLYINFOHEAD "head"

#define MAXLEVELHEAD    "maxLv"
#define JADEEXPENDHEAD  "jade_expend"
#define EFFECTADDHEAD     "eft_add"

PowerDataManager* PowerDataManager::m_instance = nullptr;
rapidjson::Document* PowerDataManager::m_doc = nullptr;

PowerDataManager::PowerDataManager()
: Ref()
{
    
}
PowerDataManager::~PowerDataManager()
{
    
}

bool PowerDataManager::init()
{
    m_doc = new rapidjson::Document();
    JsonHelp::readJsonFile(POWERDATAFILENAME, *m_doc);
    
    return true;
}

int PowerDataManager::getMaxLevel(PhysicNodeType type)
{
    int maxLv = 0;
    //JsonHelp::logJson(infoValue);
    if ((*m_doc)[this->_findInfoValueTypeKey(type).c_str()].HasMember(MAXLEVELHEAD))
    {
        maxLv = JsonHelp::getInt((*m_doc)[this->_findInfoValueTypeKey(type).c_str()][MAXLEVELHEAD]);
    }
    return maxLv;
}
float PowerDataManager::getNextLevelEffectAdd(PhysicNodeType type)
{
    float effect_add = 0.0f;
    if ((*m_doc)[this->_findInfoValueTypeKey(type).c_str()].HasMember(MAXLEVELHEAD))
    {
        effect_add = JsonHelp::getFloat((*m_doc)[this->_findInfoValueTypeKey(type).c_str()][EFFECTADDHEAD]);
    }
    return effect_add;
}
int PowerDataManager::getNextLevelJadeExpend(PhysicNodeType type)
{
    int expend = 99999999;
    if ((*m_doc)[this->_findInfoValueTypeKey(type).c_str()].HasMember(JADEEXPENDHEAD))
    {
        int curLv = MYUserDefaultManager::getInstance()->getPowerLevel(type);
        expend = JsonHelp::getInt((*m_doc)[this->_findInfoValueTypeKey(type).c_str()][JADEEXPENDHEAD][curLv+1]);
    }
    return expend;
}

#pragma mark - private

void PowerDataManager::_findInfoValue(PhysicNodeType type, rapidjson::Value& _value)
{
    switch (type)
    {
        case kPhysicNodeItemSpare:
        {
            if ((*m_doc).HasMember(SPAREINFOHEAD))
            {
                _value = (*m_doc)[SPAREINFOHEAD];
            }
            else
            {
                if ((*m_doc).HasMember(DEFAULTINFOHEAD))
                {
                    _value = (*m_doc)[DEFAULTINFOHEAD];
                    JsonHelp::logJson(_value);
                }
                
            }
        }
            break;
        case kPhysicNodeItemMagnet:
        {
            if ((*m_doc).HasMember(MAGNETINFOHEAD))
            {
                _value = (*m_doc)[MAGNETINFOHEAD];
            }
            else
            {
                _value = (*m_doc)[DEFAULTINFOHEAD];
            }
        }
            break;
        case kPhysicNodeItemTimesCoin:
        {
            if ((*m_doc).HasMember(TIMESCOININFOHEAD))
            {
                _value = (*m_doc)[TIMESCOININFOHEAD];
            }
            else
            {
                _value = (*m_doc)[DEFAULTINFOHEAD];
            }
        }
            break;
        case kPhysicNodeItemTimesJump:
        {
            if ((*m_doc).HasMember(TIMESJUMPINFOHEAD))
            {
                _value = (*m_doc)[TIMESJUMPINFOHEAD];
            }
            else
            {
                _value = (*m_doc)[DEFAULTINFOHEAD];
            }
        }
            break;
        case kPhysicNodeItemDad:
        {
            if ((*m_doc).HasMember(DADINFOHEAD))
            {
                _value = (*m_doc)[DADINFOHEAD];
            }
            else
            {
                _value = (*m_doc)[DEFAULTINFOHEAD];
            }
        }
            break;
        case kPhysicNodeItemLandBuild:
        {
            if ((*m_doc).HasMember(LANDBUILDINFOHEAD))
            {
                _value = (*m_doc)[LANDBUILDINFOHEAD];
            }
            else
            {
                _value = (*m_doc)[DEFAULTINFOHEAD];
            }
        }
            break;
        case kPhysicNodeItemFly:
        {
            if ((*m_doc).HasMember(FLYINFOHEAD))
            {
                _value = (*m_doc)[FLYINFOHEAD];
            }
            else
            {
                _value = (*m_doc)[DEFAULTINFOHEAD];
            }
        }
            break;
            
        default:
            CCASSERT(false, "type error!");
            break;
    }
}

const string PowerDataManager::_findInfoValueTypeKey(PhysicNodeType type)
{
    switch (type)
    {
        case kPhysicNodeItemSpare:
        {
            if ((*m_doc).HasMember(SPAREINFOHEAD))
            {
                return SPAREINFOHEAD;
            }
            else
            {
                return DEFAULTINFOHEAD;
            }
        }
            break;
        case kPhysicNodeItemMagnet:
        {
            if ((*m_doc).HasMember(MAGNETINFOHEAD))
            {
                return MAGNETINFOHEAD;
            }
            else
            {
                return DEFAULTINFOHEAD;
            }
        }
            break;
        case kPhysicNodeItemTimesCoin:
        {
            if ((*m_doc).HasMember(TIMESCOININFOHEAD))
            {
                return TIMESCOININFOHEAD;
            }
            else
            {
                return DEFAULTINFOHEAD;
            }
        }
            break;
        case kPhysicNodeItemTimesJump:
        {
            if ((*m_doc).HasMember(TIMESJUMPINFOHEAD))
            {
                return TIMESJUMPINFOHEAD;
            }
            else
            {
                return DEFAULTINFOHEAD;
            }
        }
            break;
        case kPhysicNodeItemDad:
        {
            if ((*m_doc).HasMember(DADINFOHEAD))
            {
                return DADINFOHEAD;
            }
            else
            {
                return DEFAULTINFOHEAD;
            }
        }
            break;
        case kPhysicNodeItemLandBuild:
        {
            if ((*m_doc).HasMember(LANDBUILDINFOHEAD))
            {
                return LANDBUILDINFOHEAD;
            }
            else
            {
                return DEFAULTINFOHEAD;
            }
        }
            break;
        case kPhysicNodeItemFly:
        {
            if ((*m_doc).HasMember(FLYINFOHEAD))
            {
                return FLYINFOHEAD;
            }
            else
            {
                return DEFAULTINFOHEAD;
            }
        }
            break;
            
        default:
            CCASSERT(false, "type error!");
            break;
    }

}

#pragma mark -

PowerDataManager* PowerDataManager::getInstance()
{
    if (!m_instance)
    {
        m_instance = new PowerDataManager();
        if (m_instance && m_instance->init())
        {
            return m_instance;
        }
        else
        {
            delete m_instance;
            m_instance = nullptr;
        }
    }
    return m_instance;
}
void PowerDataManager::purgeInstance()
{
    if (m_instance)
    {
        delete m_instance;
        m_instance = nullptr;
    }
    if (m_doc)
    {
        delete m_doc;
        m_doc = nullptr;
    }
}