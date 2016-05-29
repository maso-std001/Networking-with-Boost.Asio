//
//  Server.cpp
//  server_example
//
//  Created by mac on 2016. 5. 27..
//  Copyright © 2016년 mac. All rights reserved.
//

#include <iostream>

#include "Server.hpp"
#include "Session.hpp"

Server::Server(boost::asio::io_service& io, boost::asio::ip::tcp::endpoint endpoint)
: _socket(io), _acceptor(io, endpoint), _sessionManager(*this)
{
    doAccept();
}


void Server::doAccept()
{
    _acceptor.async_accept(_socket, [this](const boost::system::error_code& ec){
        
        if ( !ec )
        {
            std::cout << "<Serer::doAccept> client connected." << std::endl;
            std::make_shared<Session>(_sessionManager, std::move(_socket))->start();
        }
        else
        {
            std::cout << "<Server::doAccept> error code " << ec.value() << std::endl;
        }

        doAccept();
        
    });
}









