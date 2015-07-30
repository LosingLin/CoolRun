//
//  Jade.cpp
//  CoolRun
//
//  Created by ManYou on 15/6/24.
//
//

#include "JadeView.h"
#include "MYMultiLanguageManager.h"
#include "ResourceManager.h"

JadeView::JadeView()
: Node()
, m_numLab(nullptr)
{
    
}
JadeView::~JadeView()
{
    
}

bool JadeView::init()
{
    if (!Node::init())
    {
        return false;
    }
    
    auto csize = Size(240, 54);
    this->setContentSize(csize);
    
    auto bg = Scale9Sprite::createWithSpriteFrameName("num_bg.png");
    bg->setPreferredSize(csize);
    bg->setAnchorPoint(Vec2::ZERO);
    this->addChild(bg);
    
    auto jade_icon = Sprite::createWithSpriteFrameName("jade.png");
    jade_icon->setScale(0.5);
    jade_icon->setPosition(Vec2(32, 27));
    this->addChild(jade_icon);
    
    m_numLab = Label::createWithBMFont(ResourceManager::getInstance()->getFntRes("Score"), "0");
    m_numLab->setAnchorPoint(Vec2(0, 0.5));
    m_numLab->setPosition(Vec2(62, 20));
    m_numLab->setAlignment(TextHAlignment::LEFT, TextVAlignment::CENTER);
    this->addChild(m_numLab);
    return true;
}

void JadeView::setString(const std::string& str)
{
    auto _scaleTo = ScaleTo::create(0.1f, 1.2f);
    auto _scaleTo2 = ScaleTo::create(0.1f, 1.0f);
    m_numLab->runAction(Sequence::create(_scaleTo, _scaleTo2, NULL));
    m_numLab->setString(str);
}