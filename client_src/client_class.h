#ifndef CLIENT_CLASS_H
#define CLIENT_CLASS_H

class Client {
public:
    Client(const char* port, const char* host);
    void run();
private:
    const char* port;
    const char* host;
};

#endif  //CLIENT_CLASS_H
