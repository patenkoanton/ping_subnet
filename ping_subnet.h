#ifndef _PING_SUBNET_H_
#define _PING_SUBNET_H_

#include <string>
#include <vector>
#include <memory>
#include "address_range.h"
#include "icmp_socket.h"

class PingSubnet {
    std::unique_ptr<AddressRange> address_range;
    std::unique_ptr<ICMPSocket> icmp_socket;
    

    int send_icmp_request(uint32_t dest_ip);
    int receive_icmp_reply(std::vector<char> &receive_buffer);
    void parse_package(std::vector<char> &receive_buffer);    
    uint16_t generate_internet_checksum(const void *packet, int packet_size);
public:
    PingSubnet(std::string address_and_mask);
    const std::vector<uint32_t> &get_address_range();
    void ping();
};

#endif