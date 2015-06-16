//
//  BossBulletNet.h
//  CoolRun
//
//  Created by ManYou on 15/3/17.
//
//

#ifndef __CoolRun__BossBulletNetNet__
#define __CoolRun__BossBulletNetNet__

#include "cocos2d.h"
#include "Bullet.h"

class BossBulletNet : public Bullet
{
public:
    BossBulletNet();
    ~BossBulletNet();
    
    virtual bool init() override;
    CREATE_FUNC(BossBulletNet)
    
    virtual void beingDestoryed() override;
    void brokeDone();
private:
    Sprite* m_bullet;
};

#endif /* defined(__CoolRun__BossBulletNetNet__) */
