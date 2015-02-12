//
//  Villager.cpp
//  CoolRun
//
//  Created by ManYou on 14-9-5.
//
//

#include "Villager.h"
#include "Base.h"
#include "Dialog.h"

#define kDialogActionTag 1000
#define kDialogTag  1001


Villager::Villager()
: Node()
, m_touchBtn(nullptr)
, m_villagerSp(nullptr)
, m_words(nullptr)
{
}
Villager::~Villager()
{
    if (m_words)
    {
        delete m_words;
    }
}
bool Villager::init()
{
    if (!Node::init())
    {
        return false;
    }
    
    return true;
}

void Villager::init(const string& _frameName, const string& _words)
{
    m_villagerSp = Sprite::createWithSpriteFrameName(_frameName);
    auto _size = m_villagerSp->getContentSize();
    this->setContentSize(_size);
    m_villagerSp->setPosition(Vec2(_size.width/2, _size.height/2));
    this->addChild(m_villagerSp);
    
    m_touchBtn = MYButton::createWithContentSize(_size);
    this->addChild(m_touchBtn);
    
    m_words = new string;
    *m_words = _words;
    
    log("words: %s", m_words->c_str());
}

Villager* Villager::createWithFrameName(const string& _frameName, const string& _words)
{
    auto _villager = Villager::create();
    _villager->init(_frameName, _words);
    return _villager;
}

void Villager::addTouchCallback(MYButton::MYButtonCallback _callback)
{
    CCASSERT(m_touchBtn, "button is not exist");
    m_touchBtn->addTouchEventListener(_callback);
}

void Villager::talk()
{
    auto _dialog = dynamic_cast<Dialog*>(this->getChildByTag(kDialogTag));
    if (!_dialog)
    {
        _dialog = Dialog::create();
        auto csize = this->getContentSize();
        _dialog->setPosition(Vec2(csize.width/2, csize.height));
        this->addChild(_dialog, 5, kDialogTag);
        _dialog->say(m_words->c_str());
    }
    
    SAFESETVISIBLE(_dialog, true);
    _dialog->setScale(0.2);
    
    auto _action = _dialog->getActionByTag(kDialogActionTag);
    if (_action)
    {
        _dialog->stopActionByTag(kDialogActionTag);
    }
    
    auto _scale = ScaleTo::create(0.2, 1);
    auto _delay = DelayTime::create(3);
    auto _scaleBack = ScaleTo::create(0.2, 0.2);
    auto _call = CallFunc::create(CC_CALLBACK_0(Villager::talkOver, this, _dialog));
    auto _seq = Sequence::create(_scale, _delay, _scaleBack, _call, NULL);
    _seq->setTag(kDialogActionTag);
    _dialog->runAction(_seq);
}

void Villager::talkOver(Dialog* _dlg)
{
    SAFESETVISIBLE(_dlg, false);
}