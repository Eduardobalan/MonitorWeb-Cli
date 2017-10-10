//
// Created by eduardo on 10/10/17.
//

#ifndef WEBMONITOR_CLIENTE_POST_H
#define WEBMONITOR_CLIENTE_POST_H

#include <string>
#include "Result.h"

using std::string;

class Post {
private:
    string host;
    unsigned short port;
    string path;
public:

    Post(const string &path, const string &host, unsigned short port);

    virtual ~Post() {

    }

    bool validate();

    Result* exec(const string &json);

    //====== Getter end Setter
    const string &getHost() const {
        return host;
    }

    void setHost(const string &host) {
        Post::host = host;
    }

    unsigned short getPort() const {
        return port;
    }

    void setPort(unsigned short port) {
        Post::port = port;
    }

    const string &getPath() const {
        return path;
    }

    void setPath(const string &path) {
        Post::path = path;
    }
};


#endif //WEBMONITOR_CLIENTE_POST_H
