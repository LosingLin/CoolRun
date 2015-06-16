//
//  JsonHelp.cpp
//  CoolRun
//
//  Created by ManYou on 14-8-13.
//
//

#include "JsonHelp.h"


string JsonHelp::readJsonFile(const string& fileName, rapidjson::Document &doc)
{
    string jsonStr = FileUtils::getInstance()->getStringFromFile(fileName);
    
    //log("data : %s", jsonStr.c_str());
    
    doc.Parse<0>(jsonStr.c_str());
    
    if (doc.HasParseError())
    {
        CCASSERT(false, "json parse error");
    }
    
    return jsonStr;
}


bool JsonHelp::getValueByKey(rapidjson::Document &doc, rapidjson::Value &_value, const string& key)
{
    if (doc.IsObject())
    {
        _value = doc[key.c_str()];
        return true;
    }
    else
    {
        //CCASSERT(false, "document is not an object");
        return false;
    }
}
bool JsonHelp::getValueByKey(rapidjson::Value &_fValue, rapidjson::Value &_value, const string& key)
{
    log("key: %s", key.c_str());
    
    //JsonHelp::logJson(_fValue);
    if (_fValue.HasMember(key.c_str())) {
        _value = _fValue[key.c_str()];
        JsonHelp::logJson(_value);
        return true;
    }
    else
    {
        //CCASSERT(false, "key is not the member");
        return false;
    }
}

 void JsonHelp::testArgs(int num,...)
{
    string str;
    const char* _arg = "";
    va_list args;
    va_start(args, num);
    while (num > 0) {
        --num;
        _arg = va_arg(args, const char*);
        str += _arg;
        
    }
    va_end(args);
    
    log("%s", str.c_str());
}

void JsonHelp::logJson(rapidjson::Value& _value)
{
//    rapidjson::Document doc;
//    doc.SetObject();
//    rapidjson::Document::AllocatorType& allocator = doc.GetAllocator();
//    doc.AddMember("LOG", _value, allocator);
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
//    doc.Accept(writer);
    if (_value.IsObject())
    {
        _value.Accept(writer);
        log("%s", buffer.GetString());
    }
    else
    {
        log("value is not a object");
    }
    
    
    //log("%s", _value.Accept(wirter));
}

/*

bool JsonHelp::getValueByKeys(rapidjson::Document &doc, rapidjson::Value &_value, int _num,...)
{
    int i = 0;
    rapidjson::Value tVal;
    va_list args;
    va_start(args, _num);
    while (_num > 0) {
        --_num;
        const char * key = va_arg(args, const char*);
        log("%s", key);
        if (i == 0)
        {
            if (JsonHelp::getValueByKey(doc, _value, key))
            {
                tVal = _value;
                i ++;
            }
            else
            {
                va_end(args);
                return false;
            }
            
        }
        else
        {
            if (JsonHelp::getValueByKey(tVal, _value, key))
            {
                tVal = _value;
            }
            else
            {
                va_end(args);
                return false;
            }

        }

    }
    
    va_end(args);
    _value = tVal;
    return true;
}
bool JsonHelp::getValueByKeys(rapidjson::Value &_fValue, rapidjson::Value &_value, int _num,...)
{
    rapidjson::Value &tVal = _value;
    int i = 0;
    va_list args;
    va_start(args, _num);
    while (_num > 0) {
        --_num;
        const char * key = va_arg(args, const char*);
        log("%s", key);
        if (i == 0)
        {
            ++ i;
            if (JsonHelp::getValueByKey(_fValue, _value, key)) {
                //tVal = _value;
            }
            else
            {
                va_end(args);
                return false;
            }
        }
        else
        {
            if (JsonHelp::getValueByKey(tVal, _value, key)) {
                tVal = _value;
            }
            else
            {
                va_end(args);
                return false;
            }
        }
        
        
    }
    va_end(args);
    _value = tVal;
    return true;
}
 
 */

int JsonHelp::getInt(rapidjson::Value &_value)
{
    if (_value.IsInt())
    {
        return _value.GetInt();
    }
    else
    {
        CCASSERT(false, "value is not a int");
    }
}
float JsonHelp::getFloat(rapidjson::Value &_value)
{
    if (_value.IsDouble())
    {
        return _value.GetDouble();
    }
    else if(_value.IsInt())
    {
        return _value.GetInt();
    }
    else
    {
        CCASSERT(false, "value is not a double");
    }
}
const char* JsonHelp::getString(rapidjson::Value &_value)
{
    if (_value.IsString())
    {
        return  _value.GetString();
    }
    else
    {
        CCASSERT(false, "value is not a string");
    }
}

rapidjson::Value& JsonHelp::getArray(rapidjson::Value &_value)
{
    if (_value.IsArray())
    {
        return _value;
    }
    else
    {
        CCASSERT(false, "value is not a array");
    }
}

float JsonHelp::getFloatFromMember(rapidjson::Value &_value, const string& key)
{
    if (_value.HasMember(key.c_str())) {
        if (_value[key.c_str()].IsDouble()) {
            return _value[key.c_str()].GetDouble();
        }
        else if(_value[key.c_str()].IsInt())
        {
            return _value[key.c_str()].GetInt();
        }
    }
    return 0.0f;
}

void JsonHelp::buildRect(rapidjson::Value &_value, Rect& _rect)
{
    _rect.origin.x = JsonHelp::getFloatFromMember(_value, "x");
    _rect.origin.y = JsonHelp::getFloatFromMember(_value, "y");
    _rect.size.width = JsonHelp::getFloatFromMember(_value, "w");
    _rect.size.height = JsonHelp::getFloatFromMember(_value, "h");
}
void JsonHelp::buildVec2(rapidjson::Value &_value, Vec2& _vec2)
{
    _vec2.x = JsonHelp::getFloatFromMember(_value, "x");
    _vec2.y = JsonHelp::getFloatFromMember(_value, "y");
}

void JsonHelp::buildSize(rapidjson::Value &_value, Size& _size)
{
    _size.width = JsonHelp::getFloatFromMember(_value, "w");
    _size.height = JsonHelp::getFloatFromMember(_value, "h");
}
