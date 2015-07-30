//
//  Coin.h
//  CoolRun
//
//  Created by ManYou on 14-8-12.
//
//

#ifndef __CoolRun__Coin__
#define __CoolRun__Coin__

#include "Treasure.h"

class Coin : public Treasure
{
public:
    Coin();
    ~Coin();
    virtual bool init();
    CREATE_FUNC(Coin);
    
    virtual void bePicked() override;
    
    static Coin* create(rapidjson::Value& _value);

};

#endif /* defined(__CoolRun__Coin__) */
