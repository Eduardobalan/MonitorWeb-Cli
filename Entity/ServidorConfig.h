//
// Created by eduardo on 09/10/17.
//
#include <iostream>
#include <string>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "Servidor.h"
#include <thread>

#ifndef WEBMONITOR_CLIENTE_SERVIDORCONFIG_H
#define WEBMONITOR_CLIENTE_SERVIDORCONFIG_H

using boost::property_tree::ptree;
using boost::property_tree::read_json;
using boost::property_tree::write_json;
using std::string;
using std::cout;
using std::thread;

using namespace std;

class ServidorConfig {
private:
    long id;
    Servidor servidor;
    thread *threadx;
    bool ficarMonitorando = true;
    long intervaloLeituraConfiguracoes;
    long intervaloLeituraConfiguracoesDb;
    long intervaloCpu;
    long intervaloMemoria;
    long intervaloSwap;
    string hostMonitoramento;
    string hostMonitoramento2;
    long porta;
    long porta2;

public:
    ServidorConfig();

    virtual ~ServidorConfig();

    void lerConfiguracoesLocais();

    void salvarConfiguracoesLocais();

    bool fromJson(const string &json);

    static void sincronizarConfigLocalComApi(ServidorConfig *servidorConfig);

    void threadSincronizarConfigLocalComApi(ServidorConfig *servidorConfig);

    string toJson();

    void print();

    //======= getter end setter ======

    long getId() const {
        return id;
    }

    void setId(long id) {
        ServidorConfig::id = id;
    }

    const Servidor &getServidor() const {
        return servidor;
    }

    void setServidor(const Servidor &servidor) {
        ServidorConfig::servidor = servidor;
    }

    long getIntervaloCpu() const {
        return intervaloCpu;
    }

    void setIntervaloCpu(long intervaloCpu) {
        ServidorConfig::intervaloCpu = intervaloCpu;
    }

    long getIntervaloMemoria() const {
        return intervaloMemoria;
    }

    void setIntervaloMemoria(long intervaloMemoria) {
        ServidorConfig::intervaloMemoria = intervaloMemoria;
    }

    long getIntervaloSwap() const {
        return intervaloSwap;
    }

    void setIntervaloSwap(long intervaloSwap) {
        ServidorConfig::intervaloSwap = intervaloSwap;
    }

    const string &getHostMonitoramento() const {
        return hostMonitoramento;
    }

    void setHostMonitoramento(const string &hostMonitoramento) {
        ServidorConfig::hostMonitoramento = hostMonitoramento;
    }

    const string &getHostMonitoramento2() const {
        return hostMonitoramento2;
    }

    void setHostMonitoramento2(const string &hostMonitoramento2) {
        ServidorConfig::hostMonitoramento2 = hostMonitoramento2;
    }

    long getIntervaloLeituraConfiguracoes() const {
        return intervaloLeituraConfiguracoes;
    }

    void setIntervaloLeituraConfiguracoes(long intervaloLeituraConfiguracoes) {
        ServidorConfig::intervaloLeituraConfiguracoes = intervaloLeituraConfiguracoes;
    }

    long getIntervaloLeituraConfiguracoesDb() const {
        return intervaloLeituraConfiguracoesDb;
    }

    void setIntervaloLeituraConfiguracoesDb(long intervaloLeituraConfiguracoesDb) {
        ServidorConfig::intervaloLeituraConfiguracoesDb = intervaloLeituraConfiguracoesDb;
    }

    long getPorta() const {
        return porta;
    }

    void setPorta(long porta) {
        ServidorConfig::porta = porta;
    }

    long getPorta2() const {
        return porta2;
    }

    void setPorta2(long porta2) {
        ServidorConfig::porta2 = porta2;
    }

    thread *getThreadx() const {
        return threadx;
    }

    void setThreadx(thread *threadx) {
        ServidorConfig::threadx = threadx;
    }

    bool isFicarMonitorando() const {
        return ficarMonitorando;
    }

    void setFicarMonitorando(bool ficarMonitorando) {
        ServidorConfig::ficarMonitorando = ficarMonitorando;
    }
};


#endif //WEBMONITOR_CLIENTE_SERVIDORCONFIG_H
