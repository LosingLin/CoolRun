//
//  PoisonBullet.h
//  CoolRun
//
//  Created by ManYou on 14/12/5.
//
//

#ifndef __CoolRun__PoisonBullet__
#define __CoolRun__PoisonBullet__

#include "cocos2d.h"
#include "Bullet.h"

class PoisonBullet : public Bullet
{
public:
    PoisonBullet();
    ~PoisonBullet();
    
    virtual bool init() override;
    CREATE_FUNC(PoisonBullet)
    
    void setAtkDirection(CRDirection direction);
private:
    Sprite* m_bullet;
    CRDirection m_atkDirection;
};

#endif /* defined(__CoolRun__PoisonBullet__) */
