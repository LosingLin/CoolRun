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

#define NORMALDIS(x) (x) -= 80
#define BIGDIS(x) (x) -= 120

EditorDetailMenu::EditorDetailMenu()
: EditorMenu()
, m_pNodeCor(nullptr)
, m_delete(nullptr)
, m_posX(nullptr)
, m_posY(nullptr)
, m_csizeWidth(nullptr)
, m_csizeHeight(nullptr)
, m_x_v(nullptr)
, m_x_a(nullptr)
, m_y_v(nullptr)
, m_y_a(nullptr)
, m_alignX(nullptr)
, m_alignY(nullptr)
//, m_cR_left(nullptr)
//, m_cR_down(nullptr)
//, m_cR_right(nullptr)
//, m_cR_up(nullptr)
, m_isScreenPos(nullptr)
, m_isGEffect(nullptr)
, m_isCEffect(nullptr)
, m_isVIgnore(nullptr)
, m_cType(nullptr)
, m_y(0.0f)
, m_spideState(nullptr)
, m_spiderPosionDir(nullptr)
, m_isAnimalHurt(nullptr)
, m_isRunnerHurt(nullptr)
, m_isAtkable(nullptr)
, m_flyV(nullptr)
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
    
    auto layer = LayerColor::create(Color4B(200, 200, 20, 150), csize.width, csize.height);
    this->addChild(layer);
    
    m_y = csize.height - 120;
    
    m_delete = EditorText::create("Delete", Size(260, 60), 30);
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
    
    
    m_csizeWidth = EditorTextInput::create("width", Size(260, 60));
    m_csizeWidth->setPosition(Vec2(50, m_y));
    m_csizeWidth->textInputDone = CC_CALLBACK_1(EditorDetailMenu::textInputDone, this, m_csizeWidth);
    this->addChild(m_csizeWidth);
    NORMALDIS(m_y);
    m_csizeHeight = EditorTextInput::create("height", Size(260, 60));
    m_csizeHeight->setPosition(Vec2(50, m_y));
    m_csizeHeight->textInputDone = CC_CALLBACK_1(EditorDetailMenu::textInputDone, this, m_csizeHeight);
    this->addChild(m_csizeHeight);
    BIGDIS(m_y);
    
    //v
    m_isVIgnore = EditorSelector::create(__Array::create(
                                                         __String::create("Y"),
                                                         __String::create("N"),
                                                         nullptr),
                                         "isVIgn",
                                         Size(260, 60));
    m_isVIgnore->active = CC_CALLBACK_1(EditorDetailMenu::selectedActive, this);
    m_isVIgnore->selectedKey = CC_CALLBACK_1(EditorDetailMenu::selectedDone, this, m_isVIgnore);
    m_isVIgnore->setPosition(Vec2(50, m_y));
    this->addChild(m_isVIgnore);
    NORMALDIS(m_y);
    m_x_v = EditorTextInput::create("x_v", Size(260, 60));
    m_x_v->setPosition(Vec2(50, m_y));
    m_x_v->textInputDone = CC_CALLBACK_1(EditorDetailMenu::textInputDone, this, m_x_v);
    this->addChild(m_x_v);
    NORMALDIS(m_y);
    m_x_a = EditorTextInput::create("x_a", Size(260, 60));
    m_x_a->setPosition(Vec2(50, m_y));
    m_x_a->textInputDone = CC_CALLBACK_1(EditorDetailMenu::textInputDone, this, m_x_a);
    this->addChild(m_x_a);
    NORMALDIS(m_y);
    m_y_v = EditorTextInput::create("y_v", Size(260, 60));
    m_y_v->setPosition(Vec2(50, m_y));
    m_y_v->textInputDone = CC_CALLBACK_1(EditorDetailMenu::textInputDone, this, m_y_v);
    this->addChild(m_y_v);
    NORMALDIS(m_y);
    m_y_a = EditorTextInput::create("y_a", Size(260, 60));
    m_y_a->setPosition(Vec2(50, m_y));
    m_y_a->textInputDone = CC_CALLBACK_1(EditorDetailMenu::textInputDone, this, m_y_a);
    this->addChild(m_y_a);
    BIGDIS(m_y);
    
