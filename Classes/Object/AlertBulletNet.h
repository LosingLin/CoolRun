//
//  AlertBulletNet.h
//  CoolRun
//
//  Created by ManYou on 15/3/2.
//
//

#ifndef __CoolRun__AlertBulletNet__
#define __CoolRun__AlertBulletNet__

#include "AlertBullet.h"

class AlertBulletNet : public AlertBullet
{
public:
    AlertBulletNet();
    ~AlertBulletNet();
    
    virtual bool init() override;
    CREATE_FUNC(AlertBulletNet);
};

#endif /* defined(__CoolRun__AlertBulletNet__) */
