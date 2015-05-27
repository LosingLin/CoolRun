//
//  EditorDetailSimpleMenu.cpp
//  CoolRun
//
//  Created by ManYou on 15/5/11.
//
//

#include "EditorDetailSimpleMenu.h"
#include "EditorUIBase.h"
#include "EditorZOrder.h"
#include "Spider.h"
#include "SpiderPoison.h"
#include "Bullet.h"
#include "Item.h"
#include "MYMultiLanguageManager.h"

EditorDetailSimpleMenu::EditorDetailSimpleMenu()
: EditorDetailMenu()
, m_csizeWidth(nullptr)
, m_x_v(nullptr)
, m_x_a(nullptr)
, m_spideState(nullptr)
, m_spiderPosionDir(nullptr)
//, m_flyV(nullptr)
{
    
}
EditorDetailSimpleMenu::~EditorDetailSimpleMenu()
{
    CC_SAFE_RELEASE_NULL(m_pNodeCor);
}

bool EditorDetailSimpleMenu::init()
{
    if (!EditorDetailMenu::init())
    {
        return false;
    }
    
    
    m_x_v = EditorTextInput::create(
                                    MYMultiLanguageManager::getInstance()->getText("e_x_v"),
                                    Size(260, 60)
                                    );
    m_x_v->setPosition(Vec2(50, m_y));
    m_x_v->textInputDone = CC_CALLBACK_1(EditorDetailSimpleMenu::textInputDone, this, m_x_v);
    this->addChild(m_x_v);
    NORMALDIS(m_y);
    m_x_a = EditorTextInput::create(
                                    MYMultiLanguageManager::getInstance()->getText("e_x_a"),
                                    Size(260, 60)
                                    );
    m_x_a->setPosition(Vec2(50, m_y));
    m_x_a->textInputDone = CC_CALLBACK_1(EditorDetailSimpleMenu::textInputDone, this, m_x_a);
    this->addChild(m_x_a);
    BIGDIS(m_y);
    
    
    
    
    return true;
}

