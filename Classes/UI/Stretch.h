//
//  Stretch.h
//  CoolRun
//
//  Created by ManYou on 15/2/11.
//
//

#ifndef __CoolRun__Stretch__
#define __CoolRun__Stretch__

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

class Stretch : public Node
{
public:
    Stretch();
    ~Stretch();
    
    virtual bool init() override;
    CREATE_FUNC(Stretch);
    
    void setString(const std::string& str);
private:
    Label* m_numLab;
};

#endif /* defined(__CoolRun__Stretch__) */
