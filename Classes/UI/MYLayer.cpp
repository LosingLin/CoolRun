//
//  MYLayer.cpp
//  CoolRun
//
//  Created by ManYou on 15/6/13.
//
//

#include "MYLayer.h"


MYLayer::MYLayer()
: Layer()
{
    
}
MYLayer::~MYLayer()
{
    
}

bool MYLayer::init()
{
    if (!Layer::init())
    {
        return false;
    }
    
    return true;
}