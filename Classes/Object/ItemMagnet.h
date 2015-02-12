//
//  ItemMagnet.h
//  CoolRun
//
//  Created by ManYou on 14/12/23.
//
//

#ifndef __CoolRun__ItemMagnet__
#define __CoolRun__ItemMagnet__

#include "cocos2d.h"
#include "Item.h"

class ItemMagnet : public Item
{
public:
    ItemMagnet();
    ~ItemMagnet();
    
    virtual bool init() override;
    CREATE_FUNC(ItemMagnet);
    
    virtual void active(Runner* runner) override;
};

#endif /* defined(__CoolRun__ItemMagnet__) */
