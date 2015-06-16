//
//  ADLoadingLayer.h
//  CoolRun
//
//  Created by ManYou on 15/6/14.
//
//

#ifndef __CoolRun__ADLoadingLayer__
#define __CoolRun__ADLoadingLayer__

#include "PopViewLayer.h"

class ADLoadingLayer : public PopViewLayer
{
public:
    ADLoadingLayer();
    ~ADLoadingLayer();
    
    virtual bool init() override;
    CREATE_FUNC(ADLoadingLayer);
};

#endif /* defined(__CoolRun__ADLoadingLayer__) */
