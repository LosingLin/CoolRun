//
//  ItemTimesCoin.h
//  CoolRun
//
//  Created by ManYou on 14/12/24.
//
//

#ifndef __CoolRun__ItemTimesCoin__
#define __CoolRun__ItemTimesCoin__

#include "cocos2d.h"
#include "Item.h"

class ItemTimesCoin : public Item
{
public:
    ItemTimesCoin();
    ~ItemTimesCoin();
    
    virtual bool init() override;
    CREATE_FUNC(ItemTimesCoin);
    
    virtual void active(Runner* runner) override;
};

#endif /* defined(__CoolRun__ItemTimesCoin__) */
