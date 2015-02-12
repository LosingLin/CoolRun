//
//  ItemTimesJump.h
//  CoolRun
//
//  Created by ManYou on 14/12/24.
//
//

#ifndef __CoolRun__ItemTimesJump__
#define __CoolRun__ItemTimesJump__

#include "cocos2d.h"
#include "Item.h"

class ItemTimesJump : public Item
{
public:
    ItemTimesJump();
    ~ItemTimesJump();
    
    virtual bool init() override;
    CREATE_FUNC(ItemTimesJump);
    
    virtual void active(Runner* runner) override;
};

#endif /* defined(__CoolRun__ItemTimesJump__) */
