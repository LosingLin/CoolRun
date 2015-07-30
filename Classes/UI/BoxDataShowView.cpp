//
//  BoxDataShowView.cpp
//  CoolRun
//
//  Created by ManYou on 15/7/2.
//
//

#include "BoxDataShowView.h"
#include "BoxData.h"
#include "ResourceManager.h"

BoxDataShowView::BoxDataShowView()
: Node()
{
    
}
BoxDataShowView::~BoxDataShowView()
{
    
}

bool BoxDataShowView::init()
{
    if (!Node::init())
    {
        return false;
    }
    
    return true;
}

bool BoxDataShowView::init(BoxData* _data)
{
    if (!this->init())
    {
        return false;
    }
    auto csize = Size(0, 0);
    int jadeNum = _data->getJadeNum();
    if (jadeNum > 0)
    {
        char ch[20] = {'\0'};
        sprintf(ch, "+%d ", jadeNum);
        auto _label = Label::createWithBMFont(ResourceManager::getInstance()->getFntRes("Score"), ch);
        auto _lSize = _label->getContentSize();
        _label->setAnchorPoint(Vec2(0, 0));
        _label->setPosition(Vec2(0, 0));
        this->addChild(_label);
        csize.width += _lSize.width;
        csize.height = _lSize.height > csize.height ? _lSize.height : csize.height;
        
        auto icon = Sprite::createWithSpriteFrameName("jade.png");
        icon->setAnchorPoint(Vec2(0, 0));
        icon->setScale(0.6);
        icon->setPosition(Vec2(_lSize.width, 0));
        this->addChild(icon);
        auto icSize = icon->getContentSize();
        csize.width += icSize.width;
        csize.height = icSize.height > csize.height ? icSize.height : csize.height;
    }
    
    this->setContentSize(csize);
    
    return true;
}

BoxDataShowView* BoxDataShowView::create(BoxData* _data)
{
    auto _view = new BoxDataShowView();
    if (_view && _view->init(_data))
    {
        _view->autorelease();
        return _view;
    }
    delete _view;
    _view = nullptr;
    return nullptr;
}