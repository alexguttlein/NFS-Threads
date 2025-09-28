#ifndef SERVER_CLASS_H
#define SERVER_CLASS_H

class Server {
public:
    Server(const char* port);
    void run();
private:
    const char* port;
};

#endif  //SERVER_CLASS_H
