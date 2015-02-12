//
//  BossBullet.h
//  CoolRun
//
//  Created by ManYou on 15/1/19.
//
//

#ifndef __CoolRun__BossBullet__
#define __CoolRun__BossBullet__

#include "cocos2d.h"
#include "Bullet.h"

class BossBullet : public Bullet
{
public:
    BossBullet();
    ~BossBullet();
    
    virtual bool init() override;
    CREATE_FUNC(BossBullet)
private:
    Sprite* m_bullet;
};

#endif /* defined(__CoolRun__BossBullet__) */
