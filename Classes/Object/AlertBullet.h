//
//  AlertBullet.h
//  CoolRun
//
//  Created by ManYou on 14/12/16.
//
//

#ifndef __CoolRun__AlertBullet__
#define __CoolRun__AlertBullet__

#include "cocos2d.h"
#include "Bullet.h"

class AlertBullet : public Bullet
{
public:
    AlertBullet();
    ~AlertBullet();
    
    virtual bool init() override;
    CREATE_FUNC(AlertBullet)
    
    virtual void onEnter() override;
    virtual void onExit() override;
    virtual void update(float delta) override;
    
    void alertDone();
    
protected:
    Sprite* m_bullet;
    Sprite* m_line;
    Sprite* m_alert;
    bool b_isAlterted;
};

#endif /* defined(__CoolRun__AlertBullet__) */
