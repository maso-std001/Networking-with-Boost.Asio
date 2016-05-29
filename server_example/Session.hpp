//
//  Session.hpp
//  server_example
//
//  Created by mac on 2016. 5. 27..
//  Copyright © 2016년 mac. All rights reserved.
//

#include <boost/asio.hpp>

#include <deque>

#include "Packet.hpp"

class SessionManager;

class Session : public std::enable_shared_from_this<Session>
{
    
public:
    
    explicit Session(SessionManager& mgr, boost::asio::ip::tcp::socket socket);
    
    virtual ~Session() = default;
 
    void write(Packet* packet);
    
    void start();
    
    void close();
    
    void setID(int id) { _id = id; }
    
    int getID() const { return _id; }
    
    void setPosition(float x, float y) { _positionX = x; _positionY = y; }
    
    float getPositionX() const { return _positionX; }
    
    float getPositionY() const { return _positionY; }
    
private:
    
    void doReadHeader();
    
    void doReadBody();
    
    void doWrite();
    
private:
    
    boost::asio::ip::tcp::socket _socket;
    
    Packet _recvBuf;
    
    std::deque<Packet*> _writeBuf;
    
    SessionManager& _sessionManager;
    
    int _id;
    
    float _positionX;
    
    float _positionY;
    
};









