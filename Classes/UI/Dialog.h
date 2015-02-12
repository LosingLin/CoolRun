//
//  Dialog.h
//  CoolRun
//
//  Created by ManYou on 14-9-9.
//
//

#ifndef __CoolRun__Dialog__
#define __CoolRun__Dialog__

#include "cocos2d.h"

using namespace std;
USING_NS_CC;

class Dialog : public Node
{
public:
    Dialog();
    ~Dialog();
    virtual bool init();
    CREATE_FUNC(Dialog);
    void say(const string& words);
private:
    LabelTTF* m_label;
};

#endif /* defined(__CoolRun__Dialog__) */
