//
//  EditorTextInput.h
//  CoolRun
//
//  Created by ManYou on 15/1/30.
//
//

#ifndef __CoolRun__EditorTextInput__
#define __CoolRun__EditorTextInput__

#include "EditorNode.h"

using namespace std;

class MYTextInput;
class EditorTextInput : public EditorNode
{
public:
    EditorTextInput();
    ~EditorTextInput();
    
    virtual bool init() override;
    bool init(const string& title, const Size& csize);
    static EditorTextInput* create(const string& title, const Size& csize);
    void inputDone(const string& text);
    
    void setText(const string& text);
    const char* getText();
public:
    std::function<void(const string&)> textInputDone;
private:
    MYTextInput* m_input;
};

#endif /* defined(__CoolRun__EditorTextInput__) */
