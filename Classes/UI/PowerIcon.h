//
//  PowerIcon.h
//  CoolRun
//
//  Created by ManYou on 15/5/22.
//
//

#ifndef __CoolRun__PowerIcon__
#define __CoolRun__PowerIcon__

#include "cocos2d.h"


USING_NS_CC;

class PowerIcon : public Node
{
public:
    enum class PowerType
    {
        SPARE,
        MAGNET,
        TIMESCOIN,
        TIMESJUMP,
        DAD,
        LANDBUILD,
        FLY,
        REBORN
    };
public:
    PowerIcon();
    ~PowerIcon();
    
    virtual bool init() override;
    bool init(PowerType _type);
    static PowerIcon* create(PowerType _type);
    
    void setPercentage(float _per);
    
    PowerType getPowerType() { return m_powerType; }
private:
    void setPowerType(PowerType _type) { m_powerType = _type; }
private: 
    Sprite* m_icon;
    ProgressTimer* m_proBg;
    PowerType m_powerType;
};

#endif /* defined(__CoolRun__PowerIcon__) */
