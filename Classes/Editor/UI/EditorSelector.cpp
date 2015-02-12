//
//  EditorSelector.cpp
//  CoolRun
//
//  Created by ManYou on 15/2/2.
//
//

#include "EditorSelector.h"
#include "EditorUIBase.h"


EditorSelector::EditorSelector()
: EditorNode()
, m_arr(nullptr)
, m_selector(nullptr)
, m_items(nullptr)
, selectedKey(nullptr)
, active(nullptr)
{
    
}
EditorSelector::~EditorSelector()
{
    CC_SAFE_RELEASE_NULL(m_arr);
}

bool EditorSelector::init()
{
    if (!EditorNode::init())
    {
        return false;
    }
    
    return true;
}

bool EditorSelector::init(__Array* arr, const string& title, const Size& csize)
{
    if (!this->init())
    {
        return false;
    }
    m_arr = arr;
    CC_SAFE_RETAIN(m_arr);
    
    this->setContentSize(csize);
    
    auto text = EditorText::create(title, Size(160, csize.height), 30);
    text->setPosition(Vec2(0, 0));
    text->touchNoneMoveEnded = CC_CALLBACK_0(EditorSelector::touchSelector, this);
    //text->getTouchListener()->setSwallowTouches(false);
    this->addChild(text);
    
    auto key = dynamic_cast<__String*>(m_arr->getObjectAtIndex(0));
    m_selector = EditorText::create(key->getCString(), Size(csize.width - 160, csize.height), 30);
    m_selector->setPosition(Vec2(160, 0));
    m_selector->touchNoneMoveEnded = CC_CALLBACK_0(EditorSelector::touchSelector, this);
    this->addChild(m_selector);
    
    m_items = Node::create();
    m_items->setPosition(Vec2(160, 0));
    this->addChild(m_items);
    
    int inc_y = csize.height + 10;
    int y = -inc_y;
    for (int i = 0; i < m_arr->count(); ++ i)
    {
        auto key = dynamic_cast<__String*>(m_arr->getObjectAtIndex(i));
        auto text = EditorText::create(key->getCString(), Size(csize.width-160, csize.height), 30);
        text->setPosition(Vec2(0, y));
        //text->setColor(Color3B::GRAY);
        text->touchNoneMoveEnded = CC_CALLBACK_0(EditorSelector::selected, this, key->getCString());
        m_items->addChild(text);
        y -= inc_y;
    }
    
    m_items->setVisible(false);
    
    return true;
}

void EditorSelector::touchSelector()
{
    if (m_items->isVisible())
    {
        m_items->setVisible(false);
        
//        if (selectedKey)
//        {
//            selectedKey(m_selector->getText());
//        }
    }
    else
    {
        m_items->setVisible(true);
        if (active)
        {
            active(this);
        }
    }
    
}

void EditorSelector::selected(const string& key)
{
    m_items->setVisible(false);
    m_selector->setText(key);
    
    if (selectedKey)
    {
        selectedKey(key);
    }
}

void EditorSelector::setSelected(const string& key)
{
    m_selector->setText(key);
}

EditorSelector* EditorSelector::create(__Array* arr, const string& title, const Size& csize)
{
    auto es = new EditorSelector();
    if (es && es->init(arr, title, csize))
    {
        es->autorelease();
        return es;
    }
    delete es;
    return nullptr;
}


#pragma mark -

EditorSelectorValue::EditorSelectorValue()
: Ref()
{
    
}
EditorSelectorValue::~EditorSelectorValue()
{
    
}

bool EditorSelectorValue::init()
{
    
    return true;
}

EditorSelectorValue* EditorSelectorValue::create(int v)
{
    auto esv = new EditorSelectorValue();
    if (esv && esv->init())
    {
        esv->setValue(v);
        esv->autorelease();
        return esv;
    }
    delete esv;
    return nullptr;
}