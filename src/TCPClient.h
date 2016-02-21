#include <stdint.h>

class TCPClient {
public:
    TCPClient();
    bool connected();
    bool connect(const char* domain, uint16_t port);
    size_t write(uint8_t b);
    size_t write(const char* str, size_t len);
    size_t print(const char* str);
    size_t println();
    size_t println(const char* str);
    int available();
    int read();
    void flush();
    void stop();

protected:
    int sockfd;
};
