//
//  SessionManager.cpp
//  server_example
//
//  Created by mac on 2016. 5. 27..
//  Copyright © 2016년 mac. All rights reserved.
//

#include <iostream>
#include <random>
using namespace std;

#include "SessionManager.hpp"
#include "Server.hpp"
#include "Session.hpp"
#include "GeneratedPackets.hpp"

int SessionManager::_nextValidID = 0;

bool SessionManager::insertSession(int id, shared_ptr<Session> ptr)
{
    auto session = findSession(id);
    if ( !session )
    {
        _sessions.insert( {id, ptr} );
        cout << "session size: " << _sessions.size() << endl;
        return true;
    }
    cout << "<SessionManager::insertSession> session is already exist" << endl;
    return false;
}


bool SessionManager::eraseSession(int id)
{
    auto session = findSession(id);
    if ( !session )
    {
        cout << "<SessionManager::eraseSession> id is not exist" << endl;
        return false;
    }
    _sessions.erase(id);
    return true;
}


std::shared_ptr<Session> SessionManager::findSession(int id)
{
    auto iter = _sessions.find(id);
    if ( iter == end(_sessions) )
    {
        cout << "<SessionManager::findSession> id is not exist" << endl;
        return nullptr;
    }
    return iter->second;
}


void SessionManager::deliverPacket(int id, Packet* packet)
{
    findSession(id)->write(packet);
}


void SessionManager::createSession(std::shared_ptr<Session> session)
{
    int id = getNextValidID();
    float x = random(100, 700);
    float y = random(100, 450);
    if ( !insertSession(id, session) )
    {
        session.reset();
        return ;
    }
    
    session->setID(id);
    session->setPosition(x, y);

    flatbuffers::FlatBufferBuilder builder;
    auto obj = fpacket::CreatePacketPutPlayer(builder, id,  x,  y);
    builder.Finish(obj);
    
    {
        // 내 자신에게 PUT_PLAYER 패킷을 보낸다.
        Packet* packet = new Packet();
        packet->encode(builder.GetBufferPointer(), builder.GetSize(), PacketType::PUT_PLAYER);
        session->write(packet);
    }
    
    for(auto& se : _sessions)
    {
        if ( id == se.second->getID() )
            continue;
        
        {
            // 다른 플레이어에게 내가 만들어졌다는 것을 알려줌)
            Packet* packet = new Packet();
            packet->encode(builder.GetBufferPointer(), builder.GetSize(), PacketType::PUT_PLAYER);
            se.second->write(packet);
            cout << "<SessionManager::createSession> send my info to others" << endl;
        }
        
        {
            // 다른 플레이어의 정보를 나에게 알려준다.
            flatbuffers::FlatBufferBuilder builder;
            auto obj = fpacket::CreatePacketPutPlayer(builder, se.second->getID(),
                                                      se.second->getPositionX(),
                                                      se.second->getPositionY());
            builder.Finish(obj);
            
            Packet* packet = new Packet();
            packet->encode(builder.GetBufferPointer(), builder.GetSize(), PacketType::PUT_PLAYER);
            session->write(packet);
            cout << "<SessionManager::createSession> send other info to me" << endl;
        }
    }
    
}


void SessionManager::removeSession(std::shared_ptr<Session> session)
{
    // 다른 유저에게 로그아웃을 알린다.
    int id = session->getID();
    for(auto& se : _sessions)
    {
        if ( id == se.second->getID() )
            continue;
        
        flatbuffers::FlatBufferBuilder builder;
        auto obj = fpacket::CreatePacketRemovePlayer(builder, id);
        builder.Finish(obj);
        
        Packet* packet = new Packet();
        packet->encode(builder.GetBufferPointer(), builder.GetSize(), PacketType::REMOVE_PLAYER);
        se.second->write(packet);
    }
    
    // 내 세션을 지운다.
    eraseSession(id);
    session.reset();
}


int SessionManager::random(int min, int max)
{
    static random_device rd;
    static mt19937 mt(rd());
    uniform_int_distribution<> id(min, max);
    return id(mt);
}






