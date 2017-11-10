//
// Created by eduardo on 17/10/17.
//

#ifndef WEBMONITOR_CLIENTE_INFORMACOESDB_H
#define WEBMONITOR_CLIENTE_INFORMACOESDB_H


#include "Servidor.h"
#include "ServidorConfig.h"

class InformacoesPostgres {
private:
    long Id;
    Servidor servidor;
    string listenAddresses;
    string port;
    string maxConnections;
    string ssl;
    string sharedBuffers;
    string tempBuffers;
    string workMem;
    string maintenanceWorkMem;
    string replacementWortTuples;
    string maxStackDepth;
    string maxPreparedTransactions;


public:

    InformacoesPostgres();

    virtual ~InformacoesPostgres();

    void lerInformacoesPostgres(ServidorConfig *srvConfig);

    void monitorarInformacoesPostgres(ServidorConfig *srvConfig);

    bool fromJson(const string &json);

    string toJson();

    //getter and setter
    long getId() const {
        return Id;
    }

    void setId(long Id) {
        InformacoesPostgres::Id = Id;
    }

    const Servidor &getServidor() const {
        return servidor;
    }

    void setServidor(const Servidor &servidor) {
        InformacoesPostgres::servidor = servidor;
    }

    const string &getListenAddresses() const {
        return listenAddresses;
    }

    void setListenAddresses(const string &listenAddresses) {
        InformacoesPostgres::listenAddresses = listenAddresses;
    }

    const string &getPort() const {
        return port;
    }

    void setPort(const string &port) {
        InformacoesPostgres::port = port;
    }

    const string &getMaxConnections() const {
        return maxConnections;
    }

    void setMaxConnections(const string &maxConnections) {
        InformacoesPostgres::maxConnections = maxConnections;
    }

    const string &getSsl() const {
        return ssl;
    }

    void setSsl(const string &ssl) {
        InformacoesPostgres::ssl = ssl;
    }

    const string &getSharedBuffers() const {
        return sharedBuffers;
    }

    void setSharedBuffers(const string &sharedBuffers) {
        InformacoesPostgres::sharedBuffers = sharedBuffers;
    }

    const string &getTempBuffers() const {
        return tempBuffers;
    }

    void setTempBuffers(const string &tempBuffers) {
        InformacoesPostgres::tempBuffers = tempBuffers;
    }

    const string &getWorkMem() const {
        return workMem;
    }

    void setWorkMem(const string &workMem) {
        InformacoesPostgres::workMem = workMem;
    }

    const string &getMaintenanceWorkMem() const {
        return maintenanceWorkMem;
    }

    void setMaintenanceWorkMem(const string &maintenanceWorkMem) {
        InformacoesPostgres::maintenanceWorkMem = maintenanceWorkMem;
    }

    const string &getReplacementWortTuples() const {
        return replacementWortTuples;
    }

    void setReplacementWortTuples(const string &replacementWortTuples) {
        InformacoesPostgres::replacementWortTuples = replacementWortTuples;
    }

    const string &getMaxStackDepth() const {
        return maxStackDepth;
    }

    void setMaxStackDepth(const string &maxStackDepth) {
        InformacoesPostgres::maxStackDepth = maxStackDepth;
    }

    const string &getMaxPreparedTransactions() const {
        return maxPreparedTransactions;
    }

    void setMaxPreparedTransactions(const string &maxPreparedTransactions) {
        InformacoesPostgres::maxPreparedTransactions = maxPreparedTransactions;
    }
};


#endif //WEBMONITOR_CLIENTE_INFORMACOESDB_H
