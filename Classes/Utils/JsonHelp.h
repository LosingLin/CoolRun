//
//  JsonHelp.h
//  CoolRun
//
//  Created by ManYou on 14-8-13.
//
//

#ifndef __CoolRun__JsonHelp__
#define __CoolRun__JsonHelp__

#include "cocos2d.h"
#include <json/document.h>
#include <json/rapidjson.h>
#include <json/writer.h>
#include <json/stringbuffer.h>

USING_NS_CC;
using namespace std;

#define JSONHELPMARK "MARK"

namespace JsonHelp
{
    string readJsonFile(const string& fileName, rapidjson::Document &doc);
    bool getValueByKey(rapidjson::Document &doc, rapidjson::Value &_value, const string& key);
    bool getValueByKey(rapidjson::Value &_fValue, rapidjson::Value &_value, const string& key);
//
//    bool getValueByKeys(rapidjson::Document &doc, rapidjson::Value &_value, int _num, ...);
//    bool getValueByKeys(rapidjson::Value &_fValue, rapidjson::Value &_value, int _num,...);
    
    void testArgs(int num,...);
    void logJson(rapidjson::Value& _value);
    
    int getInt(rapidjson::Value &_value);
    float getFloat(rapidjson::Value &_value);
    float getFloatFromMember(rapidjson::Value &_value, const string& key);
    const char* getString(rapidjson::Value &_value);
    rapidjson::Value& getArray(rapidjson::Value &_value);
    
    void buildRect(rapidjson::Value &_value, Rect& _rect);
    void buildVec2(rapidjson::Value &_value, Vec2& _vec2);
    void buildSize(rapidjson::Value &_value, Size& _size);
}

#endif /* defined(__CoolRun__JsonHelp__) */
