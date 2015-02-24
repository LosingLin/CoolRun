//
//  Score.h
//  CoolRun
//
//  Created by ManYou on 15/2/11.
//
//

#ifndef __CoolRun__Score__
#define __CoolRun__Score__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

class Score : public Node
{
public:
    Score();
    ~Score();
    
    virtual bool init() override;
    CREATE_FUNC(Score);
    
    void setString(const std::string& str);
private:
    Label* m_numLab;
};

#endif /* defined(__CoolRun__Score__) */
