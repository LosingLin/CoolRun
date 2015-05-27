//
//  PowerIconBar.h
//  CoolRun
//
//  Created by ManYou on 15/5/25.
//
//

#ifndef __CoolRun__PowerIconBar__
#define __CoolRun__PowerIconBar__

#include "cocos2d.h"
#include "PowerIcon.h"

USING_NS_CC;

class PowerIconBar : public Node
{
public:
    PowerIconBar();
    ~PowerIconBar();
    
    virtual bool init() override;
    CREATE_FUNC(PowerIconBar);
    
    void addPowerIcon(PowerIcon::PowerType _type);
    void removePowerIcon(PowerIcon::PowerType _type);
    void updatePowerIcon(PowerIcon::PowerType _type, float _persentage);
    void removeAllPowerIcon();
private:
    void layoutIcons();
    PowerIcon* getPowerIcon(PowerIcon::PowerType _type);
private:
    __Array* m_icons;
};

#endif /* defined(__CoolRun__PowerIconBar__) */
