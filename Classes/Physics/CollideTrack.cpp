//
//  CollideTrack.cpp
//  CoolRun
//
//  Created by ManYou on 14-8-11.
//
//

#include "CollideTrack.h"
#include "PhysicHelp.h"
#include "PhysicNode.h"
#include "Base.h"
#include "Runner.h"

#pragma mark - CollideTrackHelp -

//这里返回的方向是相对于rect1来说的 （方向参照物是rect1）
CollideDirection CollideTrackHelp::trackCollideDirection(const Rect& rect1, const Rect& rect2)
{
    auto direction = kCollideDirectionUnknown;
    
    auto pos1 = Vec2(rect1.origin.x + rect1.size.width/2, rect1.origin.y + rect1.size.height/2);
    auto pos2 = Vec2(rect2.origin.x + rect2.size.width/2, rect2.origin.y + rect2.size.height/2);
    
    auto x_dis = pos2.x - pos1.x;
    auto y_dis = pos2.y - pos1.y;
    //没有碰撞直接返回
    if ((abs(x_dis)*2) >= (rect1.size.width + rect2.size.width) || (abs(y_dis)*2) >= (rect1.size.height + rect2.size.height))
    {
        return kCollideDirectionMiss;
    }
    if ((abs(x_dis)*2) < (rect1.size.width + rect2.size.width)) //x 方向碰撞
    {
        if (x_dis > 0) //right
        {
            direction = kCollideDirectionRight;
        }
        else
        {
            direction = kCollideDirectionLeft;
        }
    }
    
    
    if ((abs(y_dis)*2) < (rect1.size.height + rect2.size.height)) //y 方向碰撞
    {
        if (y_dis > 0) //up
        {
            if (direction != kCollideDirectionMiss)
            {
                if (abs(x_dis) / rect1.size.width < abs(y_dis) / rect2.size.height) //比较x方向和y方向上的碰撞区域
                {
                    direction = kCollideDirectionUp;
                }
            }
            else
            {
                direction = kCollideDirectionUp;
            }
            
        }
        else
        {
            if (direction != kCollideDirectionMiss)
            {
                if (abs(x_dis) / rect1.size.width < abs(y_dis) / rect2.size.height) //比较x方向和y方向上的碰撞区域
                {
                    direction = kCollideDirectionDown;
                }
            }
            else
            {
                direction = kCollideDirectionDown;
            }
        }
    }
    
    return direction;
}

bool CollideTrackHelp::trackCollide(const Rect& rect1, const Rect& rect2)
{
    auto pos1 = Vec2(rect1.origin.x + rect1.size.width/2, rect1.origin.y + rect1.size.height/2);
    auto pos2 = Vec2(rect2.origin.x + rect2.size.width/2, rect2.origin.y + rect2.size.height/2);
    
    auto x_dis = pos2.x - pos1.x;
    auto y_dis = pos2.y - pos1.y;
    
    //没有碰撞直接返回
    if ((abs(x_dis)*2) > (rect1.size.width + rect2.size.width) || (abs(y_dis)*2) > (rect1.size.height + rect2.size.height))
    {
        return false;
    }
    
    return true;
}

float CollideTrackHelp::trackDistance(const Rect& rect1, const Rect& rect2, CollideDirection direction)
{
    return 0.0f;
}

//检测是否靠近右边
bool CollideTrackHelp::isNearRight(const Rect& rect1, const Rect& rect2, float distance, bool ignoreY)
{
    auto pos1 = Vec2(rect1.origin.x + rect1.size.width/2, rect1.origin.y + rect1.size.height/2);
    auto pos2 = Vec2(rect2.origin.x + rect2.size.width/2, rect2.origin.y + rect2.size.height/2);
    
    auto x_dis = pos2.x - pos1.x;
    auto y_dis = pos2.y - pos1.y;
    
    //如果rect2已经过了rect1的left则返回
    if (x_dis < 0)
    {
        return false;
    }
    //如果y方向上没有碰撞直接返回
    if (!ignoreY)
    {
        if ((abs(y_dis)*2) > (rect1.size.height + rect2.size.height +  distance))
        {
            return false;
        }
    }
    
    auto _gap = rect2.origin.x - rect1.origin.x - rect1.size.width;
    if (_gap <= distance)
    {
        return true;
    }
    return false;
}

#pragma mark - CollideTrack -

CollideTrack::CollideTrack()
: Ref()
, m_physicNodes(NULL)
, m_ctListener(NULL)
{
}
CollideTrack::~CollideTrack()
{
    CC_SAFE_RELEASE_NULL(m_physicNodes);
}

bool CollideTrack::init()
{
    m_physicNodes = __Array::create();
    CC_SAFE_RETAIN(m_physicNodes);
    
    return true;
}

