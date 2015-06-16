//
//  EditorDetailMenu.cpp
//  CoolRun
//
//  Created by ManYou on 15/1/31.
//
//

#include "EditorDetailMenu.h"
#include "EditorUIBase.h"
#include "EditorZOrder.h"
#include "Spider.h"
#include "SpiderPoison.h"
#include "Bullet.h"
#include "Item.h"
#include "MYMultiLanguageManager.h"

EditorDetailMenu::EditorDetailMenu()
: EditorMenu()
, m_pNodeCor(nullptr)
, m_delete(nullptr)
, m_posX(nullptr)
, m_posY(nullptr)
, m_y(0.0f)
{
    
}
EditorDetailMenu::~EditorDetailMenu()
{
    CC_SAFE_RELEASE_NULL(m_pNodeCor);
}

bool EditorDetailMenu::init()
{
    if (!EditorMenu::init())
    {
        return false;
    }
    
    this->setMenuType(EditorMenu::MenuType::DETAIL);
    
    auto csize = Size(420, 2000);
    this->setContentSize(csize);
    
    this->getTouchListener()->setSwallowTouches(false);
    
    auto layer = LayerColor::create(Color4B(100, 20, 100, 255), csize.width, csize.height);
    this->addChild(layer);
    
    m_y = csize.height - 120;
    
    m_delete = EditorText::create(
                                  MYMultiLanguageManager::getInstance()->getText("e_delete"),
                                  Size(260, 60),
                                  30
                                  );
    m_delete->setPosition(Vec2(50, m_y));
    m_delete->touchNoneMoveEnded = CC_CALLBACK_0(EditorDetailMenu::deleteEditorNode, this);
    this->addChild(m_delete);
    BIGDIS(m_y);
    
    m_posX = EditorTextInput::create("x", Size(260, 60));
    m_posX->setPosition(Vec2(50, m_y));
    m_posX->textInputDone = CC_CALLBACK_1(EditorDetailMenu::textInputDone, this, m_posX);
    this->addChild(m_posX);
    NORMALDIS(m_y);
    m_posY = EditorTextInput::create("y", Size(260, 60));
    m_posY->setPosition(Vec2(50, m_y));
    m_posY->textInputDone = CC_CALLBACK_1(EditorDetailMenu::textInputDone, this, m_posY);
    this->addChild(m_posY);
    BIGDIS(m_y);
    
    return true;
}

void EditorDetailMenu::setPhysicNodeContaner(EditorPhysicNodeContainer* pNodeCor)
{
    if (m_pNodeCor != pNodeCor)
    {
        if (m_pNodeCor)
        {
            CC_SAFE_RELEASE_NULL(m_pNodeCor);
        }
        m_pNodeCor = pNodeCor;
        CC_SAFE_RETAIN(m_pNodeCor);
    }
    //auto pType = m_pNodeCor->getPhysicType();
    
}

void EditorDetailMenu::updateMenu()
{
//    Size visibleSize = Director::getInstance()->getVisibleSize();
//    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    if (m_pNodeCor)
    {
        stringstream ss;
        string str;
        
//        auto pNode = m_pNodeCor->getPhysicNode();
//        auto pType = m_pNodeCor->getPhysicType();
        
        auto pos = m_pNodeCor->getPosition();
        ss << pos.x;
        ss >> str;
        m_posX->setText(str);
        ss.clear();
        ss << pos.y;
        ss >> str;
        m_posY->setText(str);
        ss.clear();
        
       
    }
}
#pragma mark - 
void EditorDetailMenu::deleteEditorNode()
{
    this->getEditorListener()->removeEditorPhysicNodeContainer(m_pNodeCor);
    m_pNodeCor = nullptr;
}

void EditorDetailMenu::textInputDone(const string& text, EditorTextInput* input)
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    stringstream ss;
    auto pNode = m_pNodeCor->getPhysicNode();
    if (input == m_posX)
    {
        float f = 0.0f;
        ss << text;
        ss >> f;
        auto pos = m_pNodeCor->getPosition();
        pos.x = f;
        if (pNode->isScreenPos())
        {
            pos.x += visibleSize.width * pNode->getAlignX();
        }
        m_pNodeCor->setPosition(pos);
    }
    else if(input == m_posY)
    {
        float f = 0.0f;
        ss << text;
        ss >> f;
        auto pos = m_pNodeCor->getPosition();
        pos.y = f;
        if (pNode->isScreenPos())
        {
            pos.y += visibleSize.height * pNode->getAlignY();
        }
        m_pNodeCor->setPosition(pos);
    }
}

void EditorDetailMenu::selectedActive(EditorSelector* selector)
{
    selector->setLocalZOrder(kSelectorActiveZOrder);
}

void EditorDetailMenu::selectedDone(const string& key, EditorSelector* selector)
{
    //log("selectedDone :  %s", key.c_str());
    selector->setLocalZOrder(kSelectorUnActiveZOrder);
}

void EditorDetailMenu::spaceCallback()
{
    //this->getEditorListener()->hideMenu(EditorListener::MenuState::FIRST);
}