//
//  EditorPhysicNodeContainer.cpp
//  CoolRun
//
//  Created by ManYou on 15/1/29.
//
//

#include "EditorPhysicNodeContainer.h"
#include "EditorDetailMenu.h"
#include "EditorDetailAllMenu.h"
#include "EditorDetailSimpleMenu.h"
#include "Collection.h"

#define kBasePhysicNodeJsonDataFileFormat "Editor/Base/Object/Obj%04d"
#define kBaseCollecionPNJsonDataFileFormat "Editor/Base/Collection/Col%04d"

EditorPhysicNodeContainer::EditorPhysicNodeContainer()
: EditorNode()
, m_pNode(nullptr)
, b_isMenu(false)
, m_detailMenu(nullptr)
, m_pType(kPhysicNodeUnknown)
, m_frame(nullptr)
{
    
}
EditorPhysicNodeContainer::~EditorPhysicNodeContainer()
{
    CC_SAFE_RELEASE_NULL(m_detailMenu);
}

bool EditorPhysicNodeContainer::init()
{
    if (!EditorNode::init())
    {
        return false;
    }
    auto csize = this->getContentSize();
    
    m_frame = Scale9Sprite::createWithSpriteFrameName("editorFrame_node.png");
    m_frame->setPreferredSize(csize);
    m_frame->setAnchorPoint(Vec2::ZERO);
    this->addChild(m_frame);
    
    return true;
}

bool EditorPhysicNodeContainer::init(const Size& csize, PhysicNode* pNode)
{
    if (!this->init())
    {
        return false;
    }
    
    b_isMenu = true;
    
    this->setContentSize(csize);
    
    auto bg = Scale9Sprite::createWithSpriteFrameName("editorFrame_bg.png");
    bg->setAnchorPoint(Vec2::ZERO);
    bg->setPreferredSize(csize);
    this->addChild(bg);
    
    this->setPhysicNode(pNode);
    
    m_frame->setVisible(false);
    
    return true;
}

bool EditorPhysicNodeContainer::init(PhysicNode* pNode)
{
    if (!this->init())
    {
        return false;
    }
    b_isMenu = false;
    auto csize = pNode->getContentSize();
    this->setContentSize(csize);
    
    this->setPhysicNode(pNode);
    
    return true;
}

void EditorPhysicNodeContainer::setContentSize(const Size& _size)
{
    EditorNode::setContentSize(_size);
    if (!b_isMenu)
    {
        m_frame->setPreferredSize(_size);
    }
}

void EditorPhysicNodeContainer::setPhysicNode(PhysicNode* pNode)
{
    if (m_pNode)
    {
        m_pNode->removeFromParentAndCleanup(true);
        m_pNode = nullptr;
    }
    auto csize = this->getContentSize();
    
    m_pNode = pNode;
    if (b_isMenu)
    {
        
        auto pSize = m_pNode->getContentSize();
        float x_s = (csize.width-30) / pSize.width;
        float y_s = (csize.height-30) / pSize.height;
        float scale = x_s > y_s ? y_s : x_s;
        m_pNode->setScale(scale);
        m_pNode->setAnchorPoint(Vec2(0.5, 0.5));
        m_pNode->setPosition(Vec2(csize.width/2, csize.height/2));
    }
    else
    {
        m_pNode->setPosition(Vec2(0, 0));
    }
    this->setPhysicNodeType(m_pNode->getPhysicType());
    auto zOrder = m_pNode->getLocalZOrder();
    this->setZOrder(zOrder);
    this->addChild(m_pNode);
}

void EditorPhysicNodeContainer::savePhysicNodeInfo(string* buffer)
{
    string str = string();
    stringstream ss;

    auto data = new string();
    m_pNode->saveData(data);
    buffer->append(data->c_str());
    delete data;
    
    auto pos = this->getPosition();
    ss << "\"pos\":{";
    ss << "\"x\":";
    ss << pos.x;
    ss << ",";
    ss << "\"y\":";
    ss << pos.y;
    ss << "},";
    
    auto csize = this->getContentSize();
    ss << "\"cSize\":{";
    ss << "\"w\":";
    ss << csize.width;
    ss << ",";
    ss << "\"h\":";
    ss << csize.height;
    ss << "}";
    
    ss >> str;
    buffer->append(str);
}

void EditorPhysicNodeContainer::setDetailMenu(EditorDetailMenu* dMenu)
{
    CC_SAFE_RELEASE_NULL(m_detailMenu);
    m_detailMenu = dMenu;
    CC_SAFE_RETAIN(m_detailMenu);
}

