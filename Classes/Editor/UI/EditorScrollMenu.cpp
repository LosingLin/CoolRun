//
//  EditorScrollMenu.cpp
//  CoolRun
//
//  Created by ManYou on 15/1/28.
//
//

#include "EditorScrollMenu.h"
#include "EditorMenu.h"

EditorScrollMenu::EditorScrollMenu()
: EditorNode()
, m_scrollView(nullptr)
{
    
}
EditorScrollMenu::~EditorScrollMenu()
{
    
}

bool EditorScrollMenu::init()
{
    if (!EditorNode::init())
    {
        return false;
    }
    
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto csize = Size(100, visibleSize.height);
    this->setContentSize(csize);
    
    m_scrollView = ScrollView::create(csize, EditorMenu::create());
    m_scrollView->setDirection(ScrollView::Direction::VERTICAL);
    this->addChild(m_scrollView);

    return true;
}

void EditorScrollMenu::setMenu(EditorMenu* menu)
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto csize = menu->getContentSize();
    csize.height = visibleSize.height;
    this->setContentSize(csize);
    
    
    m_scrollView->setContainer(menu);
    m_scrollView->setContentSize(menu->getContentSize());
    m_scrollView->setViewSize(csize);
    m_scrollView->setDirection(ScrollView::Direction::VERTICAL);
    m_scrollView->setContentOffset(Vec2(0, - menu->getContentSize().height + csize.height));
}

EditorMenu* EditorScrollMenu::getMenu()
{
    auto menu = m_scrollView->getContainer();
    return dynamic_cast<EditorMenu*>(menu);
}