//    m_cR_left = EditorTextInput::create("cRleft", Size(260, 60));
//    m_cR_left->setPosition(Vec2(50, m_y));
//    m_cR_left->textInputDone = CC_CALLBACK_1(EditorDetailMenu::textInputDone, this, m_cR_left);
//    this->addChild(m_cR_left);
//    NORMALDIS(m_y);
//    m_cR_down = EditorTextInput::create("cRDown", Size(260, 60));
//    m_cR_down->setPosition(Vec2(50, m_y));
//    m_cR_down->textInputDone = CC_CALLBACK_1(EditorDetailMenu::textInputDone, this, m_cR_down);
//    this->addChild(m_cR_down);
//    NORMALDIS(m_y);
//    m_cR_right = EditorTextInput::create("cRRight", Size(260, 60));
//    m_cR_right->setPosition(Vec2(50, m_y));
//    m_cR_right->textInputDone = CC_CALLBACK_1(EditorDetailMenu::textInputDone, this, m_cR_right);
//    this->addChild(m_cR_right);
//    NORMALDIS(m_y);
//    m_cR_up = EditorTextInput::create("cRUp", Size(260, 60));
//    m_cR_up->setPosition(Vec2(50, m_y));
//    m_cR_up->textInputDone = CC_CALLBACK_1(EditorDetailMenu::textInputDone, this, m_cR_up);
//    this->addChild(m_cR_up);
//    BIGDIS(m_y);
    
    m_isScreenPos = EditorSelector::create(__Array::create(
                                                           __String::create("Y"),
                                                           __String::create("N"),
                                                           nullptr),
                                           "isScrPos",
                                           Size(260, 60));
    m_isScreenPos->active = CC_CALLBACK_1(EditorDetailMenu::selectedActive, this);
    m_isScreenPos->selectedKey = CC_CALLBACK_1(EditorDetailMenu::selectedDone, this, m_isScreenPos);
    m_isScreenPos->setPosition(Vec2(50, m_y));
    this->addChild(m_isScreenPos);
    NORMALDIS(m_y);
    m_alignX = EditorTextInput::create("align_x", Size(260, 60));
    m_alignX->setPosition(Vec2(50, m_y));
    m_alignX->textInputDone = CC_CALLBACK_1(EditorDetailMenu::textInputDone, this, m_alignX);
    this->addChild(m_alignX);
    NORMALDIS(m_y);
    m_alignY = EditorTextInput::create("align_y", Size(260, 60));
    m_alignY->setPosition(Vec2(50, m_y));
    m_alignY->textInputDone = CC_CALLBACK_1(EditorDetailMenu::textInputDone, this, m_alignY);
    this->addChild(m_alignY);
    BIGDIS(m_y);
    
    m_isGEffect = EditorSelector::create(__Array::create(
                                                           __String::create("Y"),
                                                           __String::create("N"),
                                                           nullptr),
                                           "isGEff",
                                           Size(260, 60));
    m_isGEffect->active = CC_CALLBACK_1(EditorDetailMenu::selectedActive, this);
    m_isGEffect->selectedKey = CC_CALLBACK_1(EditorDetailMenu::selectedDone, this, m_isGEffect);
    m_isGEffect->setPosition(Vec2(50, m_y));
    this->addChild(m_isGEffect);
    NORMALDIS(m_y);
    m_isCEffect = EditorSelector::create(__Array::create(
                                                           __String::create("Y"),
                                                           __String::create("N"),
                                                           nullptr),
                                           "isCEff",
                                           Size(260, 60));
    m_isCEffect->active = CC_CALLBACK_1(EditorDetailMenu::selectedActive, this);
    m_isCEffect->selectedKey = CC_CALLBACK_1(EditorDetailMenu::selectedDone, this, m_isCEffect);
    m_isCEffect->setPosition(Vec2(50, m_y));
    this->addChild(m_isCEffect);
    NORMALDIS(m_y);
    
    m_cType = EditorSelector::create(__Array::create(
                                                           __String::create("Non"),
                                                           __String::create("Dir"),
                                                           __String::create("Sim"),
                                                           __String::create("Bul"),
                                                           nullptr),
                                           "colide_type",
                                           Size(260, 60));
    m_cType->active = CC_CALLBACK_1(EditorDetailMenu::selectedActive, this);
    m_cType->selectedKey = CC_CALLBACK_1(EditorDetailMenu::selectedDone, this, m_cType);
    m_cType->setPosition(Vec2(50, m_y));
    this->addChild(m_cType);
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
    auto pType = m_pNodeCor->getPhysicType();
    if (pType == kPhysicNodeSpiderKind || pType == kPhysicNodeSpiderPoison || pType == kPhysicNodeSpiderSpines) {
        m_spideState = EditorSelector::create(__Array::create(
                                                         __String::create("Stand"),
                                                         __String::create("Walk"),
                                                         nullptr),
                                         "spider_state",
                                         Size(260, 60));
        m_spideState->active = CC_CALLBACK_1(EditorDetailMenu::selectedActive, this);
        m_spideState->selectedKey = CC_CALLBACK_1(EditorDetailMenu::selectedDone, this, m_spideState);
        m_spideState->setPosition(Vec2(50, m_y));
        this->addChild(m_spideState);
        if (pType == kPhysicNodeSpiderPoison)
        {
            NORMALDIS(m_y);
            m_spiderPosionDir = EditorSelector::create(__Array::create(
                                                                  __String::create("Up"),
                                                                  __String::create("Down"),
                                                                  __String::create("Left"),
                                                                  __String::create("Right"),
                                                                  nullptr),
                                                  "PoisonDirector",
                                                  Size(260, 60));
            m_spiderPosionDir->active = CC_CALLBACK_1(EditorDetailMenu::selectedActive, this);
            m_spiderPosionDir->selectedKey = CC_CALLBACK_1(EditorDetailMenu::selectedDone, this, m_spiderPosionDir);
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
    if (pType == kPhysicNodeBulletPoison || pType == kPhysicNodeBulletAlertPoison || pType == kPhysicNodeBulletAlertNet)
    {
        m_isAnimalHurt = EditorSelector::create(__Array::create(
                                                              __String::create("Y"),
                                                              __String::create("N"),
                                                              nullptr),
                                              "animal_hurt",
                                              Size(260, 60));
        m_isAnimalHurt->active = CC_CALLBACK_1(EditorDetailMenu::selectedActive, this);
        m_isAnimalHurt->selectedKey = CC_CALLBACK_1(EditorDetailMenu::selectedDone, this, m_isAnimalHurt);
        m_isAnimalHurt->setPosition(Vec2(50, m_y));
        this->addChild(m_isAnimalHurt);
        NORMALDIS(m_y);
        m_isRunnerHurt = EditorSelector::create(__Array::create(
                                                              __String::create("Y"),
                                                              __String::create("N"),
                                                              nullptr),
                                              "player_hurt",
                                              Size(260, 60));
        m_isRunnerHurt->active = CC_CALLBACK_1(EditorDetailMenu::selectedActive, this);
        m_isRunnerHurt->selectedKey = CC_CALLBACK_1(EditorDetailMenu::selectedDone, this, m_isRunnerHurt);
        m_isRunnerHurt->setPosition(Vec2(50, m_y));
        this->addChild(m_isRunnerHurt);
        NORMALDIS(m_y);
        m_isAtkable = EditorSelector::create(__Array::create(
                                                             __String::create("Y"),
                                                             __String::create("N"),
                                                             nullptr),
                                             "atk_able",
                                             Size(260, 60));
        m_isAtkable->active = CC_CALLBACK_1(EditorDetailMenu::selectedActive, this);
        m_isAtkable->selectedKey = CC_CALLBACK_1(EditorDetailMenu::selectedDone, this, m_isAtkable);
        m_isAtkable->setPosition(Vec2(50, m_y));
        this->addChild(m_isAtkable);
        BIGDIS(m_y);
    }
    else
    {
        if (m_isAnimalHurt)
        {
            m_isAnimalHurt->removeFromParentAndCleanup(true);
            m_isAnimalHurt = nullptr;
        }
        if (m_isRunnerHurt)
        {
            m_isRunnerHurt->removeFromParentAndCleanup(true);
            m_isRunnerHurt = nullptr;
        }
    }
    if (pType == kPhysicNodeItemDad || pType == kPhysicNodeItemFly || pType == kPhysicNodeItemLandBuild ||
        pType == kPhysicNodeItemMagnet || pType == kPhysicNodeItemSpare || pType == kPhysicNodeItemTimesCoin ||
        pType == kPhysicNodeItemTimesJump)
    {
        m_flyV = EditorTextInput::create("fly_v", Size(260, 60));
        m_flyV->setPosition(Vec2(50, m_y));
        m_flyV->textInputDone = CC_CALLBACK_1(EditorDetailMenu::textInputDone, this, m_flyV);
        this->addChild(m_flyV);
        BIGDIS(m_y);
    }
    else
    {
        if (m_flyV)
        {
            m_flyV->removeFromParentAndCleanup(true);
            m_flyV = nullptr;
        }
    }
    this->updateMenu();
}

void EditorDetailMenu::updateMenu()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    if (m_pNodeCor)
    {
        stringstream ss;
        string str;
        
        auto pNode = m_pNodeCor->getPhysicNode();
        auto pType = m_pNodeCor->getPhysicType();
        
        auto pos = m_pNodeCor->getPosition();
        ss << pos.x;
        ss >> str;
        m_posX->setText(str);
        ss.clear();
        ss << pos.y;
        ss >> str;
        m_posY->setText(str);
        ss.clear();
        
        auto csize = m_pNodeCor->getContentSize();
        ss << csize.width;
        ss >> str;
        m_csizeWidth->setText(str);
        ss.clear();
        ss << csize.height;
        ss >> str;
        m_csizeHeight->setText(str);
        ss.clear();
        
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
        auto yv = pNode->getYV();
        ss << yv;
        ss >> str;
        m_y_v->setText(str);
        ss.clear();
        auto ya = pNode->getYA();
        ss << ya;
        ss >> str;
        m_y_a->setText(str);
        ss.clear();
        auto alx = pNode->getAlignX();
        ss << alx;
        ss >> str;
        m_alignX->setText(str);
        ss.clear();
        auto aly = pNode->getAlignY();
        ss << aly;
        ss >> str;
        m_alignY->setText(str);
        ss.clear();
        
        if (pNode->isScreenPos())
        {
            m_isScreenPos->setSelected("Y");
        }
        else
        {
            m_isScreenPos->setSelected("N");
        }
        if (pNode->isGravityEffect())
        {
            m_isGEffect->setSelected("Y");
        }
        else
        {
            m_isGEffect->setSelected("N");
        }
        if (pNode->isCollideEffect())
        {
            m_isCEffect->setSelected("Y");
        }
        else
        {
            m_isCEffect->setSelected("N");
        }
        if (pNode->isVelocityIgnore())
        {
            m_isVIgnore->setSelected("Y");
        }
        else
        {
            m_isVIgnore->setSelected("N");
        }
        auto cType = pNode->getCollideType();
        switch (cType)
        {
            case kCollideTypeUnknown:
            {
                m_cType->setSelected("Non");
            }
                break;
            case kCollideTypeDirection:
            {
                m_cType->setSelected("Dir");
            }
                break;
            case kCollideTypeSimple:
            {
                m_cType->setSelected("Sim");
            }
                break;
            case kCollideTypeBullet:
            {
                m_cType->setSelected("Bul");
            }
                break;
                
            default:
                break;
        }
        
        if (pType == kPhysicNodeSpiderKind || pType == kPhysicNodeSpiderPoison || pType == kPhysicNodeSpiderSpines) {
            auto cPNode = dynamic_cast<Spider*>(pNode);
            auto state = cPNode->getState();
            switch (state)
            {
                case kSpiderState_Stand:
                    m_spideState->setSelected("Stand");
                    break;
                case kSpiderState_Walk:
                    m_spideState->setSelected("Walk");
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
                        m_spiderPosionDir->setSelected("Up");
                        break;
                    case kCRDirectionDown:
                        m_spiderPosionDir->setSelected("Down");
                        break;
                    case kCRDirectionLeft:
                        m_spiderPosionDir->setSelected("Left");
                    case kCRDirectionRight:
                        m_spiderPosionDir->setSelected("Right");
                    default:
                        break;
                }
            }
        }
        if (pType == kPhysicNodeBulletPoison || pType == kPhysicNodeBulletAlertPoison || pType == kPhysicNodeBulletAlertNet)
        {
            auto cPNode = dynamic_cast<Bullet*>(pNode);
            if (cPNode->isAnimalHurt())
            {
                m_isAnimalHurt->setSelected("Y");
            }
            else
            {
                m_isAnimalHurt->setSelected("N");
            }
            if (cPNode->isRunnerHurt())
            {
                m_isRunnerHurt->setSelected("Y");
            }
            else
            {
                m_isRunnerHurt->setSelected("N");
            }
            if (cPNode->isAtkable())
            {
                m_isAtkable->setSelected("Y");
            }
            else
            {
                m_isAtkable->setSelected("N");
            }
        }
        if (pType == kPhysicNodeItemDad || pType == kPhysicNodeItemFly || pType == kPhysicNodeItemLandBuild ||
            pType == kPhysicNodeItemMagnet || pType == kPhysicNodeItemSpare || pType == kPhysicNodeItemTimesCoin ||
            pType == kPhysicNodeItemTimesJump)
        {
            auto cPNode = dynamic_cast<Item*>(pNode);
            auto flyv = cPNode->getFlyVelcity();
            ss << flyv;
            ss >> str;
            m_flyV->setText(str);
            ss.clear();
        }
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
    
    else if (input == m_csizeWidth)
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
    else if (input == m_csizeHeight)
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
        csize.height = f;
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
    else if (input == m_y_v)
    {
        float f = 0.0f;
        ss << text;
        ss >> f;
        pNode->setYV(f);
    }
    else if (input == m_y_a)
    {
        float f = 0.0f;
        ss << text;
        ss >> f;
        pNode->setYA(f);
    }
    else if (input == m_alignX)
    {
        float f = 0.0f;
        ss << text;
        ss >> f;
        pNode->setAlignX(f);
    }
    else if (input == m_alignY)
    {
        float f = 0.0f;
        ss << text;
        ss >> f;
        pNode->setAlignY(f);
    }
    else if (input == m_flyV)
    {
        float f = 0.0f;
        ss << text;
        ss >> f;
        auto cPNode = dynamic_cast<Item*>(pNode);
        cPNode->setFlyVelcity(f);
    }
}

