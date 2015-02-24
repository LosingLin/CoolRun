//
//  EditorNode.h
//  CoolRun
//
//  Created by ManYou on 15/1/28.
//
//

#ifndef __CoolRun__EditorNode__
#define __CoolRun__EditorNode__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "EditorListener.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;

class EditorNode : public Node
{
public:
    EditorNode();
    ~EditorNode();
    
    virtual bool init() override;
    CREATE_FUNC(EditorNode);
    
    void setEditorListener(EditorListener* listener) { m_listener = listener; }
    EditorListener* getEditorListener() { return m_listener; }
    
    EventListenerTouchOneByOne* getTouchListener() { return m_touchListener; }
    
    void setTouchEnable(bool flag);
    bool isTouchEnable() { return b_isTouchEnable; };
    
    virtual bool onTouchBegan(Touch *touch, Event *unusedEvent);
    virtual void onTouchMoved(Touch *touch, Event *unusedEvent);
    virtual void onTouchEnded(Touch *touch, Event *unusedEvent);
    virtual void onTouchCancelled(Touch *touch, Event *unusedEvent);
    
    
    virtual void editorNodeTouchBegan();
    virtual void editorNodeTouchMoved(int x, int y);
    virtual void editorNodeNoneMoveEnded();
    virtual void editorNodeMoveEnded();
    
protected:
    bool isTouchInside(Touch* touch);
    bool hasVisibleParents() const;
public:
    std::function<void()> touchBegan;
    std::function<void(int x_inc, int y_inc)> touchMoved;
    std::function<void()> touchNoneMoveEnded;
    std::function<void()> touchMoveEnded;
private:
    EditorListener* m_listener;
    EventListenerTouchOneByOne* m_touchListener;
    bool b_isTouchEnable;
    
    Vec2 m_beganTouchLoc;
    Vec2 m_lastTouchLoc;
    bool b_isTouchMoved;
};

#endif /* defined(__CoolRun__EditorNode__) */
