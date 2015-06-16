//
//  NormalFrame.h
//  CoolRun
//
//  Created by ManYou on 15/5/16.
//
//

#ifndef __CoolRun__NormalFrame__
#define __CoolRun__NormalFrame__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "MYButton.h"

USING_NS_CC;
USING_NS_CC_EXT;


class NormalFrame : public Node
{
public:
    NormalFrame();
    ~NormalFrame();
    
    bool init(const Size& _size, const char* title, bool hasClose = true);
    static NormalFrame* create(const  Size& _size, const char* title, bool hasClose = true);
    
    void addCloseCallback(MYButton::MYButtonCallback callback);
    void updateBMFTitleLabel(const string& _bmf, const string& title);
private:
    MYButton* m_closeBtn;
    Label* m_titleLab;
};

#endif /* defined(__CoolRun__NormalFrame__) */
