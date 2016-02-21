#include <stdio.h>
#include "TCPClient.h"

int main() {
    TCPClient client;
    client.connect("httpbin.org", 80);

    if(client.connected()) {
        client.println("GET /get HTTP/1.0");
        client.println();

        while(client.available()) {
            printf("%c", client.read());
        }
    }

    client.stop();

    return 0;
}
