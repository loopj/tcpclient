#include <sys/ioctl.h>
#include <netdb.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>

#include "TCPClient.h"

TCPClient::TCPClient() : sockfd(-1) { }

bool TCPClient::connected() {
    return sockfd >= 0;
}

bool TCPClient::connect(const char* domain, uint16_t port) {
    struct addrinfo hints;
    struct addrinfo *res;

    // Specify TCP stream socket (don't mind if ipv4 or ipv6)
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    // Specify host and port
    char portString[5];
    sprintf(portString, "%d", port);
    getaddrinfo(domain, portString, &hints, &res);

    // Create the socket
    if((sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol)) < 0) {
        return false;
    }

    // Connect the socket
    if(::connect(sockfd, res->ai_addr, res->ai_addrlen) < 0) {
        return false;
    }

    // Cleanup
    freeaddrinfo(res);

    return true;
}

size_t TCPClient::write(uint8_t b) {
    return write((char *)&b, 1);
}

size_t TCPClient::write(const char* str, size_t len) {
    return ::send(sockfd, str, len, 0);
}

size_t TCPClient::print(const char* str) {
    return write(str, strlen(str));
}

size_t TCPClient::println() {
    return print("\n");
}

size_t TCPClient::println(const char* str) {
    size_t bytes = 0;
    bytes += print(str);
    bytes += print("\n");

    return bytes;
}

int TCPClient::available() {
    uint8_t buf;
    ::recv(sockfd, &buf, 1, MSG_PEEK);

    return buf > 0;
}

int TCPClient::read() {
    uint8_t buf;
    ::recv(sockfd, &buf, 1, 0);
    return buf;
}

void TCPClient::flush() {
    while(available()) read();
}

void TCPClient::stop() {
    if (sockfd != -1) {
        while (close(sockfd) < 0) {
            usleep(10000);
        }
        sockfd = -1;
    }
}
