//
//  CollectionCoin.h
//  CoolRun
//
//  Created by ManYou on 14-10-7.
//
//

#ifndef __CoolRun__CollectionCoin__
#define __CoolRun__CollectionCoin__

#include "cocos2d.h"
#include "Collection.h"

USING_NS_CC;

class CollectionCoin : public Collection
{
public:
    CollectionCoin();
    ~CollectionCoin();
    virtual bool init();
    CREATE_FUNC(CollectionCoin);
private:
};

#endif /* defined(__CoolRun__CollectionCoin__) */
