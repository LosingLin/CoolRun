//
//  ItemLandBuild.h
//  CoolRun
//
//  Created by ManYou on 14/12/31.
//
//

#ifndef __CoolRun__ItemLandBuild__
#define __CoolRun__ItemLandBuild__

#include "cocos2d.h"
#include "Item.h"

class ItemLandBuild : public Item
{
public:
    ItemLandBuild();
    ~ItemLandBuild();
    
    virtual bool init() override;
    CREATE_FUNC(ItemLandBuild);
    
    virtual void active(Runner* runner) override;
};

#endif /* defined(__CoolRun__ItemLandBuild__) */
