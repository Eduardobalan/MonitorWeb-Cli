//
// Created by eduardo on 05/10/17.
//

#include "Result.h"

Result::Result(unsigned short status, const string &result, const string &error) : status(status), result(result), error(error) {

    setStatus(status);
    setResult(result);
    setError(error);
}

Result::~Result() {

}
