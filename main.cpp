//
// Created by eduardo on 29/09/17.
//
#include <stdlib.h>
#include <unistd.h>
#include <boost/date_time/date.hpp>
#include <map>
#include "Util/SystemLog.h"
#include "Entity/InformacoesCpu.h"
#include "Entity/ServidorConfigDb.h"
#include "Entity/MonitoramentoPostgres.h"
#include "Entity/ThreadLerServidorConfigDb.h"
#include "Entity/InformacoesMemoria.h"
#include "Entity/InformacoesSwap.h"
#include "Entity/MonitoramentoCpu.h"
#include "Entity/MonitoramentoMemoria.h"
#include "Entity/MonitoramentoSwap.h"
#include "Entity/ThreadLerServidorConfigInformacoesDb.h"

using namespace std;

int main(int argc, char* argv[]) {

    //############################
    //### Configurações log ######
    //############################

    SystemLog::lerLogConf();


    //############################
    //# Configurações do sistema #
    //############################

    ServidorConfig srvConfig;
    srvConfig.lerConfiguracoesLocais();
    srvConfig.threadSincronizarConfigLocalComApi(&srvConfig);

    sleep(3);
//    //############################
//    //# Informacoes  do  sistema #
//    //############################

    InformacoesCpu informacoesCpu;
    informacoesCpu.monitorarInformacoesCpu(&srvConfig);

    InformacoesMemoria informacoesMemoria;
    informacoesMemoria.monitorarInformacoesMemoria(&srvConfig);

    InformacoesSwap informacoesSwap;
    informacoesSwap.monitorarInformacoesSwap(&srvConfig);

    sleep(3);
//    //############################
//    //# Monitoramento do sistema #
//    //############################

    MonitoramentoCpu monitoramentoCpu;
    monitoramentoCpu.threadMonitorarMonitoramentoCpu(&srvConfig, &informacoesCpu, &monitoramentoCpu);

    MonitoramentoMemoria monitoramentoMemoria;
    monitoramentoMemoria.threadMonitorarMonitoramentoMemoria(&srvConfig, &informacoesMemoria, &monitoramentoMemoria);

    MonitoramentoSwap monitoramentoSwap;
    monitoramentoSwap.threadMonitorarMonitoramentoSwap(&srvConfig, &informacoesSwap, &monitoramentoSwap);


    sleep(3);
//    //############################
//    //# Monitoramento do DB      #
//    //############################

    std::map<long, MonitoramentoPostgresInformacoes*> mapMonitoramentoPostgresInformacoes;
    ThreadLerServidorConfigInformacoesDb  ThreadLerServidorConfigInformacoesDb;
    ThreadLerServidorConfigInformacoesDb.threadSincronizarConfigLocalComApi(&srvConfig, &mapMonitoramentoPostgresInformacoes);

    std::map<long, MonitoramentoPostgres*> mapMonitoramentoPostgres;
    ThreadLerServidorConfigDb threadLerServidorConfigDb;
    threadLerServidorConfigDb.threadSincronizarConfigLocalComApi(&srvConfig, &mapMonitoramentoPostgres);

    do{
        sleep(1000000000);
    }while(true);
}