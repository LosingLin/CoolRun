//
//  CommonBackground.h
//  CoolRun
//
//  Created by ManYou on 15/5/19.
//
//

#ifndef __CoolRun__CommonBackground__
#define __CoolRun__CommonBackground__

#include "cocos2d.h"

USING_NS_CC;

class Background;
class CommonBackground : public Layer
{
public:
    CommonBackground();
    ~CommonBackground();
    
    virtual bool init() override;
    CREATE_FUNC(CommonBackground);
    
private:
    Background *m_awayBG;
    Background *m_farBG;
    Background *m_midBG;
};

#endif /* defined(__CoolRun__CommonBackground__) */
