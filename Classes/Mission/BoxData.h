//
//  BoxData.h
//  CoolRun
//
//  Created by ManYou on 15/7/1.
//
//

#ifndef __CoolRun__BoxData__
#define __CoolRun__BoxData__

#include "cocos2d.h"

USING_NS_CC;

class BoxData : public Ref
{
public:
    BoxData();
    ~BoxData();
    
    virtual bool init();
    CREATE_FUNC(BoxData);
    
    int getJadeNum() { return m_jadeNum; }
    void setJadeNum(int num) { m_jadeNum = num; }
private:
    int m_jadeNum;
};

#endif /* defined(__CoolRun__BoxData__) */
