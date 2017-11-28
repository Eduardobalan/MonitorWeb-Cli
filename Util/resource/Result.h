//
// Created by eduardo on 05/10/17.
//

#include <string>

#ifndef WEBMONITOR_CLIENTE_RESULT_H
#define WEBMONITOR_CLIENTE_RESULT_H

using std::string;

class Result {

private:
    unsigned short status;
    string verbo;
    string result;
    string error;
    string host;
    unsigned short port;
    string path;
    string json;

public:
    Result(unsigned short status, const string &result, const string &error,const string &verbo, const string &path, const string &host, unsigned short port, const string json);

    void imprimir(const string &origem);

    virtual ~Result();

    unsigned short getStatus() const {
        return status;
    }

    void setStatus(unsigned short status) {
        Result::status = status;
    }

    const string &getResult() const {
        return result;
    }

    void setResult(const string &result) {
        Result::result = result;
    }

    const string &getError() const {
        return error;
    }

    void setError(const string &error) {
        Result::error = error;
    }

    const string &getHost() const {
        return host;
    }

    void setHost(const string &host) {
        Result::host = host;
    }

    unsigned short getPort() const {
        return port;
    }

    void setPort(unsigned short port) {
        Result::port = port;
    }

    const string &getPath() const {
        return path;
    }

    void setPath(const string &path) {
        Result::path = path;
    }

    const string &getjson() const {
        return json;
    }

    void setjson(const string &json) {
        Result::json = json;
    }

    const string &getVerbo() const {
        return verbo;
    }

    void setVerbo(const string &verbo) {
        Result::verbo = verbo;
    }

    const string &getJson() const {
        return json;
    }

    void setJson(const string &json) {
        Result::json = json;
    }
};


#endif //WEBMONITOR_CLIENTE_RESULT_H
