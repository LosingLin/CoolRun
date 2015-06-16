//
//  Bullet.cpp
//  CoolRun
//
//  Created by ManYou on 14/12/5.
//
//

#include "Bullet.h"

Bullet::Bullet()
: MultipleCollideNode()
, b_isRunnerHurt(false)
, b_isAnimalHurt(false)
, b_isAtkable(false)
, m_particleSys(nullptr)
{
}
Bullet::~Bullet()
{
}

bool Bullet::init()
{
    if (!MultipleCollideNode::init())
    {
        return false;
    }
    
    this->setCollideType(kCollideTypeBullet);
    
    this->setLocalZOrder(ZORDER_BULLET);
    
    return true;
}

void Bullet::loadJson(rapidjson::Value& _value)
{
    MultipleCollideNode::loadJson(_value);
    
    //b_isRunnerHurt
    if (_value.HasMember("b_isR_hurt")) {
        if (_value["b_isR_hurt"].IsBool()) {
            auto flag = _value["b_isR_hurt"].GetBool();
            this->setRunnerHurt(flag);
        }
    }
    //b_isAnimalHurt
    if (_value.HasMember("b_isA_hurt")) {
        if (_value["b_isA_hurt"].IsBool()) {
            auto flag = _value["b_isA_hurt"].GetBool();
            this->setAnimalHurt(flag);
        }
    }
    //b_isAtkable
    if (_value.HasMember("b_isA_able")) {
        if (_value["b_isA_able"].IsBool()) {
            auto flag = _value["b_isA_able"].GetBool();
            this->setAtkable(flag);
        }
    }
}
void Bullet::saveData(string* buffer)
{
    MultipleCollideNode::saveData(buffer);
    
    string str = string();
    stringstream ss;
    
    ss << "\"b_isR_hurt\":";
    if (this->isRunnerHurt())
    {
        ss << "true";
    }
    else
    {
        ss << "false";
    }
    ss << ",";
    
    ss << "\"b_isA_hurt\":";
    if (this->isAnimalHurt())
    {
        ss << "true";
    }
    else
    {
        ss << "false";
    }
    ss << ",";
    
    ss << "\"b_isA_able\":";
    if (this->isAtkable())
    {
        ss << "true";
    }
    else
    {
        ss << "false";
    }
    ss << ",";
    
    ss >> str;
    buffer->append(str);
}

void Bullet::beingDestoryed()
{
    this->setDestoryed(true);
}