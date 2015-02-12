//
//  CollectionCoin.cpp
//  CoolRun
//
//  Created by ManYou on 14-10-7.
//
//

#include "CollectionCoin.h"
#include "Base.h"


CollectionCoin::CollectionCoin()
: Collection()
{
}
CollectionCoin::~CollectionCoin()
{
}

bool CollectionCoin::init()
{
    if (!Collection::init())
    {
        return false;
    }
     
    return true;
}