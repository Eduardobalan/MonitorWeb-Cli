//
// Created by eduardo on 09/10/17.
//
#include <iostream>
#include <string>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "Servidor.h"

#ifndef WEBMONITOR_CLIENTE_SERVIDORCONFIG_H
#define WEBMONITOR_CLIENTE_SERVIDORCONFIG_H

using boost::property_tree::ptree;
using boost::property_tree::read_json;
using boost::property_tree::write_json;
using std::string;
using std::cout;

using namespace std;

class ServidorConfig {
private:
    long id;
    Servidor servidor;
    long intervaloLeituraConfiguracoes;
    long intervaloCpu;
    long intervaloMemoria;
    long intervaloSwap;
    long intervaloDB;
    string hostMonitoramento;
    string hostMonitoramento2;
    long porta;
    long porta2;
    string postgresPathMain;
    string postgresVersao;

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

    long getIntervaloDB() const {
        return intervaloDB;
    }

    void setIntervaloDB(long intervaloDB) {
        ServidorConfig::intervaloDB = intervaloDB;
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

    const string &getPostgresPathMain() const {
        return postgresPathMain;
    }

    void setPostgresPathMain(const string &postgresPathMain) {
        ServidorConfig::postgresPathMain = postgresPathMain;
    }

    const string &getPostgresVersao() const {
        return postgresVersao;
    }

    void setPostgresVersao(const string &postgresVersao) {
        ServidorConfig::postgresVersao = postgresVersao;
    }
};


#endif //WEBMONITOR_CLIENTE_SERVIDORCONFIG_H
