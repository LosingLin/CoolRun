//
//  EditorNode.cpp
//  CoolRun
//
//  Created by ManYou on 15/1/28.
//
//

#include "EditorNode.h"

EditorNode::EditorNode()
: Node()
, m_listener(nullptr)
, m_touchListener(nullptr)
, b_isTouchEnable(false)
, m_beganTouchLoc(Vec2(0, 0))
, m_lastTouchLoc(Vec2(0, 0))
, b_isTouchMoved(false)
, touchBegan(nullptr)
, touchMoved(nullptr)
, touchMoveEnded(nullptr)
, touchNoneMoveEnded(nullptr)
{
    
}
EditorNode::~EditorNode()
{
    CC_SAFE_RELEASE_NULL(m_touchListener);
}

bool EditorNode::init()
{
    if (!Node::init())
    {
        return false;
    }
    
    this->setTouchEnable(true);
    
    touchBegan = CC_CALLBACK_0(EditorNode::editorNodeTouchBegan, this);
    touchMoved = CC_CALLBACK_2(EditorNode::editorNodeTouchMoved, this);
    touchNoneMoveEnded = CC_CALLBACK_0(EditorNode::editorNodeNoneMoveEnded, this);
    touchMoveEnded = CC_CALLBACK_0(EditorNode::editorNodeMoveEnded, this);
    
    //test
//    auto layer = LayerColor::create(Color4B(200, 20, 200, 150), 100, 100);
//    this->addChild(layer);
//    this->setContentSize(Size(100, 100));

    return true;
}

void EditorNode::setTouchEnable(bool flag)
{
    if (b_isTouchEnable == flag)
    {
        return;
    }
    b_isTouchEnable = flag;
    
    if (b_isTouchEnable)
    {
        if (!m_touchListener)
        {
            m_touchListener = EventListenerTouchOneByOne::create();
            CC_SAFE_RETAIN(m_touchListener);
            m_touchListener->setSwallowTouches(true);
            m_touchListener->onTouchBegan = CC_CALLBACK_2(EditorNode::onTouchBegan, this);
            m_touchListener->onTouchMoved = CC_CALLBACK_2(EditorNode::onTouchMoved, this);
            m_touchListener->onTouchEnded = CC_CALLBACK_2(EditorNode::onTouchEnded, this);
            m_touchListener->onTouchCancelled = CC_CALLBACK_2(EditorNode::onTouchCancelled, this);
            _eventDispatcher->addEventListenerWithSceneGraphPriority(m_touchListener, this);
        }
    }
    else
    {
        if (m_touchListener)
        {
            _eventDispatcher->removeEventListener(m_touchListener);
            CC_SAFE_RELEASE_NULL(m_touchListener);
        }
    }
}

#pragma mark - 
void EditorNode::editorNodeTouchBegan()
{
    
}
void EditorNode::editorNodeTouchMoved(int x, int y)
{
//    auto pos = this->getPosition();
//    pos.x += x;
//    pos.y += y;
//    this->setPosition(pos);
}
void EditorNode::editorNodeNoneMoveEnded()
{
    
}
void EditorNode::editorNodeMoveEnded()
{
    
}

#pragma mark - help
bool EditorNode::isTouchInside(Touch* touch)
{
    Vec2 touchLocation = touch->getLocation();
    touchLocation = this->getParent()->convertToNodeSpace(touchLocation);
    Rect bBox = getBoundingBox();
    return bBox.containsPoint(touchLocation);
}

bool EditorNode::hasVisibleParents() const
{
    auto parent = this->getParent();
    for( auto c = parent; c != nullptr; c = c->getParent() )
    {
        if( !c->isVisible() )
        {
            return false;
        }
    }
    return true;
}

#pragma mark - touch

bool EditorNode::onTouchBegan(Touch *touch, Event *unusedEvent)
{
    if (!isTouchInside(touch) || !this->isVisible() || !this->hasVisibleParents())
    {
        return false;
    }
    m_beganTouchLoc = touch->getLocation();
    m_lastTouchLoc = m_beganTouchLoc;
    if (touchBegan)
    {
        touchBegan();
    }
    b_isTouchMoved = false;
    return true;
}
void EditorNode::onTouchMoved(Touch *touch, Event *unusedEvent)
{
    b_isTouchMoved = true;
    
    if (touchMoved)
    {
        auto moveTouchLoc = touch->getLocation();
        int x = moveTouchLoc.x - m_lastTouchLoc.x;
        int y = moveTouchLoc.y - m_lastTouchLoc.y;
        touchMoved(x, y);
    }
    
    m_lastTouchLoc = touch->getLocation();
}
void EditorNode::onTouchEnded(Touch *touch, Event *unusedEvent)
{
    if (isTouchInside(touch))
    {
        if (b_isTouchMoved)
        {
            if (touchMoveEnded)
            {
                touchMoveEnded();
            }
        }
        else
        {
            if (touchNoneMoveEnded)
            {
                touchNoneMoveEnded();
            }
        }
    }
    b_isTouchMoved = false;
}
void EditorNode::onTouchCancelled(Touch *touch, Event *unusedEvent)
{
    
}