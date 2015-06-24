//
//  Box.h
//  CoolRun
//
//  Created by ManYou on 15/6/24.
//
//

#ifndef __CoolRun__Box__
#define __CoolRun__Box__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

class Box : public Node
{
public:
    Box();
    ~Box();
    
    virtual bool init() override;
    CREATE_FUNC(Box);
    
    void setString(const std::string& str);
    
    void addAction(int num);
private:
    Label* m_numLab;
};

#endif /* defined(__CoolRun__Box__) */
