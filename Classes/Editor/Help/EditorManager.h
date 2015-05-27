//
//  EditorManager.h
//  CoolRun
//
//  Created by ManYou on 15/5/14.
//
//

#ifndef __CoolRun__EditorManager__
#define __CoolRun__EditorManager__

#include "cocos2d.h"

USING_NS_CC;
using namespace std;

class EditorManager : public Ref
{
public:
    enum class EditorType
    {
        PLAYER,
        DEVELOPER
    };
    static EditorManager* getInstance();
    static void purgeInstance();
    
    void setEditorType(EditorType _type) { m_editorType = _type; }
    EditorType getEditorType() { return m_editorType; }
    
private:
    EditorManager();
    ~EditorManager();
    
    static EditorManager* m_instance;
    static EditorType m_editorType;
};

#endif /* defined(__CoolRun__EditorManager__) */
