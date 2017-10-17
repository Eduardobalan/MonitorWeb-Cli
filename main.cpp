//
// Created by eduardo on 29/09/17.
//
#include <stdlib.h>
#include <unistd.h>
#include "Util/SystemLog.h"
#include "Entity/InformacoesCpu.h"
#include "Entity/MonitoramentoCpu.h"

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

    //############################
    //# Informacoes  do  sistema #
    //############################

    InformacoesCpu informacoesCpu;
    informacoesCpu.monitorarInformacoesCpu(&srvConfig);

    //############################
    //# Monitoramento do sistema #
    //############################

    MonitoramentoCpu monitoramentoCpu;
    monitoramentoCpu.threadMonitorarMonitoramentoCpu(&srvConfig, &informacoesCpu, &monitoramentoCpu);


    sleep(1000000000);
}