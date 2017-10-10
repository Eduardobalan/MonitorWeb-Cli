//
// Created by eduardo on 29/09/17.
//
#include <stdlib.h>
#include <iostream>
#include "Entity/Servidor.h"
#include "Entity/InformacoesCpu.h"
#include "Entity/ServidorConfig.h"
#include "Util/verbosHttp/Get.h"
#include "Util/verbosHttp/Post.h"

//#include "Entity/InformacoesCpu.h"

using namespace std;

int main(int argc, char* argv[]) {

    bool log = true;

    Servidor servidor;
    servidor.setId(1);


    //#########################################################################
    //########## Inicializa Informações servidor configurações ################
    //#########################################################################

    ServidorConfig servidorConfig;

    Get getServidorConfig("/servidor/"+ to_string(servidor.getId()) +"/servidorconfiguracoes/1","172.23.64.255",8081);
    Result *resultServidorConfig;
    do{
        resultServidorConfig = getServidorConfig.exec();
        if(resultServidorConfig->getStatus() == 200){
            servidorConfig.fromJson(resultServidorConfig->getResult());
        }else{
            cout << "Erro ao conectar " << endl;
        }
    }
    while(resultServidorConfig->getStatus() != 200);

    servidorConfig.print();


    //#########################################################################
    //#################### Inicializa Informações Cpu #########################
    //#########################################################################

    //Inicializa Informações Cpu
    InformacoesCpu informacoesCpu;
    informacoesCpu.lerInformacoesCpu();

    Post postInformacoesCpu("/servidor/"+ to_string(servidor.getId()) +"/informacoescpu","172.23.64.255",8081);
    Result *resultInformacoesCpu;
    do{
        resultInformacoesCpu = postInformacoesCpu.exec(informacoesCpu.toJson());
        if(resultInformacoesCpu->getStatus() == 200){
            informacoesCpu.fromJson(resultInformacoesCpu->getResult());
        }else{
            cout << "Erro ao conectar " << endl;
        }
    }
    while(resultInformacoesCpu->getStatus() != 200);

    informacoesCpu.print();


    return 0;

}