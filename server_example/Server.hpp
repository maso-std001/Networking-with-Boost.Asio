//
//  Server.hpp
//  server_example
//
//  Created by mac on 2016. 5. 27..
//  Copyright © 2016년 mac. All rights reserved.
//

#pragma once

#include <boost/noncopyable.hpp>
#include <boost/asio.hpp>

#include "SessionManager.hpp"

class Server : public boost::noncopyable
{
    
public:
    
    Server(boost::asio::io_service& io, boost::asio::ip::tcp::endpoint endpoint);
    
    virtual ~Server() = default;
    
private:
    
    void doAccept();
    
private:
    
    boost::asio::ip::tcp::socket _socket;
    
    boost::asio::ip::tcp::acceptor _acceptor;
    
    SessionManager _sessionManager;
    
};









