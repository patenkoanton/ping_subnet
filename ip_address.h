#ifndef _IP_ADDRESS_H
#define _IP_ADDRESS_H

#include <stdint.h>
#include <string>


class IPAddress {
    uint32_t host_order = 0;
    uint32_t network_order = 0;
    uint32_t reverse_byte_order(uint32_t input);
public:
    IPAddress(uint32_t ip_host_order);
    IPAddress(const std::string &ip_string);
    uint32_t to_network() const;
    uint32_t to_host() const;
    std::string to_string() const;

    // Make calculations easier.
    IPAddress operator&(uint32_t arg) const;
    IPAddress operator+(uint32_t arg) const;
    IPAddress operator-(uint32_t arg) const;
    bool operator<(const IPAddress &arg) const;
    IPAddress operator++(int);
    friend std::ostream& operator<<(std::ostream& stream, const IPAddress& arg);
};


#endif // _IP_ADDRESS_H