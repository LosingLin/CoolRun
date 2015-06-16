//
//  MYLayer.h
//  CoolRun
//
//  Created by ManYou on 15/6/13.
//
//

#ifndef __CoolRun__MYLayer__
#define __CoolRun__MYLayer__

#include "cocos2d.h"

USING_NS_CC;

class MYLayer : public Layer
{
public:
    MYLayer();
    ~MYLayer();
    
    virtual bool init() override;
    CREATE_FUNC(MYLayer);
};

#endif /* defined(__CoolRun__MYLayer__) */
