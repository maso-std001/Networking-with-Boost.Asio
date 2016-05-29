//
//  Server.hpp
//  client_example
//
//  Created by mac on 2016. 5. 27..
//
//

#pragma once

#include <deque>

#include <boost/asio.hpp>


#include <boost/lockfree/queue.hpp>

#include "Packet.hpp"

class Server
{
    
public:
    
    Server() : _socket(_io), _queue(512) {}
    
    virtual ~Server() = default;
    
    void connect();
    
    void write(Packet* packet);
    
    bool isQueueEmpty() const { return _queue.empty(); }
    
    void dequeue(Packet*& packet) { while ( !_queue.pop(packet) ); }
    
    void enqueue(Packet* packet) { while ( !_queue.push(packet) ); }
    
private:
    
    void doReadHeader();
    
    void doReadBody();
    
    void doWrite();
    
private:
    
    boost::asio::io_service _io;
    
    boost::asio::ip::tcp::socket _socket;
    
    Packet _recvBuf;
    
    std::deque<Packet*> _writeBuf;
    
    boost::lockfree::queue<Packet*> _queue;
    
};









