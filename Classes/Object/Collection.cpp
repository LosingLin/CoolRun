//
//  Collection.cpp
//  CoolRun
//
//  Created by ManYou on 14-10-7.
//
//

#include "Collection.h"
#include "Base.h"
#include "PhysicNode.h"
#include "PhysicNodeFactory.h"
#include "CollectionMatrix.h"

Collection::Collection()
: Ref()
, m_collection(nullptr)
, m_jsonStr(nullptr)
, m_cmIndex(0)
, m_incX(0)
, m_incY(0)
{
}
Collection::~Collection()
{
    CC_SAFE_RELEASE_NULL(m_collection);
    if (m_jsonStr)
    {
        delete m_jsonStr;
        m_jsonStr = nullptr;
    }
}
bool Collection::init()
{
    CREATEANDRETAINARRAY(m_collection);
    
    return true;
}

int Collection::getMatrixTotalNum()
{
    return sizeof(CollectionMatrixInstance::INSTANCE)/sizeof(CollectionMatrixInstance::INSTANCE[0]);
}

void Collection::setJsonStr(const string& json)
{
    if (m_jsonStr)
    {
        delete m_jsonStr;
        m_jsonStr = nullptr;
    }
    m_jsonStr = new string(json);
}

void Collection::loadJson(rapidjson::Value& _value)
{
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    if (_value.IsObject())
    {
        _value.Accept(writer);
        this->setJsonStr(buffer.GetString());
    }
    else
    {
        this->setJsonStr("{}");
    }
    int index = 0;
    float x_inc = 0.0f;
    float y_inc = 0.0f;
    
    if (_value.HasMember("cm_index"))
    {
        index = JsonHelp::getInt(_value["cm_index"]);
        this->setCmIndex(index);
    }
    if (_value.HasMember("x_inc"))
    {
        x_inc = JsonHelp::getFloat(_value["x_inc"]);
        this->setIncX(x_inc);
    }
    if (_value.HasMember("y_inc"))
    {
        y_inc = JsonHelp::getFloat(_value["y_inc"]);
        this->setIncY(y_inc);
    }
    
    CollectionMatrix _matrix = CollectionMatrixInstance::INSTANCE[index];
    
    for (int i = 0; i < kCollectionMatrixNum; ++i)
    {
        for (int j = 0; j < kCollectionMatrixNum; ++j)
        {
            if (_matrix.matrix[i][j] == 1)
            {
                auto _node = PhysicNodeFactory::getInstance()->create(_value);
                auto _pos = _node->getPosition();
                _pos.x += j*x_inc;
                _pos.y += (kCollectionMatrixNum-1-i)*y_inc;
                _node->setPosition(_pos);
                m_collection->addObject(_node);
            }
        }
    }
}

PhysicNode* Collection::createEditorPhysicNode()
{
    rapidjson::Document doc;
    doc.Parse<0>(m_jsonStr->c_str());
    if (doc.HasParseError())
    {
        CCASSERT(false, "json parse error");
    }
    auto pNode = PhysicNodeFactory::getInstance()->create(doc);
    pNode->removeAllChildrenWithCleanup(true);
    //auto csize = pNode->getContentSize();
    auto csize = Size(50, 50);
    pNode->setContentSize(Size(5*this->getIncX() + csize.width, 5*this->getIncY() + csize.height));
    
    CollectionMatrix _matrix = CollectionMatrixInstance::INSTANCE[this->getCmIndex()];
    for (int i = 0; i < kCollectionMatrixNum; ++i)
    {
        for (int j = 0; j < kCollectionMatrixNum; ++j)
        {
            if (_matrix.matrix[i][j] == 1)
            {
                auto _node = PhysicNodeFactory::getInstance()->create(doc);
                auto _pos = Vec2::ZERO;
                _pos.x += j*this->getIncX();
                _pos.y += (kCollectionMatrixNum-1-i)*this->getIncY();
                _node->setPosition(_pos);
                _node->setForEditor(true);
                pNode->addChild(_node);
            }
        }
    }
    pNode->setForEditor(true);
    return pNode;
}

void Collection::saveData(string* buffer)
{
    string str = string();
    stringstream ss;
    ss << "\"cm_index\":";
    ss << this->getCmIndex();
    ss << ",";
    ss << "\"x_inc\":";
    ss << this->getIncX();
    ss << ",";
    ss << "\"y_inc\":";
    ss << this->getIncY();
    ss << ",";
    ss >> str;
    buffer->append(str);
}