void EditorDetailSimpleMenu::setPhysicNodeContaner(EditorPhysicNodeContainer* pNodeCor)
{
    EditorDetailMenu::setPhysicNodeContaner(pNodeCor);
    
    auto pType = m_pNodeCor->getPhysicType();
    if (pType == kPhysicNodeStone)
    {
        m_csizeWidth = EditorTextInput::create(
                                               MYMultiLanguageManager::getInstance()->getText("e_width"),
                                               Size(260, 60)
                                               );
        m_csizeWidth->setPosition(Vec2(50, m_y));
        m_csizeWidth->textInputDone = CC_CALLBACK_1(EditorDetailSimpleMenu::textInputDone, this, m_csizeWidth);
        this->addChild(m_csizeWidth);
        BIGDIS(m_y);
    }
    else
    {
        if (m_csizeWidth)
        {
            m_csizeWidth->removeFromParentAndCleanup(true);
            m_csizeWidth = nullptr;
        }
    }
    if (pType == kPhysicNodeSpiderKind || pType == kPhysicNodeSpiderPoison || pType == kPhysicNodeSpiderSpines) {
        m_spideState = EditorSelector::create(__Array::create(
                                                              __String::create(MYMultiLanguageManager::getInstance()->getText("e_ssStand")),
                                                              __String::create(MYMultiLanguageManager::getInstance()->getText("e_ssWalk")),
                                                              nullptr),
                                              MYMultiLanguageManager::getInstance()->getText("e_spiderStatus"),
                                              Size(260, 60));
        m_spideState->active = CC_CALLBACK_1(EditorDetailSimpleMenu::selectedActive, this);
        m_spideState->selectedKey = CC_CALLBACK_1(EditorDetailSimpleMenu::selectedDone, this, m_spideState);
        m_spideState->setPosition(Vec2(50, m_y));
        this->addChild(m_spideState);
        if (pType == kPhysicNodeSpiderPoison)
        {
            NORMALDIS(m_y);
            m_spiderPosionDir = EditorSelector::create(__Array::create(
                                                                       __String::create(MYMultiLanguageManager::getInstance()->getText("e_pdUp")),
                                                                       __String::create(MYMultiLanguageManager::getInstance()->getText("e_pdDown")),
                                                                       __String::create(MYMultiLanguageManager::getInstance()->getText("e_pdLeft")),
                                                                       __String::create(MYMultiLanguageManager::getInstance()->getText("e_pdRight")),
                                                                       nullptr),
                                                       MYMultiLanguageManager::getInstance()->getText("e_poisonDir"),
                                                       Size(260, 60));
            m_spiderPosionDir->active = CC_CALLBACK_1(EditorDetailSimpleMenu::selectedActive, this);
            m_spiderPosionDir->selectedKey = CC_CALLBACK_1(EditorDetailSimpleMenu::selectedDone, this, m_spiderPosionDir);
            m_spiderPosionDir->setPosition(Vec2(50, m_y));
            this->addChild(m_spiderPosionDir);
            
        }
        BIGDIS(m_y);
        
    }
    else
    {
        if (m_spideState)
        {
            m_spideState->removeFromParentAndCleanup(true);
            m_spideState = nullptr;
        }
    }
   
//    if (pType == kPhysicNodeItemDad || pType == kPhysicNodeItemFly || pType == kPhysicNodeItemLandBuild ||
//        pType == kPhysicNodeItemMagnet || pType == kPhysicNodeItemSpare || pType == kPhysicNodeItemTimesCoin ||
//        pType == kPhysicNodeItemTimesJump)
//    {
//        m_flyV = EditorTextInput::create("fly_v", Size(260, 60));
//        m_flyV->setPosition(Vec2(50, m_y));
//        m_flyV->textInputDone = CC_CALLBACK_1(EditorDetailSimpleMenu::textInputDone, this, m_flyV);
//        this->addChild(m_flyV);
//        BIGDIS(m_y);
//    }
//    else
//    {
//        if (m_flyV)
//        {
//            m_flyV->removeFromParentAndCleanup(true);
//            m_flyV = nullptr;
//        }
//    }
    this->updateMenu();
}

void EditorDetailSimpleMenu::updateMenu()
{
    EditorDetailMenu::updateMenu();
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    if (m_pNodeCor)
    {
        stringstream ss;
        string str;
        
        auto pNode = m_pNodeCor->getPhysicNode();
        auto pType = m_pNodeCor->getPhysicType();
        
       
        
        auto xv = pNode->getXV();
        ss << xv;
        ss >> str;
        m_x_v->setText(str);
        ss.clear();
        auto xa = pNode->getXA();
        ss << xa;
        ss >> str;
        m_x_a->setText(str);
        ss.clear();
        
        if (pType == kPhysicNodeStone)
        {
            stringstream ss;
            string str;
            
            auto csize = m_pNodeCor->getContentSize();
            ss << csize.width;
            ss >> str;
            m_csizeWidth->setText(str);
            ss.clear();
        }
        
        if (pType == kPhysicNodeSpiderKind || pType == kPhysicNodeSpiderPoison || pType == kPhysicNodeSpiderSpines) {
            auto cPNode = dynamic_cast<Spider*>(pNode);
            auto state = cPNode->getState();
            switch (state)
            {
                case kSpiderState_Stand:
                    m_spideState->setSelected(MYMultiLanguageManager::getInstance()->getText("e_ssStand"));
                    break;
                case kSpiderState_Walk:
                    m_spideState->setSelected(MYMultiLanguageManager::getInstance()->getText("e_ssWalk"));
                    break;
                default:
                    break;
            }
            if (pType == kPhysicNodeSpiderPoison)
            {
                auto ccPNode = dynamic_cast<SpiderPoison*>(pNode);
                auto dir = ccPNode->getAtkDirection();
                switch (dir)
                {
                    case kCRDirectionUp:
                        m_spiderPosionDir->setSelected(MYMultiLanguageManager::getInstance()->getText("e_pdUp"));
                        break;
                    case kCRDirectionDown:
                        m_spiderPosionDir->setSelected(MYMultiLanguageManager::getInstance()->getText("e_pdDown"));
                        break;
                    case kCRDirectionLeft:
                        m_spiderPosionDir->setSelected(MYMultiLanguageManager::getInstance()->getText("e_pdLeft"));
                    case kCRDirectionRight:
                        m_spiderPosionDir->setSelected(MYMultiLanguageManager::getInstance()->getText("e_pdRight"));
                    default:
                        break;
                }
            }
        }
        
//        if (pType == kPhysicNodeItemDad || pType == kPhysicNodeItemFly || pType == kPhysicNodeItemLandBuild ||
//            pType == kPhysicNodeItemMagnet || pType == kPhysicNodeItemSpare || pType == kPhysicNodeItemTimesCoin ||
//            pType == kPhysicNodeItemTimesJump)
//        {
//            auto cPNode = dynamic_cast<Item*>(pNode);
//            auto flyv = cPNode->getFlyVelcity();
//            ss << flyv;
//            ss >> str;
//            m_flyV->setText(str);
//            ss.clear();
//        }
    }
}

