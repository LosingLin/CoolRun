//
//  ItemDad.h
//  CoolRun
//
//  Created by ManYou on 14/12/25.
//
//

#ifndef __CoolRun__ItemDad__
#define __CoolRun__ItemDad__

#include "cocos2d.h"
#include "Item.h"

class ItemDad : public Item
{
public:
    ItemDad();
    ~ItemDad();
    
    virtual bool init() override;
    CREATE_FUNC(ItemDad);
    
    virtual void active(Runner* runner) override;
};

#endif /* defined(__CoolRun__ItemDad__) */
