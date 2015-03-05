//
//  AlertBulletPoison.h
//  CoolRun
//
//  Created by ManYou on 15/3/2.
//
//

#ifndef __CoolRun__AlertBulletPoison__
#define __CoolRun__AlertBulletPoison__

#include "AlertBullet.h"

class AlertBulletPoison : public AlertBullet
{
public:
    AlertBulletPoison();
    ~AlertBulletPoison();
    
    virtual bool init() override;
    CREATE_FUNC(AlertBulletPoison);
};

#endif /* defined(__CoolRun__AlertBulletPoison__) */
