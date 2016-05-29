//
//  Server.cpp
//  client_example
//
//  Created by mac on 2016. 5. 27..
//
//

#include <string>

#include <boost/thread.hpp>
#include <boost/bind.hpp>

#include "Server.hpp"

#include "cocos2d.h"


#include <thread>
#include <functional>

void Server::connect()
{
    
    boost::asio::ip::tcp::resolver resolver(_io);
    auto endpoint = resolver.resolve( boost::asio::ip::tcp::resolver::query("192.168.200.157", "40000"));
    boost::asio::async_connect(_socket, endpoint,
                               [this](const boost::system::error_code& ec,
                                      boost::asio::ip::tcp::resolver::iterator iter)
                               {
                                   if ( !ec )
                                   {
                                       cocos2d::log("<Server::connect> connected!");
                                       
                                       Packet* packet = new Packet();
                                       packet->encode(nullptr, 0, PacketType::LOGIN);
                                       this->write(packet);
                                       
                                       doReadHeader();
                                   }
                                   else
                                   {
                                       cocos2d::log("<Server::connect> error code: %d", ec.value());
                                   }
                               });
    
    boost::thread t(boost::bind(&boost::asio::io_service::run, &_io));
}


void Server::doReadHeader()
{
    boost::asio::async_read(_socket, boost::asio::buffer(_recvBuf.data(), Packet::HEADER_LENGTH),
                            [this](const boost::system::error_code& ec, size_t length)
                            {
                                if ( !ec && _recvBuf.decode() )
                                {
                                    doReadBody();
                                }
                            });
}


void Server::doReadBody()
{
    boost::asio::async_read(_socket, boost::asio::buffer(_recvBuf.body(), _recvBuf.bodyLength()),
                            [this](const boost::system::error_code& ec, size_t length)
                            {
                                if ( !ec )
                                {
                                    Packet* packet = new Packet();
                                    memcpy(packet->data(), _recvBuf.data(), _recvBuf.length());
                                    enqueue(packet);
                                    
                                    doReadHeader();
                                }
                            });
}


void Server::write(Packet* packet)
{
    bool isEmpty = _writeBuf.empty();
    _writeBuf.push_back(packet);
    if ( isEmpty ) doWrite();
}


void Server::doWrite()
{
    boost::asio::async_write(_socket,
                             boost::asio::buffer(_writeBuf.front()->data(), _writeBuf.front()->length()),
                             [this](const boost::system::error_code& ec, size_t length){
                                 
                                 if ( !ec )
                                 {
                                     Packet* packet = _writeBuf.front();
                                     delete packet;
                                     packet = nullptr;
                                     
                                     _writeBuf.pop_front();
                                     if ( !_writeBuf.empty() ) doWrite();
                                 }
                                 
                             });
}









