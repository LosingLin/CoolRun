//
//  PhysicNode.cpp
//  CoolRun
//
//  Created by ManYou on 14-8-8.
//
//

#include "PhysicNode.h"

PhysicNode::PhysicNode()
: DrawableNode()
, m_type(kPhysicNodeUnknown)
, m_velocityX(0.0f)
, m_velocityY(0.0f)
, m_aX(0.0f)
, m_aY(0.0f)
, b_isScreenPos(false)
, m_align_x(0)
, m_align_y(0)
, b_isGravityEffect(false)
, b_isCollideEffect(false)
, b_isVelocityIgnore(false)
, b_isDestoryed(false)
, m_collideType(kCollideTypeUnknown)
, m_collideRect(Rect(0, 0, 0, 0))
//, m_positionPN(Vec2(0, 0))
, b_isForEditor(false)
{
}
PhysicNode::~PhysicNode()
{
}

bool PhysicNode::init()
{
    if (!DrawableNode::init()) {
        return false;
    }
    
    SHOW_RECT(m_collideRect);
    
    return true;
}

void PhysicNode::debugShow()
{
    SHOW_ORIGIN_AND_CONTENT;
    SHOW_RECT(this->getCollideRect());
}

/*
 "PhysicNode" : {
     "aPoint" : {"x" : 10.0, "y" : 10.0 },
     "pos" : { "x" : 10.0, "y" : 10.0 },
     "cSize" : { "w":100.0, "h":100 },
     "b_isG_effect" : true,
     "x" : { "v" : 10.0, "a" : 10.0 },
     "y" : { "v" : 10.0, "a" : 10.0 },
     "cRect" : { "x":10.0, "y":10.0, "w":100.0, "h":100 }
 }
 */

void PhysicNode::setAlignX(float alx)
{
    m_align_x = alx;
}
void PhysicNode::setAlignY(float aly)
{
    m_align_y = aly;
}

//void PhysicNode::setPosition(const Vec2 &position)
//{
//    DrawableNode::setPosition(position);
//    m_positionPN.x = position.x;
//    m_positionPN.y = position.y;
//    if (this->isScreenPos())
//    {
//        Size visibleSize = Director::getInstance()->getVisibleSize();
//        Vec2 origin = Director::getInstance()->getVisibleOrigin();
//        
//        m_positionPN.x = position.x + origin.x + m_align_x * visibleSize.width;
//        m_positionPN.y = position.y + origin.y + m_align_y * visibleSize.height;
//    }
//    else
//    {
//        m_positionPN.x = position.x;
//        m_positionPN.y = position.y;
//    }
//}
//const Vec2& PhysicNode::getPosition() const
//{
//    return m_positionPN;
//}

