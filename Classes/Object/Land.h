//
//  Land.h
//  CoolRun
//
//  Created by ManYou on 14/12/29.
//
//

#ifndef __CoolRun__Land__
#define __CoolRun__Land__

#include "cocos2d.h"
#include "PhysicNode.h"

class Land : public PhysicNode
{
public:
    Land();
    ~Land();
    virtual bool init() override;
    CREATE_FUNC(Land);
    
    virtual void onEnter() override;
    virtual void onExit() override;
    
    virtual void setLand(bool flag) { m_isLand = flag; }
    bool isLand() { return m_isLand; }
    
    virtual void setLeftIgnore(bool flag) { m_isLeftIgnore = flag; }
    bool isLeftIgnore() { return m_isLeftIgnore; }
    virtual void setRightIgnore(bool flag) { m_isRightIgnore = flag; }
    bool isRightIgnore() { return m_isRightIgnore; }
    void setUpIgnore(bool flag) { m_isUpIgnore = flag; }
    bool isUpIgnore() { return m_isUpIgnore; }
    void setDownIgnore(bool flag) { m_isDownIgnore = flag; }
    bool isDownIgnore() { return m_isDownIgnore; }
    
    void showTips(int index);
private:
    bool m_isLand;
    bool m_isLeftIgnore;
    bool m_isRightIgnore;
    bool m_isUpIgnore;
    bool m_isDownIgnore;
};

#endif /* defined(__CoolRun__Land__) */
