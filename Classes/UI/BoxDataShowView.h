//
//  BoxDataShowView.h
//  CoolRun
//
//  Created by ManYou on 15/7/2.
//
//

#ifndef __CoolRun__BoxDataShowView__
#define __CoolRun__BoxDataShowView__

#include "cocos2d.h"

USING_NS_CC;

class BoxData;
class BoxDataShowView : public Node
{
public:
    BoxDataShowView();
    ~BoxDataShowView();
    
    virtual bool init() override;
    bool init(BoxData* _data);
    static BoxDataShowView* create(BoxData* _data);
};

#endif /* defined(__CoolRun__BoxDataShowView__) */
