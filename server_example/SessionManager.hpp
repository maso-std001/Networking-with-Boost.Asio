//
//  SessionManager.hpp
//  server_example
//
//  Created by mac on 2016. 5. 27..
//  Copyright © 2016년 mac. All rights reserved.
//

#pragma once

#include <map>
#include <memory>

#include "Packet.hpp"

class Session;
class Server;

class SessionManager
{
    
public:
    
    explicit SessionManager(Server& server) : _server(server) {}
    
    virtual ~SessionManager() = default;
    
    bool insertSession(int id, std::shared_ptr<Session> ptr);
    
    bool eraseSession(int id);
    
    std::shared_ptr<Session> findSession(int id);
    
    int getNextValidID() const { return _nextValidID++; }
    
    void deliverPacket(int id, Packet* packet);
    
    void createSession(std::shared_ptr<Session> session);
    
    static int random(int min, int max);
    
    void removeSession(std::shared_ptr<Session> session);
    
private:
    
    Server& _server;
    
    std::map<int, std::shared_ptr<Session>> _sessions;
    
    static int _nextValidID;
    
};









