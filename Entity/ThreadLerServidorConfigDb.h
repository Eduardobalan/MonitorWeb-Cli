//
// Created by eduardo on 09/11/17.
//

#ifndef WEBMONITOR_CLIENTE_THREADLERSERVIDORCONFIGDB_H
#define WEBMONITOR_CLIENTE_THREADLERSERVIDORCONFIGDB_H


#include "ServidorConfig.h"
#include "MonitoramentoPostgres.h"

class ThreadLerServidorConfigDb {

private:
    thread *threadx;
public:

    ThreadLerServidorConfigDb();

    virtual ~ThreadLerServidorConfigDb();

    void lerConfiguracoesLocais();

    void salvarConfiguracoesLocais();

    static bool fromJson(const string &json, ServidorConfig *srvConfig, std::map<long, MonitoramentoPostgres*>  *mapMonitoramentoPostgres);

    static void sincronizarConfigLocalComApi(ServidorConfig *srvConfig, std::map<long, MonitoramentoPostgres*>  *mapMonitoramentoPostgres);

    void threadSincronizarConfigLocalComApi(ServidorConfig *srvConfig, std::map<long, MonitoramentoPostgres*>  *mapMonitoramentoPostgres);

    thread *getThreadx() const {
        return threadx;
    }

    void setThreadx(thread *threadx) {
        ThreadLerServidorConfigDb::threadx = threadx;
    }
};


#endif //WEBMONITOR_CLIENTE_THREADLERSERVIDORCONFIGDB_H
