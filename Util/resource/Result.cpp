//
// Created by eduardo on 05/10/17.
//

#include "Result.h"
#include "../SystemLog.h"

Result::Result(unsigned short status, const string &result, const string &error, const string &verbo, const string &path, const string &host = "127.0.0.1", unsigned short port = 80, const string json = "") : status(status), result(result), error(error), verbo(verbo), host(host), port(port), path(path), json(json) {
    setHost(host);
    setPort(port);
    setPath(path);
    setStatus(status);
    setResult(result);
    setError(error);
    setVerbo(verbo);
    setjson(json);
}

void Result::imprimir(const string &origem = ""){
    if(getStatus() == 200){
        SystemLog::execLog('l',origem+": "+ getVerbo() +" - Status 200 "+ getHost()+":"+ to_string(getPort())+ getPath());
    }else{
        SystemLog::execLog('e',origem+":"+ getVerbo() +" - "+ getHost()+":"+ to_string(getPort())+ getPath());
        SystemLog::execLog('e',origem+": Status: "+to_string(getStatus()));
        SystemLog::execLog('e',origem+": Resulta: "+getResult());
        SystemLog::execLog('e',origem+": Error: "+getError());
        SystemLog::execLog('e',origem+": json: "+getjson());
    }
};

Result::~Result() {

}
