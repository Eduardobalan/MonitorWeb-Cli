//
// Created by eduardo on 05/10/17.
//

#include <string>
#include "Result.h"

#ifndef WEBMONITOR_CLIENTE_GET_H
#define WEBMONITOR_CLIENTE_GET_H

using std::string;

class Get {

private:
    string host;
    unsigned short port;
    string path;

public:

    Get(const string &path, const string &host, unsigned short port);

    virtual ~Get();

    Result* exec();

    bool validate();


    // ============ Getter and Setter ======

    const string &getHost() const {
        return host;
    }

    void setHost(const string &host) {
        Get::host = host;
    }

    unsigned short getPort() const {
        return port;
    }

    void setPort(unsigned short port) {
        Get::port = port;
    }

    const string &getPath() const {
        return path;
    }

    void setPath(const string &path) {
        Get::path = path;
    }

};


#endif //WEBMONITOR_CLIENTE_GET_H
