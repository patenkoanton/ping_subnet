#include <string>
#include <cstring>  // strerror
#include <sys/time.h>
#include <netdb.h>
#include <unistd.h>
#include <iostream>
#include "socket.h"


Socket::Socket(int socket_timeout_sec)
{
    // Open socket
    if (this->open_socket() < 0) {
        throw std::string("failed to open socket.");
    }

    // Configure socket
    if (this->configure_socket(socket_timeout_sec) < 0) {
        this->close_socket();
        throw std::string("failed to configure socket.");
    }
}


int Socket::open_socket()
{
    protoent *protocol = NULL;
    if ((protocol = getprotobyname("icmp")) == NULL) {
        std::cerr << "ERROR: failed to get ICMP protocol info." << std::endl;
        return -1;
    }

    this->hsocket = socket(AF_INET, SOCK_RAW, protocol->p_proto);
    if (this->hsocket < 0) {
        std::cerr << "ERROR: " << std::strerror(errno);
        std::cerr << ". Try using 'sudo'." << std::endl;
        return -1;
    }

    return 0;
}


int Socket::configure_socket(int socket_timeout_sec)
{
    timeval timeValue = {
        .tv_sec = socket_timeout_sec,
        .tv_usec = 0,
    };
    
    // Set socket timeout
    if (setsockopt(this->hsocket, SOL_SOCKET, SO_RCVTIMEO, &timeValue, sizeof(timeValue)) < 0) {
        std::cerr << "ERROR: setsockopt error. " << std::strerror(errno) << std::endl;
        return -1;
    }

    return 0;
}


void Socket::close_socket()
{
    close(this->hsocket);
}


Socket::~Socket()
{
    this->close_socket();
}


int Socket::get_socket()
{
    return this->hsocket;
}