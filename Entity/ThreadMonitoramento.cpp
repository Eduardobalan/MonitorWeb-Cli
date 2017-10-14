//
// Created by eduardo on 11/10/17.
//

#include "ThreadMonitoramento.h"
#include "InformacoesCpu.h"
#include "../Util/verbosHttp/Get.h"


ThreadMonitoramento::ThreadMonitoramento() {}

ThreadMonitoramento::~ThreadMonitoramento() {

}




void ThreadMonitoramento::monitorarInformacoesCpu(){
    InformacoesCpu informacoesCpu;

    Post postInformacoesCpu("/servidor/1/informacoescpu","172.23.64.255",8081);
    Result *resultInformacoesCpu;
    do{
        informacoesCpu.lerInformacoesCpu();

        resultInformacoesCpu = postInformacoesCpu.exec(informacoesCpu.toJson());

        if(resultInformacoesCpu->getStatus() == 200){
            informacoesCpu.fromJson(resultInformacoesCpu->getResult());
        }else{
            cout << "Erro ao conectar " << endl;
        }
        usleep(1000000);
    }
    while(resultInformacoesCpu->getStatus() != 1000);

    informacoesCpu.print();
}

void ThreadMonitoramento::threadinformacoesCpu(){
    std::thread threadx(monitorarInformacoesCpu);
    threadx.detach();
    cerr << "ThreadMonitoramento::threadinformacoesCpu parou de rodar" << endl;
}



