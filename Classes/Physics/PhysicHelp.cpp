//
//  PhysicHelp.cpp
//  CoolRun
//
//  Created by ManYou on 14-8-12.
//
//

#include "PhysicHelp.h"
#include "PhysicNode.h"


void PhysicHelp::exchangePhysicNode_XV_XA(PhysicNode *node1, PhysicNode *node2)
{
    auto tV = (node1)->getXV();       
    (node1)->setXV((node2)->getXV());
    (node2)->setXV(tV);
    auto aV = (node1)->getXA();
    (node1)->setXA((node2)->getXA());
    (node2)->setXA(aV);
}
void PhysicHelp::exchangePhysicNode_YV_YA(PhysicNode *node1, PhysicNode *node2)
{
    auto tV = (node1)->getYV();
    (node1)->setYV((node2)->getYV());
    (node2)->setYV(tV);
    auto aV = (node1)->getYA();
    (node1)->setYA((node2)->getYA());
    (node2)->setYA(aV);
}

const Rect PhysicHelp::countPhysicNodeRect(PhysicNode *node)
{
    return PhysicHelp::countPhysicNodeRect(node, node->getCollideRect());
}

const Rect PhysicHelp::countPhysicNodeRect(PhysicNode *node, const Rect& rect)
{
    auto pos1 = node->getPosition();
    auto aP1 = node->getAnchorPoint();
    auto csize1 = node->getContentSize();
    
    pos1.x -= csize1.width*aP1.x;
    pos1.y -= csize1.height*aP1.y;
    
    auto rect1 = Rect(rect);
    rect1.origin.x += pos1.x;
    rect1.origin.y += pos1.y;
    
    return rect1;
}

void PhysicHelp::showTips(const char* tips, Node *parent, const Vec2& pos)
{
#if defined(COCOS2D_DEBUG) && (COCOS2D_DEBUG > 0)
    auto _label = Label::createWithTTF(tips, "Marker Felt.ttf", 32);
    _label->setPosition(pos);
    parent->addChild(_label, 10);
    
    auto _scale = ScaleTo::create(0.5, 2);
    auto _fadeout = FadeOut::create(0.5);
    auto _callback = CallFunc::create(CC_CALLBACK_0(PhysicHelp::showTipsOver, nullptr, _label));
    auto _sequence = Sequence::create(_scale, _fadeout, _callback, NULL);
    _label->runAction(_sequence);
#endif
    
//    auto fun1 = [_label](){ log("%s", _label->getString().c_str()); };
//    fun1();
}

void PhysicHelp::showTipsOver(Node *node, Node *label)
{
    label->removeFromParent();
}