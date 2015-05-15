//
//  BackgroundAudio.h
//  CoolRun
//
//  Created by ManYou on 15/5/5.
//
//

#ifndef __CoolRun__BackgroundAudio__
#define __CoolRun__BackgroundAudio__

#include "cocos2d.h"

USING_NS_CC;

class BackgroundAudio : public Layer
{
public:
    enum class BGAType
    {
        NULLTYPE,
        DAY,
        NIGHT,
        BOSS,
    };
public:
    BackgroundAudio();
    ~BackgroundAudio();
    
    virtual bool init();
    CREATE_FUNC(BackgroundAudio);
    
    virtual void onEnter();
    virtual void onExit();
    
    void setBGAType(BGAType _type);
private:
    BGAType m_type;
};


#endif /* defined(__CoolRun__BackgroundAudio__) */