void PhysicNode::loadJson(rapidjson::Value& _value)
{
    rapidjson::Value tVal;
    //rapidjson::Value kVal; kVal = _value;
    
    //x
    if (_value.HasMember("x")) {
        rapidjson::Value& _val = _value["x"];
        if (_val.HasMember("v")) {
            if (_val["v"].IsDouble()) {
                auto xv = _val["v"].GetDouble();
                this->setXV(xv);
            }
            else if(_val["v"].IsInt())
            {
                auto xv = _val["v"].GetInt();
                this->setXV(xv);
            }
        }
        if (_val.HasMember("a")) {
            if (_val["a"].IsDouble()) {
                auto xa = _val["a"].GetDouble();
                this->setXA(xa);
            }
            else if(_val["a"].IsInt())
            {
                auto xa = _val["a"].GetInt();
                this->setXA(xa);
            }
        }
    }
    
    
    //y
    if (_value.HasMember("y")) {
        rapidjson::Value& _val = _value["y"];
        if (_val.HasMember("v")) {
            if (_val["v"].IsDouble()) {
                auto xv = _val["v"].GetDouble();
                this->setYV(xv);
            }
            else if(_val["v"].IsInt())
            {
                auto xv = _val["v"].GetInt();
                this->setYV(xv);
            }
        }
        if (_val.HasMember("a")) {
            if (_val["a"].IsDouble()) {
                auto xa = _val["a"].GetDouble();
                this->setYA(xa);
            }
            else if(_val["a"].IsInt())
            {
                auto xa = _val["a"].GetInt();
                this->setYA(xa);
            }
        }
    }
    //b_isScreenPos
    if (_value.HasMember("b_isS_pos")) {
        if (_value["b_isS_pos"].IsBool()) {
            auto flag = _value["b_isS_pos"].GetBool();
            this->setScreenPos(flag);
        }
    }
    //m_align_x
    if (_value.HasMember("align_x")) {
        if (_value["align_x"].IsDouble())
        {
            auto alx = _value["align_x"].GetDouble();
            this->setAlignX(alx);
        }
        else if (_value["align_x"].IsInt())
        {
            auto alx = _value["align_x"].GetInt();
            this->setAlignX(alx);
        }
    }
    //m_align_x
    if (_value.HasMember("align_y")) {
        if (_value["align_y"].IsDouble())
        {
            auto alx = _value["align_y"].GetDouble();
            this->setAlignY(alx);
        }
        else if (_value["align_y"].IsInt())
        {
            auto alx = _value["align_y"].GetInt();
            this->setAlignY(alx);
        }
    }
    //b_isGravityEffect
    if (_value.HasMember("b_isG_effect")) {
        if (_value["b_isG_effect"].IsBool()) {
            auto flag = _value["b_isG_effect"].GetBool();
            this->setGravityEffect(flag);
        }
    }
    //b_isCollideEffect
    if (_value.HasMember("b_isC_effect")) {
        if (_value["b_isC_effect"].IsBool()) {
            auto flag = _value["b_isC_effect"].GetBool();
            this->setCollideEffect(flag);
        }
    }
    //b_isVelocityIgnore
    if (_value.HasMember("b_isV_ignore")) {
        if (_value["b_isV_ignore"].IsBool()) {
            auto flag = _value["b_isV_ignore"].GetBool();
            this->setVelocityIgnore(flag);
        }
    }
    //m_collideType
    if (_value.HasMember("collideType")) {
        auto _type = (CollideType)JsonHelp::getInt(_value["collideType"]);
        this->setCollideType(_type);
    }
    
    //anchorPoint
    if (_value.HasMember("aPoint")) {
        Vec2 _vec2;
        JsonHelp::buildVec2(_value["aPoint"], _vec2);
        this->setAnchorPoint(_vec2);
    }
    
    //position
    if (_value.HasMember("pos")) {
        Vec2 _vec2;
        JsonHelp::buildVec2(_value["pos"], _vec2);
        this->setPosition(_vec2);
    }
    
    //contentSize
    if (_value.HasMember("cSize")) {
        Size _size;
        JsonHelp::buildSize(_value["cSize"], _size);
        this->setContentSize(_size);
    }
    
    //collideRect
    if (_value.HasMember("cRect")) {
        Rect _rect;
        JsonHelp::buildRect(_value["cRect"], _rect);
        this->setCollideRect(_rect);
    }
}

void PhysicNode::saveData(string* buffer)
{
    string str = string();
    stringstream ss;
    
    ss << "\"pNodeType\":";
    ss << this->getPhysicType();
    ss << ",";
    
    ss << "\"x\":{";
    ss << "\"v\":";
    ss << this->getXV();
    ss << ",";
    ss << "\"a\":";
    ss << this->getXA();
    ss << "},";
    
    ss << "\"y\":{";
    ss << "\"v\":";
    ss << this->getYV();
    ss << ",";
    ss << "\"a\":";
    ss << this->getYA();
    ss << "},";
    
    ss << "\"collideType\":";
    ss << this->getCollideType();
    ss << ",";
    
    ss << "\"align_x\":";
    ss << this->getAlignX();
    ss << ",";
    ss << "\"align_y\":";
    ss << this->getAlignY();
    ss << ",";
    
    ss << "\"b_isG_effect\":";
    if (this->isGravityEffect())
    {
        ss << "true";
    }
    else
    {
        ss << "false";
    }
    ss << ",";
    
    ss << "\"b_isC_effect\":";
    if (this->isCollideEffect())
    {
        ss << "true";
    }
    else
    {
        ss << "false";
    }
    ss << ",";
    
    ss << "\"b_isS_pos\":";
    if (this->isScreenPos())
    {
        ss << "true";
    }
    else
    {
        ss << "false";
    }
    ss << ",";
    
    ss << "\"b_isV_ignore\":";
    if (this->isVelocityIgnore())
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



