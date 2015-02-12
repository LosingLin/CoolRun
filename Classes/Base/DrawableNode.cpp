//
//  DrawableNode.cpp
//  CoolRun
//
//  Created by ManYou on 14-8-8.
//
//

#include "DrawableNode.h"


DrawableNode::DrawableNode()
: Node()
, m_draw(NULL)
{
}
DrawableNode::~DrawableNode()
{
}

bool DrawableNode::init()
{
    if (!Node::init()) {
        return false;
    }
    
    m_draw = DrawNode::create();
    this->addChild(m_draw, 600);
    
    return true;
}

void DrawableNode::showOriginDot()
{
    this->drawDot(Vec2(0, 0), 10, Color4F(1, 0, 0, 1));
}
void DrawableNode::showContentSizeRect()
{
    auto csize = this->getContentSize();
    Vec2 v[] = {Vec2(0, 0), Vec2(0, csize.height), Vec2(csize.width, csize.height), Vec2(csize.width, 0)};
    
    this->drawPolygon(v, 4, Color4F(0, 1, 0, 0.1), 2, Color4F(0, 1, 0, 0.8));
}
void DrawableNode::showRect(const Rect &_rect)
{
    
    Vec2 v[] = {Vec2(_rect.origin.x, _rect.origin.y),
                Vec2(_rect.origin.x, _rect.origin.y + _rect.size.height),
                Vec2(_rect.origin.x + _rect.size.width, _rect.origin.y + _rect.size.height),
                Vec2(_rect.origin.x + _rect.size.width, _rect.origin.y)};
    
    this->drawPolygon(v, 4, Color4F(1, 1, 0, 0.1), 2, Color4F(1, 1, 0, 1));
}

/** draw a dot at a position, with a given radius and color */
void DrawableNode::drawDot(const Vec2 &pos, float radius, const Color4F &color)
{
    m_draw->drawDot(pos, radius, color);
}

/** draw a segment with a radius and color */
void DrawableNode::drawLine(const Vec2 &from, const Vec2 &to, float radius, const Color4F &color)
{
    m_draw->drawSegment(from, to, radius, color);
}

void DrawableNode::drawPolygon(Vec2 *verts, int count, const Color4F &fillColor, float borderWidth, const Color4F &borderColor)
{
    m_draw->drawPolygon(verts, count, fillColor, borderWidth, borderColor);
}

/** draw a triangle with color */
void DrawableNode::drawTriangle(const Vec2 &p1, const Vec2 &p2, const Vec2 &p3, const Color4F &color)
{
    m_draw->drawTriangle(p1, p2, p3, color);
}