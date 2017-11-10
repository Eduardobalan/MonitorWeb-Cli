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
    string result;
    string error;

public:
    Result(unsigned short status, const string &result, const string &error);

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
};


#endif //WEBMONITOR_CLIENTE_RESULT_H
