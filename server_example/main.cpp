//
//  main.cpp
//  server_example
//
//  Created by mac on 2016. 5. 27..
//  Copyright © 2016년 mac. All rights reserved.
//

#include <iostream>
using namespace std;

#include "Server.hpp"

int main()
{
    cout << "server on!" << endl;
    boost::asio::io_service io;
    Server server(io, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 40000));
    io.run();
}
