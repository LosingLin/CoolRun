//
//  Jade.h
//  CoolRun
//
//  Created by ManYou on 15/7/1.
//
//

#ifndef __CoolRun__Jade__
#define __CoolRun__Jade__

#include "Treasure.h"

class Jade : public Treasure
{
public:
    Jade();
    ~Jade();
    virtual bool init() override;
    CREATE_FUNC(Jade);
    
    
    virtual void times() override;
    
    virtual void bePicked() override;
    
    void setJadeNum(int num) { m_jadeNum = num; }
    int getJadeNum() { return m_jadeNum; }
private:
    int m_jadeNum;
};

#endif /* defined(__CoolRun__Jade__) */
