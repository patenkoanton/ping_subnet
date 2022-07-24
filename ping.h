#ifndef _PING_H_
#define _PING_H_

#include <string>
#include <vector>
#include <memory>
#include "subnet.h"
#include "socket.h"

class Ping {
    std::shared_ptr<Subnet> subnet;
    std::shared_ptr<Socket> socket;

    int send_icmp_request(uint32_t dest_ip);
    int receive_icmp_reply(std::vector<char> &receive_buffer);
    void parse_package(std::vector<char> &receive_buffer);    
    uint16_t generate_internet_checksum(const void *packet, int packet_size);
public:
    Ping(std::shared_ptr<Subnet> subnet);
    void ping();
};

#endif