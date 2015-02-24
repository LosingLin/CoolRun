//
//  MYTextInput.h
//  CoolRun
//
//  Created by ManYou on 15/1/28.
//
//

#ifndef __CoolRun__MYTextInput__
#define __CoolRun__MYTextInput__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

using namespace std;

class MYTextInput : public Node, public EditBoxDelegate
{
public:
    MYTextInput();
    ~MYTextInput();
    
    bool init(const Size& size);
    static MYTextInput* create(const Size& size);
    
    void setText(const char* text);
    const char* getText();
    
    virtual void editBoxEditingDidBegin(EditBox* editBox) {};
    virtual void editBoxEditingDidEnd(EditBox* editBox) {};
    virtual void editBoxTextChanged(EditBox* editBox, const std::string& text) {};
    virtual void editBoxReturn(EditBox* editBox);
    
    virtual void editBoxInputDone(const string& str);
public:
    std::function<void(const string&)> textInputDone;
private:
    EditBox* m_editBox;
};
#endif /* defined(__CoolRun__MYTextInput__) */
