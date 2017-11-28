//
// Created by eduardo on 17/10/17.
//

#ifndef WEBMONITOR_CLIENTE_MONITORAMENTOSWAP_H
#define WEBMONITOR_CLIENTE_MONITORAMENTOSWAP_H


#include "InformacoesSwap.h"

class MonitoramentoSwap {
private:
    thread *threadx;
    InformacoesSwap *informacoesSwap;
    long free;
    long cached;
public:

    MonitoramentoSwap();

    virtual ~MonitoramentoSwap();

    bool fromJson(const string &json);

    string toJson();

    void lerMonitorarSwap();

    static void monitorarMonitoramentoSwap(ServidorConfig *srvConfig, InformacoesSwap *informacoesSwap, MonitoramentoSwap *monitoramentoSwap);

    void threadMonitorarMonitoramentoSwap(ServidorConfig *srvConfig, InformacoesSwap *informacoesSwap, MonitoramentoSwap *monitoramentoSwap);


    //getter and setter
    InformacoesSwap *getInformacoesSwap() const {
        return informacoesSwap;
    }

    void setInformacoesSwap(InformacoesSwap *informacoesSwap) {
        MonitoramentoSwap::informacoesSwap = informacoesSwap;
    }

    long getFree() const {
        return free;
    }

    void setFree(long free) {
        MonitoramentoSwap::free = free;
    }

    long getCached() const {
        return cached;
    }

    void setCached(long cached) {
        MonitoramentoSwap::cached = cached;
    }

    thread *getThreadx() const {
        return threadx;
    }

    void setThreadx(thread *threadx) {
        MonitoramentoSwap::threadx = threadx;
    }
};


#endif //WEBMONITOR_CLIENTE_MONITORAMENTOSWAP_H
