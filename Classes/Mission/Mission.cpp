//
//  Mission.cpp
//  CoolRun
//
//  Created by ManYou on 14-8-20.
//
//

#include "Mission.h"
#include "Base.h"

#define MISSIONDATA_START_PATH       "start"
#define MISSIONDATA_START_FORMAT     "/s%04d"
#define MISSIONDATA_EASY_PATH       "easy"
#define MISSIONDATA_EASY_FORMAT     "/e%04d"
#define MISSIONDATA_NORMAL_PATH       "normal"
#define MISSIONDATA_NORMAL_FORMAT     "/n%04d"
#define MISSIONDATA_HARD_PATH       "hard"
#define MISSIONDATA_HARD_FORMAT     "/h%04d"
#define MISSIONDATA_Boss_PATH       "boss"
#define MISSIONDATA_Boss_FORMAT     "/b%04d"

Mission::Mission()
: Ref()
, m_jsonStr(NULL)
, m_pageIndex(0)
, m_repeatModel(Mission::MissionRepeatModel::LAST)
{

}
Mission::~Mission()
{
    if (m_jsonStr)
    {
        delete m_jsonStr;
    }
}


bool Mission::init()
{
    
    return true;
}

void Mission::setJsonStr(const string& str)
{
    m_jsonStr = new string(str);
    m_pageIndex = -1;
}

int Mission::getMissionPageCount()
{
    rapidjson::Document doc;
    doc.Parse<0>(m_jsonStr->c_str());
    if (doc.HasParseError())
    {
        CCASSERT(false, "json parse error");
    }
    rapidjson::Value _value;
    if (JsonHelp::getValueByKey(doc, _value, "pages"))
    {
        return _value.Size();
    }
    
    return 0;
}

MissionPage* Mission::getMissionPage(int _index)
{
    rapidjson::Document doc;
    doc.Parse<0>(m_jsonStr->c_str());
    if (doc.HasParseError())
    {
        CCASSERT(false, "json parse error");
    }
    rapidjson::Value _value;
    if (JsonHelp::getValueByKey(doc, _value, "pages"))
    {
        CCASSERT(_index >= 0 && _index < _value.Size(), "index out of range");
        auto page = MissionPage::create(_value[_index]);
        if (MissionRepeatModel::LAST == m_repeatModel)
        {
            if (_index == _value.Size()-1)
            {
                page->setLastPage(true);
            }
        }
        
        return page;
    }
    
    return nullptr;
}
MissionPage* Mission::getNextMissionPage()
{
    m_pageIndex += 1;
    
    rapidjson::Document doc;
    doc.Parse<0>(m_jsonStr->c_str());
    if (doc.HasParseError())
    {
        CCASSERT(false, "json parse error");
    }
    rapidjson::Value _value;
    if (JsonHelp::getValueByKey(doc, _value, "pages"))
    {
        if (m_pageIndex >= _value.Size())
        {
            CCASSERT(_value.Size() >= 1, "pages is not enough");
            //这里循环的是最后一页
            if (MissionRepeatModel::LAST == m_repeatModel)
            {
                m_pageIndex = _value.Size() - 1;
            }
            else if (MissionRepeatModel::ALL == m_repeatModel)
            {
                m_pageIndex = 0;
            }
        
        }
        
        return this->getMissionPage(m_pageIndex);
    }
    m_pageIndex += 1;
    return nullptr;
}

#pragma mark - random

string Mission::getRandomMissionData(const string& path, const string& format, int num)
{
    string data = "";
    char ca[80] = {'\0'};
    int total = 0;
    stringstream ss;
    ss << FileUtils::getInstance()->getStringFromFile(path + "/count");
    ss >> total;
    //log("count : %d", total);

    for (int i = 0; i < num; ++ i)
    {
        int r = rand() % total + 1;
        log("pathformat : %s", (path+format).c_str());
        sprintf(ca, (path+format).c_str(), r);
        log("name : %s\n", ca);
        data += FileUtils::getInstance()->getStringFromFile(ca);
        
        if (i != num-1)
        {
            data += ",";
        }
    }
    return data;
}


#pragma mark - create


Mission* Mission::create(const std::string& filename, MissionRepeatModel model)
{
    auto _mission = Mission::create();
    
    auto jsonStr = FileUtils::getInstance()->getStringFromFile(filename);
    _mission->setJsonStr(jsonStr);
    
    _mission->setMissionRepeatModel(model);
    
    return _mission;
}

Mission* Mission::create(const std::string& jsonStr)
{
    auto _mission = Mission::create();
    int e = 0, n = 0, h = 0;
    int s = 0, b = 1;
    rapidjson::Document doc;
    doc.Parse<rapidjson::kParseDefaultFlags>(jsonStr.c_str());
    if (doc.HasParseError())
    {
        CCASSERT(false, "json parse error");
    }
    rapidjson::Value _value;
    if (doc.HasMember("s"))
    {
        if (JsonHelp::getValueByKey(doc, _value, "s"))
        {
            if (_value.HasMember("num"))
            {
                s = JsonHelp::getInt(_value["num"]);
            }
        }
    }
    if (JsonHelp::getValueByKey(doc, _value, "e"))
    {
        if (_value.HasMember("num"))
        {
            e = JsonHelp::getInt(_value["num"]);
        }
    }
    if (JsonHelp::getValueByKey(doc, _value, "n"))
    {
        if (_value.HasMember("num"))
        {
            n = JsonHelp::getInt(_value["num"]);
        }
    }
    if (JsonHelp::getValueByKey(doc, _value, "h"))
    {
        if (_value.HasMember("num"))
        {
            h = JsonHelp::getInt(_value["num"]);
        }
    }
    
    log("MISSION : easy : %d, normal: %d, hard : %d", e, n, h);
    auto missionData = FileUtils::getInstance()->getStringFromFile("head");
    
    missionData += _mission->getRandomMissionData(MISSIONDATA_START_PATH, MISSIONDATA_START_FORMAT, s);
    if (s > 0 && (e > 0 || n > 0 || h > 0))
    {
        missionData += ",";
    }
    missionData += _mission->getRandomMissionData(MISSIONDATA_EASY_PATH, MISSIONDATA_EASY_FORMAT, e);
    if (e >0 && (n > 0 || h > 0))
    {
        missionData += ",";
    }
    missionData += _mission->getRandomMissionData(MISSIONDATA_NORMAL_PATH, MISSIONDATA_NORMAL_FORMAT, n);
    if (n > 0 && h > 0)
    {
        missionData += ",";
    }
    missionData += _mission->getRandomMissionData(MISSIONDATA_HARD_PATH, MISSIONDATA_HARD_FORMAT, h);
    missionData += ",";
    missionData += _mission->getRandomMissionData(MISSIONDATA_Boss_PATH , MISSIONDATA_Boss_FORMAT, b);
    missionData += ",";
    missionData += _mission->getRandomMissionData(MISSIONDATA_Boss_PATH , MISSIONDATA_Boss_FORMAT, b);
    missionData += FileUtils::getInstance()->getStringFromFile("tail");
    //log("MISSIONDATA : %s\n", missionData.c_str());
    
    _mission->setJsonStr(missionData);
    
    return _mission;
}

Mission* Mission::createWithDataStr(const std::string& data)
{
    auto _mission = Mission::create();
    _mission->setJsonStr(data);
    return _mission;
}
