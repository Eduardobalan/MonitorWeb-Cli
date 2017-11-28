//
// Created by eduardo on 18/11/17.
//

#ifndef WEBMONITOR_CLIENTE_RESOURCE_H
#define WEBMONITOR_CLIENTE_RESOURCE_H

#include <string>
#include "Result.h"

using std::string;

class Resource {
private:
    string host;
    unsigned short port;
    string path;
    Result* exec(const string &json, const string &verbo);
    bool validarResource(const string &verbo);
public:

    Resource(const string &path, const string &host, unsigned short port);

    virtual ~Resource() {

    }

    Result* get();

    Result* post(const string &json);

    //====== Getter end Setter
    const string &getHost() const {
        return host;
    }

    void setHost(const string &host) {
        Resource::host = host;
    }

    unsigned short getPort() const {
        return port;
    }

    void setPort(unsigned short port) {
        Resource::port = port;
    }

    const string &getPath() const {
        return path;
    }

    void setPath(const string &path) {
        Resource::path = path;
    }
};


#endif //WEBMONITOR_CLIENTE_RESOURCE_H
