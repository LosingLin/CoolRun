//
//  Saw.h
//  CoolRun
//
//  Created by ManYou on 15/2/27.
//
//

#ifndef __CoolRun__Saw__
#define __CoolRun__Saw__

#include "MultipleCollideNode.h"

class Saw : public MultipleCollideNode
{
public:
    Saw();
    ~Saw();
    
    virtual bool init() override;
    CREATE_FUNC(Saw);
    
    virtual void trackCollideWithRunner(Runner* _runner) override;
};

#endif /* defined(__CoolRun__Saw__) */
