//
//  MYTextInput.cpp
//  CoolRun
//
//  Created by ManYou on 15/1/28.
//
//

#include "MYTextInput.h"

MYTextInput::MYTextInput()
: Node()
, m_editBox(nullptr)
, textInputDone(nullptr)
{
}
MYTextInput::~MYTextInput()
{
}

bool MYTextInput::init(const Size& size)
{
    if (!Node::init())
    {
        return false;
    }
    this->setContentSize(size);
    
    auto inputBg = Scale9Sprite::createWithSpriteFrameName("input_bg.png");
    m_editBox = EditBox::create(size, inputBg);
    m_editBox->setInputMode(EditBox::InputMode::SINGLE_LINE);
    //m_editBox->setInputFlag(EditBox::InputFlag::SENSITIVE);
    m_editBox->setReturnType(EditBox::KeyboardReturnType::DONE);
    m_editBox->setDelegate(this);
    m_editBox->setPosition(Vec2(size.width/2, size.height/2));
    this->addChild(m_editBox);
    
    textInputDone = CC_CALLBACK_1(MYTextInput::editBoxInputDone, this);
    
    return true;
}

void MYTextInput::setText(const char* text)
{
    m_editBox->setText(text);
}
const char* MYTextInput::getText()
{
    return m_editBox->getText();
}

MYTextInput* MYTextInput::create(const Size& size)
{
    auto input = new MYTextInput();
    if (input->init(size))
    {
        input->autorelease();
        return input;
    }
    delete input;
    return nullptr;
}

void MYTextInput::editBoxReturn(EditBox* editBox)
{
    if (textInputDone)
    {
        textInputDone(editBox->getText());
    }
};

void MYTextInput::editBoxInputDone(const string& str)
{
    
}