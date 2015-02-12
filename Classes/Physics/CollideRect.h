//
//  CollideRect.h
//  CoolRun
//
//  Created by ManYou on 14/10/27.
//
//

#ifndef __CoolRun__CollideRect__
#define __CoolRun__CollideRect__

#include "cocos2d.h"

USING_NS_CC;

class CollideRect : public Ref
{
public:
    CollideRect();
    ~CollideRect();
    virtual bool init();
    CREATE_FUNC(CollideRect);
    
    static CollideRect* create(const Rect& _rect, int _id);
    
    void setRect(const Rect& _rect)
    {
        m_rect.size.width = _rect.size.width;
        m_rect.size.height = _rect.size.height;
        m_rect.origin.x = _rect.origin.x;
        m_rect.origin.y = _rect.origin.y;
    };
    const Rect& getRect() { return m_rect; };
    
    void setId(int _id) { m_id = _id; };
    int getId() { return m_id; };
    
private:
    Rect m_rect;
    int m_id;
};

#endif /* defined(__CoolRun__CollideRect__) */