#pragma mark -
void EditorDetailSimpleMenu::textInputDone(const string& text, EditorTextInput* input)
{
    EditorDetailMenu::textInputDone(text, input);
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    stringstream ss;
    auto pNode = m_pNodeCor->getPhysicNode();
    if (input == m_csizeWidth)
    {
        float f = 0.0f;
        ss << text;
        ss >> f;
        if (f < 20)
        {
            f = 20;
            input->setText("20");
        }
        auto csize = m_pNodeCor->getContentSize();
        csize.width = f;
        m_pNodeCor->setContentSize(csize);
        pNode->setContentSize(csize);
    }
    
    else if (input == m_x_v)
    {
        float f = 0.0f;
        ss << text;
        ss >> f;
        pNode->setXV(f);
    }
    else if (input == m_x_a)
    {
        float f = 0.0f;
        ss << text;
        ss >> f;
        pNode->setXA(f);
    }
    
//    else if (input == m_flyV)
//    {
//        float f = 0.0f;
//        ss << text;
//        ss >> f;
//        auto cPNode = dynamic_cast<Item*>(pNode);
//        cPNode->setFlyVelcity(f);
//    }
}

void EditorDetailSimpleMenu::selectedActive(EditorSelector* selector)
{
    EditorDetailMenu::selectedActive(selector);
    
}

void EditorDetailSimpleMenu::selectedDone(const string& key, EditorSelector* selector)
{
    EditorDetailMenu::selectedDone(key, selector);
    
    auto pNode = m_pNodeCor->getPhysicNode();
    if (selector == m_spideState)
    {
        auto cPNode = dynamic_cast<Spider*>(pNode);
        if (MYMultiLanguageManager::getInstance()->getText("e_ssStand") == key)
        {
            cPNode->setState(kSpiderState_Stand);
        }
        else
        {
            cPNode->setState(kSpiderState_Walk);
        }
    }
    else if (selector == m_spiderPosionDir)
    {
        auto cPNode = dynamic_cast<SpiderPoison*>(pNode);
        if (MYMultiLanguageManager::getInstance()->getText("e_pdUp") == key)
        {
            cPNode->setAtkDirection(CRDirection::kCRDirectionUp);
        }
        else if (MYMultiLanguageManager::getInstance()->getText("e_pdDown") == key)
        {
            cPNode->setAtkDirection(CRDirection::kCRDirectionDown);
        }
        else if (MYMultiLanguageManager::getInstance()->getText("e_pdLeft") == key)
        {
            cPNode->setAtkDirection(CRDirection::kCRDirectionLeft);
        }
        else if (MYMultiLanguageManager::getInstance()->getText("e_pdRight") == key)
        {
            cPNode->setAtkDirection(CRDirection::kCRDirectionRight);
        }
    }
}

void EditorDetailSimpleMenu::spaceCallback()
{
    //this->getEditorListener()->hideMenu(EditorListener::MenuState::FIRST);
}