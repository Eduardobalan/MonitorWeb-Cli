//
// Created by eduardo on 17/10/17.
//

#ifndef WEBMONITOR_CLIENTE_MONITORAMENTOMEMORIA_H
#define WEBMONITOR_CLIENTE_MONITORAMENTOMEMORIA_H


#include "InformacoesMemoria.h"

class MonitoramentoMemoria {
private:
    thread *threadx;
    InformacoesMemoria *informacoesMemoria;
    long active;
    long memfree;
    long availabre;
    long buffers;
public:
    MonitoramentoMemoria();

    virtual ~MonitoramentoMemoria();

    bool fromJson(const string &json);

    string toJson();

    void lerMonitorarMemoria();

    static void monitorarMonitoramentoMemoria(ServidorConfig *srvConfig, InformacoesMemoria *informacoesMemoria, MonitoramentoMemoria *monitoramentoMemoria);

    void threadMonitorarMonitoramentoMemoria(ServidorConfig *srvConfig, InformacoesMemoria *informacoesMemoria, MonitoramentoMemoria *monitoramentoMemoria);


    //getter and setter

    InformacoesMemoria *getInformacoesMemoria() const {
        return informacoesMemoria;
    }

    void setInformacoesMemoria(InformacoesMemoria *informacoesMemoria) {
        MonitoramentoMemoria::informacoesMemoria = informacoesMemoria;
    }

    long getActive() const {
        return active;
    }

    void setActive(long active) {
        MonitoramentoMemoria::active = active;
    }

    long getMemfree() const {
        return memfree;
    }

    void setMemfree(long memfree) {
        MonitoramentoMemoria::memfree = memfree;
    }

    long getAvailabre() const {
        return availabre;
    }

    void setAvailabre(long availabre) {
        MonitoramentoMemoria::availabre = availabre;
    }

    long getBuffers() const {
        return buffers;
    }

    void setBuffers(long buffers) {
        MonitoramentoMemoria::buffers = buffers;
    }

    thread *getThreadx() const {
        return threadx;
    }

    void setThreadx(thread *threadx) {
        MonitoramentoMemoria::threadx = threadx;
    }
};


#endif //WEBMONITOR_CLIENTE_MONITORAMENTOMEMORIA_H
