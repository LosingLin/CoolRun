//
//  DrawableNode.h
//  CoolRun
//
//  Created by ManYou on 14-8-8.
//
//

#ifndef __CoolRun__DrawableNode__
#define __CoolRun__DrawableNode__

#include "cocos2d.h"

USING_NS_CC;

class DrawableNode : public Node
{
public:
    DrawableNode();
    ~DrawableNode();
    virtual bool init();
    CREATE_FUNC(DrawableNode);
    
    /** draw a dot at a position, with a given radius and color */
    void drawDot(const Vec2 &pos, float radius, const Color4F &color);
    
    /** draw a segment with a radius and color */
    void drawLine(const Vec2 &from, const Vec2 &to, float radius, const Color4F &color);
    
    void drawPolygon(Vec2 *verts, int count, const Color4F &fillColor, float borderWidth, const Color4F &borderColor);
	
    /** draw a triangle with color */
    void drawTriangle(const Vec2 &p1, const Vec2 &p2, const Vec2 &p3, const Color4F &color);
    
    void showOriginDot();
    void showPositionDot();
    void showContentSizeRect();
    void showRect(const Rect &rect);
    
private:
    DrawNode *m_draw;
};


#endif /* defined(__CoolRun__DrawableNode__) */
