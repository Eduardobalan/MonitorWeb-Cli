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

    ServidorConfigDb srvConfigDbParaThread;
    std::map<long, MonitoramentoPostgres*> mapMonitoramentoPostgres;

    ThreadLerServidorConfigDb threadLerServidorConfigDb;
    threadLerServidorConfigDb.threadSincronizarConfigLocalComApi(&srvConfig, &mapMonitoramentoPostgres);


//    //############################
//    //# Informacoes  do  sistema #
//    //############################
//
//    InformacoesCpu informacoesCpu;
//    informacoesCpu.monitorarInformacoesCpu(&srvConfig);
//
//    InformacoesMemoria informacoesMemoria;
//    informacoesMemoria.monitorarInformacoesMemoria(&srvConfig);
//
//    InformacoesSwap informacoesSwap;
//    informacoesSwap.monitorarInformacoesSwap(&srvConfig);
//
//    InformacoesPostgres informacoesPostgres;
//    informacoesPostgres.monitorarInformacoesPostgres(&srvConfig);

//    //############################
//    //# Monitoramento do sistema #
//    //############################
//
//    MonitoramentoCpu monitoramentoCpu;
//    monitoramentoCpu.threadMonitorarMonitoramentoCpu(&srvConfig, &informacoesCpu, &monitoramentoCpu);
//
//    MonitoramentoMemoria monitoramentoMemoria;
//    monitoramentoMemoria.threadMonitorarMonitoramentoMemoria(&srvConfig, &informacoesMemoria, &monitoramentoMemoria);
//
//    MonitoramentoSwap monitoramentoSwap;
//    monitoramentoSwap.threadMonitorarMonitoramentoSwap(&srvConfig, &informacoesSwap, &monitoramentoSwap);
//
//
//    std::map<long, MonitoramentoPostgres*> mapMonitoramentoPostgres;
//
//    do{
//        for(std::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
//        std::cout << it->first << " => " << it->second << '\n';
//
//
//        sleep(srvConfig.getIntervaloDB());
//    }
//    while(true);



//    MonitoramentoPostgres monitoramentoPostgres1;
//    monitoramentoPostgres1.threadSincronizarConfigLocalComApi(srvConfig, ssssssssssssssssss);




//
//    MonitoramentoPostgres monitoramentoPostgres;
//    monitoramentoPostgres.lerMonitorarPostgres();

    sleep(1000000000);
}