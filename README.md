# Arduino-Style POSIX TCP Client

Arduino's [`EthernetClient`](https://www.arduino.cc/en/Reference/EthernetClient)/[`WiFiClient`](https://www.arduino.cc/en/Reference/WiFiClient) classes and Particle's [`TCPClient`](https://docs.particle.io/reference/firmware/#tcpclient) class make it easy to make network requests from your embedded apps, but in [POSIX](https://en.wikipedia.org/wiki/POSIX) environments (Linux, BSD, Mac) networking can be a little more complicated.

This library provides a `TCPClient` class, which allows you to make TCP requests in a super simple way.

## Usage

```c++
// Create a TCP client
TCPClient client;

// Connect to the following address and port
client.connect("httpbin.org", 80);

// Make sure we're connected
if(client.connected()) {
    // Make a HTTP GET request
    client.println("GET /get HTTP/1.0");
    client.println();

    // Read the response and print it
    while(client.available()) {
        printf("%c", client.read());
    }
}

// Close the connection
client.stop();
```
