//
// Created by eduardo on 29/09/17.
//
#include <stdlib.h>
#include <unistd.h>
#include "Util/SystemLog.h"
#include "Entity/InformacoesCpu.h"
#include "Entity/MonitoramentoCpu.h"
#include "Entity/InformacoesMemoria.h"
#include "Entity/MonitoramentoMemoria.h"
#include "Entity/InformacoesSwap.h"
#include "Entity/MonitoramentoSwap.h"

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

    InformacoesMemoria informacoesMemoria;
    informacoesMemoria.monitorarInformacoesMemoria(&srvConfig);

    InformacoesSwap informacoesSwap;
    informacoesSwap.monitorarInformacoesSwap(&srvConfig);

    //############################
    //# Monitoramento do sistema #
    //############################

    MonitoramentoCpu monitoramentoCpu;
    monitoramentoCpu.threadMonitorarMonitoramentoCpu(&srvConfig, &informacoesCpu, &monitoramentoCpu);

    MonitoramentoMemoria monitoramentoMemoria;
    monitoramentoMemoria.threadMonitorarMonitoramentoMemoria(&srvConfig, &informacoesMemoria, &monitoramentoMemoria);

    MonitoramentoSwap monitoramentoSwap;
    monitoramentoSwap.threadMonitorarMonitoramentoSwap(&srvConfig, &informacoesSwap, &monitoramentoSwap);

    sleep(1000000000);
}