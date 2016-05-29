//
//  Session.cpp
//  server_example
//
//  Created by mac on 2016. 5. 27..
//  Copyright © 2016년 mac. All rights reserved.
//

#include <iostream>
using namespace std;

#include "Session.hpp"
#include "SessionManager.hpp"
#include "GeneratedPackets.hpp"

Session::Session(SessionManager& mgr, boost::asio::ip::tcp::socket socket) :
_sessionManager(mgr),
_socket(std::move(socket)),
_id(-1),
_positionX(0),
_positionY(0)
{
}


void Session::write(Packet* packet)
{
    bool isEmpty = _writeBuf.empty();
    _writeBuf.push_back(packet);
    if ( isEmpty )
    {
        doWrite();
    }
}


void Session::start()
{
    doReadHeader();
}


void Session::close()
{
    _socket.close();
}


void Session::doReadHeader()
{
    auto self(shared_from_this());
    boost::asio::async_read(_socket,
                            boost::asio::buffer(_recvBuf.data(), Packet::HEADER_LENGTH),
                            [this, self](const boost::system::error_code& ec, size_t length)
                            {
                                if ( !ec && _recvBuf.decode() )
                                {
                                    doReadBody();
                                }
                                else
                                {
                                    if (boost::asio::error::eof == ec || boost::asio::error::connection_reset == ec )
                                    {
                                        cout << "<Seession::doReadHeader> session disconnected" << endl;
                                        _sessionManager.removeSession(self);
                                    }
                                }
                            });
}


void Session::doReadBody()
{
    auto self(shared_from_this());
    boost::asio::async_read(_socket,
                            boost::asio::buffer(_recvBuf.body(), _recvBuf.bodyLength()),
                            [this, self](const boost::system::error_code& ec, size_t length)
                            {
                                if ( !ec )
                                {
                                    // packet process
                                    PacketType type = _recvBuf.type();
                                    if ( type == PacketType::LOGIN )
                                    {
                                        _sessionManager.createSession(self);
                                    }
                                    
                                    if ( type == PacketType::CHAT_MESSAGE )
                                    {
                                        
                                    }
                                    
                                    doReadHeader();
                                }
                                else
                                {
                                    if (boost::asio::error::eof == ec || boost::asio::error::connection_reset == ec )
                                    {
                                        cout << "<Seession::doReadBody> session disconnected" << endl;
                                        _sessionManager.removeSession(self);
                                    }
                                }
                            });
}


void Session::doWrite()
{
    auto self(shared_from_this());
    boost::asio::async_write(_socket,
                             boost::asio::buffer(_writeBuf.front()->data(), _writeBuf.front()->length()),
                             [this, self](const boost::system::error_code& ec, size_t length)
                             {
                                 Packet* packet = _writeBuf.front();
                                 delete packet;
                                 packet = nullptr;
                                 
                                 _writeBuf.pop_front();
                                 if ( !_writeBuf.empty() )
                                 {
                                     doWrite();
                                 }
                             });
}









