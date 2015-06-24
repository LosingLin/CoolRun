//
//  NormalFrame.cpp
//  CoolRun
//
//  Created by ManYou on 15/5/16.
//
//

#include "NormalFrame.h"
#include "ResourceManager.h"

NormalFrame::NormalFrame()
: Node()
, m_closeBtn(nullptr)
, m_titleLab(nullptr)
{
    
}
NormalFrame::~NormalFrame()
{
    
}

bool NormalFrame::init(const Size& _size, const char* title, bool hasClose)
{
    if (!Node::init())
    {
        return false;
    }
    
    this->setContentSize(_size);
    
    auto bgframe = Scale9Sprite::createWithSpriteFrameName("frame.png");
    bgframe->setPreferredSize(Size(_size.width, _size.height-60));
    bgframe->setAnchorPoint(Vec2(0, 0));
    this->addChild(bgframe);
    
    if (hasClose)
    {
        m_closeBtn = MYButton::createWithFrameName("btn_close.png");
        m_closeBtn->setPosition(Vec2(_size.width - 110, _size.height - 170));
        //m_closeBtn->addTouchEventListener(CC_CALLBACK_2(FreshGuideLayer::closeBtnCallback, this));
        this->addChild(m_closeBtn);
    }
    
    m_titleLab = Label::createWithBMFont(ResourceManager::getInstance()->getFntRes("NFTitle"), title);
    m_titleLab->setAnchorPoint(Vec2(0.5, 0.5));
    m_titleLab->setPosition(Vec2(_size.width/2, _size.height-60));
    this->addChild(m_titleLab);
    
    return true;
}

void NormalFrame::updateBMFTitleLabel(const string& _bmf, const string& title)
{
    auto lab = Label::createWithBMFont(_bmf, title);
    lab->setAnchorPoint(Vec2(0.5, 0.5));
    lab->setPosition(m_titleLab->getPosition());
    this->addChild(lab);
    
    m_titleLab->removeFromParentAndCleanup(true);
    m_titleLab = nullptr;
    m_titleLab = lab;
}

void NormalFrame::addCloseCallback(MYButton::MYButtonCallback callback)
{
    if (m_closeBtn)
    {
        m_closeBtn->addTouchEventListener(callback);
    }
}

NormalFrame* NormalFrame::create(const  Size& _size, const char* title, bool hasClose)
{
    auto _frame = new NormalFrame();
    if (_frame && _frame->init(_size, title, hasClose))
    {
        _frame->autorelease();
        return _frame;
    }
    delete _frame;
    _frame = nullptr;
    return nullptr;
}