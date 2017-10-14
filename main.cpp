//
// Created by eduardo on 29/09/17.
//
#include <stdlib.h>
#include <unistd.h>
#include "Util/SystemLog.h"
#include "Entity/InformacoesCpu.h"

using namespace std;

int main(int argc, char* argv[]) {

    SystemLog::setAtivarLog(true);
    SystemLog::setAtivarLogArquivo(true);

    ServidorConfig srvConfig;
    srvConfig.lerConfiguracoesLocais();
    srvConfig.threadSincronizarConfigLocalComApi(&srvConfig);

    InformacoesCpu informacoesCpu;
    informacoesCpu.monitorarInformacoesCpu(&srvConfig);






//    Get getServidorConfig("/servidor/1/servidorconfiguracoes/1","172.23.64.255",8081);
//    Result *resultServidorConfig;
//    do{
//        cout << "Tread 2 <<<<<-------------------------" << endl;
//        resultServidorConfig = getServidorConfig.exec();
//        if(resultServidorConfig->getStatus() == 200){
//            servidorConfig.fromJson(resultServidorConfig->getResult());
//        }else{
//            cout << "Erro ao conectar " << endl;
//        }
//    }
//    while(resultServidorConfig->getStatus() != 500);
//
//    servidorConfig.print();


    //#########################################################################
    //#################### Inicializa Informações Cpu #########################
    //#########################################################################


//    ThreadMonitoramento threadMonitoramento;
//    threadMonitoramento.threadinformacoesCpu();

//    void InformacoesCpu::threadStartMonitorar(){
//        //
//        cerr << " Thread InformacoesCpu parou de rodar." << endl;
//    }


//    std::thread threadx(x);
    usleep(1000000000); //wait so that hello can be printed.
//    while(true) {
//
//    }

}