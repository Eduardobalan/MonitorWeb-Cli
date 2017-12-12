//
// Created by eduardo on 17/10/17.
//

#ifndef WEBMONITOR_CLIENTE_MONITORAMENTODB_H
#define WEBMONITOR_CLIENTE_MONITORAMENTODB_H


#include "MonitoramentoPostgresInformacoes.h"
#include "ServidorConfigDb.h"

class MonitoramentoPostgres {
private:
    ServidorConfigDb *servidorConfigDb;
    // enum BACKUP VACUUM
    string tipoExecucao;
    int exito;
    string mensagem;
    std::thread *threadx;
    string threadId;

public:
    MonitoramentoPostgres();

    virtual ~MonitoramentoPostgres();

    void lerMonitorarPostgres(MonitoramentoPostgres *monitoramentoPostgres);

    static void monitorarMonitoramentoPostgres(ServidorConfig *srvConfig, ServidorConfigDb *SrvConfigDb, MonitoramentoPostgres *monitoramentoPostgres);

    void threadMonitorarMonitoramentoPostgres(ServidorConfig *srvConfig, ServidorConfigDb *SrvConfigDb, MonitoramentoPostgres *monitoramentoPostgres);

    string toJson();

    //Getter and Setter

    const string &getTipoExecucao() const {
        return tipoExecucao;
    }

    void setTipoExecucao(const string &tipoExecucao) {
        MonitoramentoPostgres::tipoExecucao = tipoExecucao;
    }

    int getExito() const {
        return exito;
    }

    void setExito(int exito) {
        MonitoramentoPostgres::exito = exito;
    }

    const string &getMensagem() const {
        return mensagem;
    }

    void setMensagem(const string &mensagem) {
        MonitoramentoPostgres::mensagem = mensagem;
    }

    ServidorConfigDb *getServidorConfigDb() const {
        return servidorConfigDb;
    }

    void setServidorConfigDb(ServidorConfigDb *servidorConfigDb) {
        MonitoramentoPostgres::servidorConfigDb = servidorConfigDb;
    }

    thread *getThreadx() const {
        return threadx;
    }

    void setThreadx(thread *threadx) {
        MonitoramentoPostgres::threadx = threadx;
    }

    const string &getThreadId() const {
        return threadId;
    }

    void setThreadId(const string &threadId) {
        MonitoramentoPostgres::threadId = threadId;
    }

};


#endif //WEBMONITOR_CLIENTE_MONITORAMENTODB_H
