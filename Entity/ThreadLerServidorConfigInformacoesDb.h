//
// Created by eduardo on 13/11/17.
//

#ifndef WEBMONITOR_CLIENTE_THREADLERSERVIDORCONFIGINFORMACOESDB_H
#define WEBMONITOR_CLIENTE_THREADLERSERVIDORCONFIGINFORMACOESDB_H


#include <map>
#include "ServidorConfig.h"
#include "MonitoramentoPostgresInformacoes.h"

class ThreadLerServidorConfigInformacoesDb {
private:
    thread *threadx;
public:
    ThreadLerServidorConfigInformacoesDb();

    virtual ~ThreadLerServidorConfigInformacoesDb();

    void lerConfiguracoesLocais();

    void salvarConfiguracoesLocais();

    static bool fromJson(const string &json, ServidorConfig *srvConfig, std::map<long, MonitoramentoPostgresInformacoes*>  *mapMonitoramentoPostgresInformacoes);

    static void sincronizarConfigLocalComApi(ServidorConfig *srvConfig, std::map<long, MonitoramentoPostgresInformacoes*>  *mapMonitoramentoPostgresInformacoes);

    void threadSincronizarConfigLocalComApi(ServidorConfig *srvConfig, std::map<long, MonitoramentoPostgresInformacoes*> *mapMonitoramentoPostgresInformacoes);

    thread *getThreadx() const {
        return threadx;
    }

    void setThreadx(thread *threadx) {
        ThreadLerServidorConfigInformacoesDb::threadx = threadx;
    }
};


#endif //WEBMONITOR_CLIENTE_THREADLERSERVIDORCONFIGINFORMACOESDB_H