void EditorDetailMenu::selectedActive(EditorSelector* selector)
{
    selector->setLocalZOrder(kSelectorActiveZOrder);
}

void EditorDetailMenu::selectedDone(const string& key, EditorSelector* selector)
{
    log("selectedDone :  %s", key.c_str());
    selector->setLocalZOrder(kSelectorUnActiveZOrder);
    auto pNode = m_pNodeCor->getPhysicNode();
    if (selector == m_isScreenPos)
    {
        if ("Y" == key)
        {
            pNode->setScreenPos(true);
        }
        else
        {
            pNode->setScreenPos(false);
        }
    }
    else if (selector == m_isGEffect)
    {
        if ("Y" == key)
        {
            pNode->setGravityEffect(true);
        }
        else
        {
            pNode->setGravityEffect(false);
        }
    }
    else if (selector == m_isCEffect)
    {
        if ("Y" == key)
        {
            pNode->setCollideEffect(true);
        }
        else
        {
            pNode->setCollideEffect(false);
        }
    }
    else if (selector == m_isVIgnore)
    {
        if ("Y" == key)
        {
            pNode->setVelocityIgnore(true);
        }
        else
        {
            pNode->setVelocityIgnore(false);
        }
    }
    else if (selector == m_cType)
    {
        if ("Dir" == key)
        {
            pNode->setCollideType(kCollideTypeDirection);
        }
        else if ("Sim" == key)
        {
            pNode->setCollideType(kCollideTypeSimple);
        }
        else if ("Bul" == key)
        {
            pNode->setCollideType(kCollideTypeBullet);
        }
        else
        {
            pNode->setCollideType(kCollideTypeUnknown);
        }
    }
    else if (selector == m_spideState)
    {
        auto cPNode = dynamic_cast<Spider*>(pNode);
        if ("Stand" == key)
        {
            cPNode->setState(kSpiderState_Stand);
        }
        else
        {
            cPNode->setState(kSpiderState_Walk);
        }
    }
    else if (selector == m_isAnimalHurt)
    {
        auto cPNode = dynamic_cast<Bullet*>(pNode);
        if ("Y" == key)
        {
            cPNode->setAnimalHurt(true);
        }
        else
        {
            cPNode->setAnimalHurt(false);
        }
    }
    else if (selector == m_isRunnerHurt)
    {
        auto cPNode = dynamic_cast<Bullet*>(pNode);
        if ("Y" == key)
        {
            cPNode->setRunnerHurt(true);
        }
        else
        {
            cPNode->setRunnerHurt(false);
        }
    }
    else if (selector == m_isAtkable)
    {
        auto cPNode = dynamic_cast<Bullet*>(pNode);
        if ("Y" == key)
        {
            cPNode->setAtkable(true);
        }
        else
        {
            cPNode->setAtkable(false);
        }
    }
    else if (selector == m_spiderPosionDir)
    {
        auto cPNode = dynamic_cast<SpiderPoison*>(pNode);
        if ("Up" == key)
        {
            cPNode->setAtkDirection(CRDirection::kCRDirectionUp);
        }
        else if ("Down" == key)
        {
            cPNode->setAtkDirection(CRDirection::kCRDirectionDown);
        }
        else if ("Left" == key)
        {
            cPNode->setAtkDirection(CRDirection::kCRDirectionLeft);
        }
        else if ("Right" == key)
        {
            cPNode->setAtkDirection(CRDirection::kCRDirectionRight);
        }
    }
}

void EditorDetailMenu::spaceCallback()
{
    //this->getEditorListener()->hideMenu(EditorListener::MenuState::FIRST);
}