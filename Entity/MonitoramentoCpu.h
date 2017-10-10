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


using boost::property_tree::ptree;
using boost::property_tree::read_json;
using boost::property_tree::write_json;
using std::string;
using std::cout;

class MonitoramentoCpu {

private:
    long numeroNucleos;
    long cpuMhz;

public:
    MonitoramentoCpu();

    virtual ~MonitoramentoCpu();

    bool fromJson(const string &json);

    string toJson();

    void print();

    //======= getter end setter ======

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
};



#endif //WEBMONITOR_CLIENTE_MONITORAMENTOCPU_H
