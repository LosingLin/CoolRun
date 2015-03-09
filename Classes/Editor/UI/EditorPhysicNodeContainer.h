//
//  EditorPhysicNodeContainer.h
//  CoolRun
//
//  Created by ManYou on 15/1/29.
//
//

#ifndef __CoolRun__EditorPhysicNodeContainer__
#define __CoolRun__EditorPhysicNodeContainer__

#include "EditorNode.h"
#include "PhysicNode.h"
#include "PhysicNodeFactory.h"

class EditorDetailMenu;
class Collection;
class EditorPhysicNodeContainer : public EditorNode
{
public:
    EditorPhysicNodeContainer();
    ~EditorPhysicNodeContainer();
    
    virtual bool init() override;
    CREATE_FUNC(EditorPhysicNodeContainer);
    
    bool init(const Size& csize, PhysicNode* pNode);
    static EditorPhysicNodeContainer* create(const Size& csize, PhysicNode* pNode);
    
    bool init(PhysicNode* pNode);
    static EditorPhysicNodeContainer* create(PhysicNode* pNode);
    
    virtual void setContentSize(const Size& _size) override;
    
    void setPhysicNode(PhysicNode* pNode);
    PhysicNode* getPhysicNode() { return m_pNode; }
    
    void savePhysicNodeInfo(string* buffer);
    
    void setPhysicNodeType(PhysicNodeType type) { m_pType = type; }
    PhysicNodeType getPhysicType() { return m_pType; }
    
    void setDetailMenu(EditorDetailMenu* dMenu);
    EditorDetailMenu* getDetailMenu() { return m_detailMenu; }
    
    static PhysicNode* createBasePhysicNode(PhysicNodeType type);
    static PhysicNode* createBaseCollectionPhysicNode(int cmIndx);
    static Collection* createBaseCollection(int cmIndx);
    
    virtual void editorNodeTouchBegan() override;
    virtual void editorNodeTouchMoved(int x, int y) override;
    virtual void editorNodeNoneMoveEnded() override;
    virtual void editorNodeMoveEnded() override;
private:
    void _showDetailMenu();
private:
    bool b_isMenu;
    PhysicNode* m_pNode;
    PhysicNodeType m_pType;
    Scale9Sprite* m_frame;
    
    EditorDetailMenu* m_detailMenu;
};

#endif /* defined(__CoolRun__EditorPhysicNodeContainer__) */
