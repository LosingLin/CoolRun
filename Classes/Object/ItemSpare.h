//
//  ItemSpare.h
//  CoolRun
//
//  Created by ManYou on 14/12/23.
//
//

#ifndef __CoolRun__ItemSpare__
#define __CoolRun__ItemSpare__

#include "cocos2d.h"
#include "Item.h"

class ItemSpare : public Item
{
public:
    ItemSpare();
    ~ItemSpare();
    
    virtual bool init() override;
    CREATE_FUNC(ItemSpare);
    
    virtual void active(Runner* runner) override;
};

#endif /* defined(__CoolRun__ItemSpare__) */
