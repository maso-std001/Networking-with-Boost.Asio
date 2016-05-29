//
//  Packet.hpp
//  server_example
//
//  Created by mac on 2016. 5. 27..
//  Copyright © 2016년 mac. All rights reserved.
//

#pragma once

#include <cstring>
#include <cstdlib>

#include <array>

enum class PacketType : int
{
    LOGIN,
    PUT_PLAYER,
    REMOVE_PLAYER,
    CHAT_MESSAGE
};

class Packet
{
    
public:
    
    enum { HEADER_LENGTH = 8 };
    enum { MAX_BODY_LENGTH = 4096 };
    
public:
    
    void encode(uint8_t* body, uint32_t size, PacketType type)
    {
        char bodySize[5] = "";
        char packetType[5] = "";
        sprintf(bodySize, "%04d", static_cast<int>(size));
        sprintf(packetType, "%04d", static_cast<int>(type));
        
        _bodyLength = size;
        
        memcpy(_buffer.data(), bodySize, 4);
        memcpy(_buffer.data() + 4, packetType, 4);
        memcpy(_buffer.data() + 8, body, size);
    }
    
    bool decode()
    {
        char bodySize[5] = "";
        strncat(bodySize, _buffer.data(), 4);
        
        _bodyLength = atoi(bodySize);
        if ( _bodyLength > MAX_BODY_LENGTH)
        {
            _bodyLength = 0;
            return false;
        }
        
        char packetType[5] = "";
        strncat(packetType, _buffer.data() + 4, 4);
        _type = static_cast<PacketType>(atoi(packetType));
        
        return true;
    }
    
    PacketType type() const { return _type; }
    
    uint32_t length() const { return _bodyLength + HEADER_LENGTH; }
    
    uint32_t bodyLength() const { return _bodyLength; }
    
    const char* body() const { return _buffer.data() + HEADER_LENGTH; }
    
    char* body() { return _buffer.data() + HEADER_LENGTH; }
    
    const char* data() const { return _buffer.data(); }
    
    char* data() { return _buffer.data(); }
    
private:
    
    std::array<char, HEADER_LENGTH + MAX_BODY_LENGTH> _buffer;
    
    uint32_t _bodyLength;
    
    PacketType _type;
    
};









