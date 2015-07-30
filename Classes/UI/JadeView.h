//
//  Jade.h
//  CoolRun
//
//  Created by ManYou on 15/6/24.
//
//

#ifndef __CoolRun__Jade__
#define __CoolRun__Jade__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

class JadeView : public Node
{
public:
    JadeView();
    ~JadeView();
    
    virtual bool init() override;
    CREATE_FUNC(JadeView);
    
    void setString(const std::string& str);
    
    void addAction(int num);
private:
    Label* m_numLab;
};

#endif /* defined(__CoolRun__Jade__) */
