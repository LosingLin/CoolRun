//
//  EditorOpenFileMenu.h
//  CoolRun
//
//  Created by ManYou on 15/2/4.
//
//

#ifndef __CoolRun__EditorOpenFileMenu__
#define __CoolRun__EditorOpenFileMenu__

#include "EditorMenu.h"

class EditorText;
class EditorTextInput;
class EditorOpenFileMenu : public EditorMenu
{
public:
    EditorOpenFileMenu();
    ~EditorOpenFileMenu();
    
    virtual bool init() override;
    CREATE_FUNC(EditorOpenFileMenu);
    
    void open();
    void save();
private:
    EditorText* m_open;
    EditorText* m_save;
    EditorTextInput* m_path;
};

#endif /* defined(__CoolRun__EditorOpenFileMenu__) */
