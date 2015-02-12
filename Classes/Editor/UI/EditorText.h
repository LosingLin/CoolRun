//
//  EditorText.h
//  CoolRun
//
//  Created by ManYou on 15/1/29.
//
//

#ifndef __CoolRun__EditorText__
#define __CoolRun__EditorText__

#include "EditorNode.h"

class EditorText : public EditorNode
{
public:
    EditorText();
    ~EditorText();
    
    virtual bool init() override;
    bool init(const string& text, const Size& csize,  int fontSize);
    static EditorText* create(const string& text, const Size& csize, int fontSize);
    
    void setText(const string& text);
    const string getText();
private:
    Label* m_label;
};

#endif /* defined(__CoolRun__EditorText__) */
