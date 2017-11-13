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
public:
    void lerConfiguracoesLocais();

    void salvarConfiguracoesLocais();

    static bool fromJson(const string &json, ServidorConfig *srvConfig, std::map<long, MonitoramentoPostgresInformacoes*>  *mapMonitoramentoPostgresInformacoes);

    static void sincronizarConfigLocalComApi(ServidorConfig *srvConfig, std::map<long, MonitoramentoPostgresInformacoes*>  *mapMonitoramentoPostgresInformacoes);

    void threadSincronizarConfigLocalComApi(ServidorConfig *srvConfig, std::map<long, MonitoramentoPostgresInformacoes*> *mapMonitoramentoPostgresInformacoes);
};


#endif //WEBMONITOR_CLIENTE_THREADLERSERVIDORCONFIGINFORMACOESDB_H
