//
//  ItemFly.h
//  CoolRun
//
//  Created by ManYou on 15/1/1.
//
//

#ifndef __CoolRun__ItemFly__
#define __CoolRun__ItemFly__

#include "cocos2d.h"
#include "Item.h"

class ItemFly : public Item
{
public:
    ItemFly();
    ~ItemFly();
    
    virtual bool init() override;
    CREATE_FUNC(ItemFly);
    
    virtual void active(Runner* runner) override;
};


#endif /* defined(__CoolRun__ItemFly__) */