void CollideTrack::addPhysicNode(PhysicNode *pNode)
{
    m_physicNodes->addObject(pNode);
}
void CollideTrack::removePhysicNode(PhysicNode *pNode)
{
    m_physicNodes->removeObject(pNode);
}

void CollideTrack::setCollideTrackListener(CollideTrackListener *listener)
{
    m_ctListener = listener;
}

void CollideTrack::collideTrackPhysicNode(PhysicNode *runner)
{
    PhysicNode* node1 = NULL;
    int cTimes[kCollideDirectionTotal] = {0};
    int pNodeIndex[kCollideDirectionTotal] = {0};
    auto pNodeCount = m_physicNodes->count();
    for (int i = 0; i < pNodeCount; ++ i)
    {
        node1 = dynamic_cast<PhysicNode*>(m_physicNodes->getObjectAtIndex(i));
        
        if (!node1->isCollideEffect())
        {
            cTimes[kCollideDirectionMiss] ++;
            pNodeIndex[kCollideDirectionMiss] = i;
            continue;
        }
        
        auto rect1 = PhysicHelp::countPhysicNodeRect(node1);
        auto rect2 = PhysicHelp::countPhysicNodeRect(runner);
        
        auto direction = this->trackCollideDirection(rect1, rect2);
        
        switch (direction) {
            case kCollideDirectionUnknown:
            {
                cTimes[kCollideDirectionUnknown] ++;
                pNodeIndex[kCollideDirectionUnknown] = i;
            }
                break;
            case kCollideDirectionMiss:
            {
                cTimes[kCollideDirectionMiss] ++;
                pNodeIndex[kCollideDirectionMiss] = i;
            }
                break;
            case kCollideDirectionLeft:
            {
                cTimes[kCollideDirectionLeft] ++;
                pNodeIndex[kCollideDirectionLeft] = i;
            }
                break;
            case kCollideDirectionRight:
            {
                cTimes[kCollideDirectionRight] ++;
                pNodeIndex[kCollideDirectionRight] = i;
            }
                break;
            case kCollideDirectionUp:
            {
                cTimes[kCollideDirectionUp] ++;
                pNodeIndex[kCollideDirectionUp] = i;
            }
                break;
            case kCollideDirectionDown:
            {
                cTimes[kCollideDirectionDown] ++;
                pNodeIndex[kCollideDirectionDown] = i;
            }
                break;
                
            default:
                break;
        }
    }
    for (int i = kCollideDirectionUnknown; i < kCollideDirectionTotal; ++ i) {
        if (cTimes[i] > 0)
        {
            //log("%d : %d", i, cTimes[i]);
            if (cTimes[i] == pNodeCount)
            {
                runner->CollideTrackListener_CollideAll((CollideDirection)i);
                return;
            }
            
            auto node = dynamic_cast<PhysicNode*>(m_physicNodes->getObjectAtIndex(pNodeIndex[i]));
            runner->CollideTrackListener_CollideOnce((CollideDirection)i, node);
            
            return;
        }
    }
    
    
}
void CollideTrack::collideTrackUpdate()
{
    PhysicNode* node1 = NULL;
    PhysicNode* node2 = NULL;
    CollideDirection direction = kCollideDirectionUnknown;
    
    for (int i = 0; i < m_physicNodes->count(); ++ i)
    {
        node1 = dynamic_cast<PhysicNode*>(m_physicNodes->getObjectAtIndex(i));
        
        if (!node1->isCollideEffect())
        {
            continue;
        }
        
        for (int j = i+1; j < m_physicNodes->count(); ++ j) {
            node2 = dynamic_cast<PhysicNode*>(m_physicNodes->getObjectAtIndex(j));
            
            if (!node2->isCollideEffect())
            {
                continue;
            }
            
            auto rect1 = PhysicHelp::countPhysicNodeRect(node1);
            auto rect2 = PhysicHelp::countPhysicNodeRect(node2);
            
            
            direction = this->trackCollideDirection(rect1, rect2);
            
            auto csize1 = node1->getContentSize();
            auto csize2 = node2->getContentSize();
            
            switch (direction) {
                case kCollideDirectionUnknown:
                {
                }
                    break;
                case kCollideDirectionMiss:
                {
                }
                    break;
                case kCollideDirectionLeft:
                {
                    auto dis = rect2.size.width - rect1.origin.x + rect2.origin.x;
                    
                    if (csize1.width * csize1.height > csize2.width*csize2.height)
                    {
                        auto pos = node2->getPosition();
                        pos.x -= dis;
                        node2->setPosition(pos);
                    }
                    else
                    {
                        auto pos = node1->getPosition();
                        pos.x += dis;
                        node1->setPosition(pos);
                    }
                    PhysicHelp::exchangePhysicNode_XV_XA(node1, node2);
                }
                    break;
                case kCollideDirectionRight:
                {
                    auto dis = rect1.size.width - rect2.origin.x + rect1.origin.x;
                    
                    if (csize1.width * csize1.height > csize2.width*csize2.height)
                    {
                        auto pos = node2->getPosition();
                        pos.x += dis;
                        node2->setPosition(pos);
                    }
                    else
                    {
                        auto pos = node1->getPosition();
                        pos.x -= dis;
                        node1->setPosition(pos);
                    }
                    PhysicHelp::exchangePhysicNode_XV_XA(node1, node2);
                }
                    break;
                case kCollideDirectionUp:
                {
                    auto dis = rect1.size.height - rect2.origin.y + rect1.origin.y;
                    if (csize1.width * csize1.height > csize2.width*csize2.height)
                    {
                        auto pos = node2->getPosition();
                        pos.y += dis;
                        node2->setPosition(pos);
                    }
                    else
                    {
                        auto pos = node1->getPosition();
                        pos.y -= dis;
                        node1->setPosition(pos);
                    }
                    PhysicHelp::exchangePhysicNode_YV_YA(node1, node2);
                }
                    break;
                case kCollideDirectionDown:
                {
                    auto dis = rect2.size.height - rect1.origin.y + rect2.origin.y;
                    if (csize1.width * csize1.height > csize2.width*csize2.height)
                    {
                        auto pos = node2->getPosition();
                        pos.y -= dis;
                        node2->setPosition(pos);
                    }
                    else
                    {
                        auto pos = node1->getPosition();
                        pos.y += dis;
                        node1->setPosition(pos);
                    }
                    PhysicHelp::exchangePhysicNode_YV_YA(node1, node2);
                }
                    break;
                    
                default:
                    break;
            }
        }
    }
}

