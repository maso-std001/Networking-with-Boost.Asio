#include <string>

#include "HelloWorldScene.h"
using namespace cocos2d;

#include "Server.hpp"
#include "GeneratedPackets.hpp"

Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();
    auto layer = HelloWorld::create();
    scene->addChild(layer);
    return scene;
}

bool HelloWorld::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    this->scheduleUpdate();
    
    auto connectButton = ui::Button::create("CloseNormal.png", "CloseSelected.png");
    connectButton->setPosition(Vec2(568, 320));
    connectButton->setScale(3.0f);
    connectButton->addTouchEventListener([this](Ref* ref, ui::Widget::TouchEventType type){
        
        if ( type == ui::Widget::TouchEventType::ENDED )
        {
            _server.connect();
            ui::Button* self = static_cast<ui::Button*>(ref);
            self->removeFromParent();
        }
        
    });
    addChild(connectButton);
    
    auto spr = Sprite::create("CloseNormal.png");
    spr->setPosition(100, 100);
    spr->runAction(RepeatForever::create(Sequence::create(MoveBy::create(5, Vec2(1000,0)),
                                                          MoveBy::create(5, Vec2(-1000, 0)),
                                                          nullptr)));
    addChild(spr);
    
    _players = Node::create();
    addChild(_players);
    
    return true;
}


void HelloWorld::update(float dt)
{
    // process packet
    if ( !_server.isQueueEmpty() )
    {
        Packet* packet;
        _server.dequeue(packet);
        packet->decode();
        
        switch ( packet->type() )
        {
            case PacketType::PUT_PLAYER:
            {
                auto obj = fpacket::GetPacketPutPlayer(packet->body());
                auto spr = Sprite::create("grossini.png");
                spr->setTag(obj->id());
                spr->setPosition(obj->x(), obj->y());
                _players->addChild(spr);
                
                break;
            }
                
            case PacketType::REMOVE_PLAYER:
            {
                auto obj = fpacket::GetPacketRemovePlayer(packet->body());
                _players->removeChildByTag(obj->id());
                
                break;
            }
                
            case PacketType::CHAT_MESSAGE:
            {
                break;
            }
                
            default: break;
        }
        
        delete packet;
        packet = nullptr;
    }
    // etc...
}









