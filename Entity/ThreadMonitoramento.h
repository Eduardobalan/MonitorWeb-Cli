//
// Created by eduardo on 11/10/17.
//

#ifndef WEBMONITOR_CLIENTE_THREADMONITORAMENTO_H
#define WEBMONITOR_CLIENTE_THREADMONITORAMENTO_H


#include "ServidorConfig.h"

class ThreadMonitoramento {
private:
public:
    ThreadMonitoramento();

    virtual ~ThreadMonitoramento();

    static void monitorarInformacoesCpu();

    void threadinformacoesCpu();


};


#endif //WEBMONITOR_CLIENTE_THREADMONITORAMENTO_H
