//
// Created by eduardo on 17/10/17.
//

#ifndef WEBMONITOR_CLIENTE_MONITORAMENTODB_H
#define WEBMONITOR_CLIENTE_MONITORAMENTODB_H


#include "InformacoesPostgres.h"
#include "ServidorConfigDb.h"

class MonitoramentoPostgres {
private:
    ServidorConfigDb *servidorConfigDb;
    // enum BACKUP VACUUM
    string tipoExecucao;
    int exito;
    string mensagem;
    std::thread *thread;
    string threadId;

public:
    MonitoramentoPostgres();

    virtual ~MonitoramentoPostgres();

    void lerMonitorarPostgres(MonitoramentoPostgres *monitoramentoPostgres);

    static void sincronizarConfigLocalComApi(ServidorConfig *srvConfig, ServidorConfigDb *SrvConfigDb, MonitoramentoPostgres *monitoramentoPostgres);

    void threadSincronizarConfigLocalComApi(ServidorConfig *srvConfig, ServidorConfigDb *SrvConfigDb, MonitoramentoPostgres *monitoramentoPostgres);

    string toJson();


//    static bool fromJson(const string &json, ServidorConfigDb *srvConfigDb);
//
//    static void monitorarMonitoramentoPostgres(ServidorConfig *srvConfig, servidorConfigDb *informacoesMemoria, MonitoramentoMemoria *monitoramentoMemoria);
//
//    void threadMonitorarMonitoramentoPostgres(ServidorConfig *srvConfig, servidorConfigDb *informacoesMemoria, MonitoramentoMemoria *monitoramentoMemoria);


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
};


#endif //WEBMONITOR_CLIENTE_MONITORAMENTODB_H