CollideDirection CollideTrack::trackCollideDirection(const Rect& rect1, const Rect& rect2)
{
    auto direction = kCollideDirectionUnknown;
    
    auto pos1 = Vec2(rect1.origin.x + rect1.size.width/2, rect1.origin.y + rect1.size.height/2);
    auto pos2 = Vec2(rect2.origin.x + rect2.size.width/2, rect2.origin.y + rect2.size.height/2);
    
    auto x_dis = pos2.x - pos1.x;
    auto y_dis = pos2.y - pos1.y;
    //没有碰撞直接返回
    if ((abs(x_dis)*2) >= (rect1.size.width + rect2.size.width) || (abs(y_dis)*2) >= (rect1.size.height + rect2.size.height))
    {
        return kCollideDirectionMiss;
    }
//    PRINTRECT(rect1);
//    PRINTRECT(rect2);
//    log("x_dis = %f, y_dis = %f", x_dis, y_dis);
    if ((abs(x_dis)*2) < (rect1.size.width + rect2.size.width)) //x 方向碰撞
    {
        if (x_dis > 0) //right
        {
            direction = kCollideDirectionRight;
        }
        else
        {
            direction = kCollideDirectionLeft;
        }
    }
    
//    log("1_direction = %d", direction);
    
    if ((abs(y_dis)*2) < (rect1.size.height + rect2.size.height)) //y 方向碰撞
    {
        if (y_dis > 0) //up
        {
            if (direction != kCollideDirectionMiss)
            {
                if (abs(x_dis) / rect1.size.width < abs(y_dis) / rect2.size.height) //比较x方向和y方向上的碰撞区域
                {
                    direction = kCollideDirectionUp;
                }
            }
            else
            {
                direction = kCollideDirectionUp;
            }
            
        }
        else
        {
            if (direction != kCollideDirectionMiss)
            {
                if (abs(x_dis) / rect1.size.width < abs(y_dis) / rect2.size.height) //比较x方向和y方向上的碰撞区域
                {
                    direction = kCollideDirectionDown;
                }
            }
            else
            {
                direction = kCollideDirectionDown;
            }
        }
    }
    
    return direction;
}

bool CollideTrack::trackCollide(const Rect& rect1, const Rect& rect2)
{
    auto pos1 = Vec2(rect1.origin.x + rect1.size.width/2, rect1.origin.y + rect1.size.height/2);
    auto pos2 = Vec2(rect2.origin.x + rect2.size.width/2, rect2.origin.y + rect2.size.height/2);
    
    auto x_dis = pos2.x - pos1.x;
    auto y_dis = pos2.y - pos1.y;
    
    //没有碰撞直接返回
    if ((abs(x_dis)*2) > (rect1.size.width + rect2.size.width) || (abs(y_dis)*2) > (rect1.size.height + rect2.size.height))
    {
        return false;
    }
    
    return true;
}
