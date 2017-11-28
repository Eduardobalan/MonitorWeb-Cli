//
// Created by eduardo on 17/10/17.
//

#ifndef WEBMONITOR_CLIENTE_INFORMACOESDB_H
#define WEBMONITOR_CLIENTE_INFORMACOESDB_H


#include <thread>
#include "Servidor.h"
#include "ServidorConfig.h"
#include "ServidorConfigInformacoesDb.h"

class MonitoramentoPostgresInformacoes {
private:
    long Id;
    ServidorConfigInformacoesDb *servidorConfigInformacoesDb;
    std::thread *threadx;
    string threadId;
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

    MonitoramentoPostgresInformacoes();

    virtual ~MonitoramentoPostgresInformacoes();

    void lerMonitoramentoPostgresInformacoes(ServidorConfigInformacoesDb *srvConfig);

    void threadSincronizarConfigLocalComApi(ServidorConfig *srvConfig, ServidorConfigInformacoesDb *servidorConfigInformacoesDb, MonitoramentoPostgresInformacoes *monitoramentoPostgresInformacoes);

    static void sincronizarConfigLocalComApi(ServidorConfig *srvConfig, ServidorConfigInformacoesDb *servidorConfigInformacoesDb, MonitoramentoPostgresInformacoes *monitoramentoPostgresInformacoes);

    bool fromJson(const string &json);

    string toJson();

    //getter and setter
    long getId() const {
        return Id;
    }

    void setId(long Id) {
        MonitoramentoPostgresInformacoes::Id = Id;
    }

    ServidorConfigInformacoesDb *getServidorConfigInformacoesDb() const {
        return servidorConfigInformacoesDb;
    }

    void setServidorConfigInformacoesDb(ServidorConfigInformacoesDb *servidorConfigInformacoesDb) {
        MonitoramentoPostgresInformacoes::servidorConfigInformacoesDb = servidorConfigInformacoesDb;
    }

    const string &getListenAddresses() const {
        return listenAddresses;
    }

    void setListenAddresses(const string &listenAddresses) {
        MonitoramentoPostgresInformacoes::listenAddresses = listenAddresses;
    }

    const string &getPort() const {
        return port;
    }

    void setPort(const string &port) {
        MonitoramentoPostgresInformacoes::port = port;
    }

    const string &getMaxConnections() const {
        return maxConnections;
    }

    void setMaxConnections(const string &maxConnections) {
        MonitoramentoPostgresInformacoes::maxConnections = maxConnections;
    }

    const string &getSsl() const {
        return ssl;
    }

    void setSsl(const string &ssl) {
        MonitoramentoPostgresInformacoes::ssl = ssl;
    }

    const string &getSharedBuffers() const {
        return sharedBuffers;
    }

    void setSharedBuffers(const string &sharedBuffers) {
        MonitoramentoPostgresInformacoes::sharedBuffers = sharedBuffers;
    }

    const string &getTempBuffers() const {
        return tempBuffers;
    }

    void setTempBuffers(const string &tempBuffers) {
        MonitoramentoPostgresInformacoes::tempBuffers = tempBuffers;
    }

    const string &getWorkMem() const {
        return workMem;
    }

    void setWorkMem(const string &workMem) {
        MonitoramentoPostgresInformacoes::workMem = workMem;
    }

    const string &getMaintenanceWorkMem() const {
        return maintenanceWorkMem;
    }

    void setMaintenanceWorkMem(const string &maintenanceWorkMem) {
        MonitoramentoPostgresInformacoes::maintenanceWorkMem = maintenanceWorkMem;
    }

    const string &getReplacementWortTuples() const {
        return replacementWortTuples;
    }

    void setReplacementWortTuples(const string &replacementWortTuples) {
        MonitoramentoPostgresInformacoes::replacementWortTuples = replacementWortTuples;
    }

    const string &getMaxStackDepth() const {
        return maxStackDepth;
    }

    void setMaxStackDepth(const string &maxStackDepth) {
        MonitoramentoPostgresInformacoes::maxStackDepth = maxStackDepth;
    }

    const string &getMaxPreparedTransactions() const {
        return maxPreparedTransactions;
    }

    void setMaxPreparedTransactions(const string &maxPreparedTransactions) {
        MonitoramentoPostgresInformacoes::maxPreparedTransactions = maxPreparedTransactions;
    }

    thread *getThreadx() const {
        return threadx;
    }

    void setThreadx(thread *threadx) {
        MonitoramentoPostgresInformacoes::threadx = threadx;
    }

    const string &getThreadId() const {
        return threadId;
    }

    void setThreadId(const string &threadId) {
        MonitoramentoPostgresInformacoes::threadId = threadId;
    }
};


#endif //WEBMONITOR_CLIENTE_INFORMACOESDB_H