#pragma mark - help
void EditorPhysicNodeContainer::_showDetailMenu()
{
    if (m_detailMenu)
    {
        this->getEditorListener()->showMenu(EditorListener::MenuState::FIRST, EditorMenu::create());
        this->getEditorListener()->showMenu(EditorListener::MenuState::FIRST, m_detailMenu);
    }
    else
    {
        auto menu = EditorDetailSimpleMenu::create();
        menu->setPhysicNodeContaner(this);
        this->setDetailMenu(menu);
        this->getEditorListener()->showMenu(EditorListener::MenuState::FIRST, EditorMenu::create());
        this->getEditorListener()->showMenu(EditorListener::MenuState::FIRST, menu);
    }
    
    
//    auto dMenu = dynamic_cast<EditorDetailMenu*>(this->getEditorListener()->getMenu(EditorListener::MenuState::FIRST));
//    this->setDetailMenu(dMenu);
}


#pragma mark - touch event

void EditorPhysicNodeContainer::editorNodeTouchBegan()
{
    //this->setDetailMenu(nullptr);
    if (b_isMenu)
    {
        return;
    }
    this->_showDetailMenu();
}

void EditorPhysicNodeContainer::editorNodeTouchMoved(int x, int y)
{
    if (b_isMenu)
    {
        return;
    }
    auto pos = this->getPosition();
    pos.x += x;
    pos.y += y;
    this->setPosition(pos);
    
//    auto dMenu = dynamic_cast<EditorDetailMenu*>(this->getEditorListener()->getMenu(EditorListener::MenuState::FIRST));
//    if (dMenu != m_detailMenu)
//    {
//        this->getEditorListener()->showMenu(EditorListener::MenuState::FIRST, m_detailMenu);
//    }
    if (m_detailMenu)
    {
        m_detailMenu->updateMenu();
    }
}

void EditorPhysicNodeContainer::editorNodeNoneMoveEnded()
{
    if (b_isMenu)
    {
        return;
    }
    this->_showDetailMenu();
}
void EditorPhysicNodeContainer::editorNodeMoveEnded()
{
    if (b_isMenu)
    {
        return;
    }
    this->_showDetailMenu();
}

#pragma mark -  static

EditorPhysicNodeContainer* EditorPhysicNodeContainer::create(PhysicNode* pNode)
{
    auto epnc = new EditorPhysicNodeContainer();
    if (epnc && epnc->init(pNode))
    {
        epnc->autorelease();
        return epnc;
    }
    delete epnc;
    return nullptr;
}

EditorPhysicNodeContainer* EditorPhysicNodeContainer::create(const Size& csize, PhysicNode* pNode)
{
    auto epnc = new EditorPhysicNodeContainer();
    if (epnc && epnc->init(csize, pNode))
    {
        epnc->autorelease();
        return epnc;
    }
    delete epnc;
    return nullptr;
}

PhysicNode* EditorPhysicNodeContainer::createBasePhysicNode(PhysicNodeType type)
{
    if (type < 1 || type >= kPhysicNodeTypeCount )
    {
        CCASSERT(0, "PhysicNodeType ERROR!");
    }

    char ca[80] = {'\0'};
    sprintf(ca, kBasePhysicNodeJsonDataFileFormat, type);
    string info = FileUtils::getInstance()->getStringFromFile(ca);
    
    rapidjson::Document doc;
    doc.Parse<0>(info.c_str());
    if (doc.HasParseError())
    {
        CCASSERT(false, "json parse error");
    }
    
    auto obj = PhysicNodeFactory::getInstance()->create(doc);
    obj->setForEditor(true);
    return obj;
}
PhysicNode* EditorPhysicNodeContainer::createBaseCollectionPhysicNode(int cmIndx)
{
    char ca[80] = {'\0'};
    sprintf(ca, kBaseCollecionPNJsonDataFileFormat, cmIndx);
    
    string info = FileUtils::getInstance()->getStringFromFile(ca);
//    log("File : %s", info.c_str());
//    log("INFO : %s", info.c_str());
    rapidjson::Document doc;
    doc.Parse<0>(info.c_str());
    if (doc.HasParseError())
    {
        CCASSERT(false, "json parse error");
    }
    auto collection = Collection::create();
    collection->loadJson(doc);
    auto pNode = collection->createEditorPhysicNode();
    return pNode;
}
Collection* EditorPhysicNodeContainer::createBaseCollection(int cmIndx)
{
    char ca[80] = {'\0'};
    sprintf(ca, kBaseCollecionPNJsonDataFileFormat, cmIndx);
    
    string info = FileUtils::getInstance()->getStringFromFile(ca);
//    log("File : %s", info.c_str());
//    log("INFO : %s", info.c_str());
    rapidjson::Document doc;
    doc.Parse<0>(info.c_str());
    if (doc.HasParseError())
    {
        CCASSERT(false, "json parse error");
    }
    auto collection = Collection::create();
    collection->loadJson(doc);
    return collection;
}