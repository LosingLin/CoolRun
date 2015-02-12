//
//  PhysicNodeFactory.cpp
//  CoolRun
//
//  Created by ManYou on 14-8-15.
//
//

#include "PhysicNodeFactory.h"
#include "PhysicNode.h"
#include "Stone.h"
#include "Coin.h"
#include "Enemy.h"
#include "Spider.h"
#include "SpiderKind.h"
#include "SpiderPoison.h"
#include "SpiderSpines.h"
#include "PoisonBullet.h"
#include "AlertBullet.h"
#include "Item.h"
#include "ItemSpare.h"
#include "ItemMagnet.h"
#include "ItemTimesCoin.h"
#include "ItemTimesJump.h"
#include "ItemDad.h"
#include "ItemLandBuild.h"
#include "ItemFly.h"

PhysicNodeFactory* PhysicNodeFactory::m_instance = NULL;

PhysicNodeFactory::PhysicNodeFactory()
{

}
PhysicNodeFactory::~PhysicNodeFactory()
{
    this->purgeInstance();
}

PhysicNodeFactory* PhysicNodeFactory::getInstance()
{
    if (m_instance == NULL) {
        m_instance = new PhysicNodeFactory();
    }
    
    return m_instance;
}
void PhysicNodeFactory::purgeInstance()
{
    if (m_instance) {
        delete m_instance;
    }
}


PhysicNode* PhysicNodeFactory::create(rapidjson::Value& _value)
{
    auto pNodeType = kPhysicNodeUnknown;
    PhysicNode *_pNode = NULL;
    if (_value.HasMember("pNodeType")) {
        pNodeType = (PhysicNodeType)JsonHelp::getInt(_value["pNodeType"]);
    }
    switch (pNodeType) {
        case kPhysicNodeStone:
        {
            _pNode = Stone::create();
        } break;
        case kPhysicNodeCoin:
        {
            _pNode = Coin::create();
        } break;
        case kPhysicNodeEnemy:
        {
            _pNode = Enemy::create();
        } break;
        case kPhysicNodeSpider:
        {
            _pNode = Spider::create();
        } break;
        case kPhysicNodeSpiderKind:
        {
            _pNode = SpiderKind::create();
        } break;
        case kPhysicNodeSpiderPoison:
        {
            _pNode = SpiderPoison::create();
        } break;
        case kPhysicNodeSpiderSpines:
        {
            _pNode = SpiderSpines::create();
            
        } break;
        case kPhysicNodeBulletPoison:
        {
            _pNode = PoisonBullet::create();
            
        } break;
        case kPhysicNodeBulletAlert:
        {
            _pNode = AlertBullet::create();
        } break;
        case kPhysicNodeItem:
        {
            _pNode = Item::create();
        } break;
        case kPhysicNodeItemSpare:
        {
            _pNode = ItemSpare::create();
        } break;
        case kPhysicNodeItemMagnet:
        {
            _pNode = ItemMagnet::create();
        } break;
        case kPhysicNodeItemTimesCoin:
        {
            _pNode = ItemTimesCoin::create();
        } break;
        case kPhysicNodeItemTimesJump:
        {
            _pNode = ItemTimesJump::create();
        } break;
        case kPhysicNodeItemDad:
        {
            _pNode = ItemDad::create();
        } break;
        case kPhysicNodeItemLandBuild:
        {
            _pNode = ItemLandBuild::create();
        } break;
        case kPhysicNodeItemFly:
        {
            _pNode = ItemFly::create();
        } break;
        default:
            break;
    }
    _pNode->setPhysicNodeType(pNodeType);
    _pNode->loadJson(_value);
    
    return _pNode;
}