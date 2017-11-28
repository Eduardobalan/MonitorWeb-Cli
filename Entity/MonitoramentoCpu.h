//
// Created by eduardo on 14/09/17.
//

#ifndef WEBMONITOR_CLIENTE_MONITORAMENTOCPU_H
#define WEBMONITOR_CLIENTE_MONITORAMENTOCPU_H

#include <iostream>
#include <string>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "Servidor.h"
#include "ServidorConfig.h"
#include "InformacoesCpu.h"


using boost::property_tree::ptree;
using boost::property_tree::read_json;
using boost::property_tree::write_json;
using std::string;
using std::cout;

class MonitoramentoCpu {

private:
    InformacoesCpu *informacoesCpu;
    thread *threadx;
    //variavel que representa o numero do nucleo que esta sendo monitorado no momento.
    long numeroNucleoMonitorado = 0;
    long coreId;
    long numeroNucleos;
    long cpuMhz;

public:
    MonitoramentoCpu();

    virtual ~MonitoramentoCpu();

    bool fromJson(const string &json);

    string toJson();

    void lerMonitorarCpu();

    static void monitorarMonitoramentoCpu(ServidorConfig *srvConfig, InformacoesCpu *informacoesCpu, MonitoramentoCpu *monitoramentoCpu);

    void threadMonitorarMonitoramentoCpu(ServidorConfig *srvConfig, InformacoesCpu *informacoesCpu, MonitoramentoCpu *monitoramentoCpu);

    void print();

    //======= getter end setter ======

    InformacoesCpu *getInformacoesCpu() const {
        return informacoesCpu;
    }

    void setInformacoesCpu(InformacoesCpu *informacoesCpu) {
        MonitoramentoCpu::informacoesCpu = informacoesCpu;
    }

    long getNumeroNucleos() const {
        return numeroNucleos;
    }

    void setNumeroNucleos(long numeroNucleos) {
        MonitoramentoCpu::numeroNucleos = numeroNucleos;
    }

    long getCpuMhz() const {
        return cpuMhz;
    }

    void setCpuMhz(long cpuMhz) {
        MonitoramentoCpu::cpuMhz = cpuMhz;
    }

    long getCoreId() const {
        return coreId;
    }

    void setCoreId(long coreId) {
        MonitoramentoCpu::coreId = coreId;
    }

    thread *getThreadx() const {
        return threadx;
    }

    void setThreadx(thread *threadx) {
        MonitoramentoCpu::threadx = threadx;
    }

    long getNumeroNucleoMonitorado() const {
        return numeroNucleoMonitorado;
    }

    void setNumeroNucleoMonitorado(long numeroNucleoMonitorado) {
        MonitoramentoCpu::numeroNucleoMonitorado = numeroNucleoMonitorado;
    }
};



#endif //WEBMONITOR_CLIENTE_MONITORAMENTOCPU_H
