//
// Created by eduardo on 17/10/17.
//

#include <thread>
#include "MonitoramentoPostgres.h"
#include "../Util/SystemLog.h"
#include "../Util/SystemData.h"
#include "../Util/resource/Resource.h"

MonitoramentoPostgres::MonitoramentoPostgres() {
    servidorConfigDb = new ServidorConfigDb;
}

MonitoramentoPostgres::~MonitoramentoPostgres() {
    if(threadx != nullptr){
        delete threadx;
    }
    if(servidorConfigDb != nullptr){
        delete servidorConfigDb;
    }

}

void MonitoramentoPostgres::lerMonitorarPostgres(MonitoramentoPostgres *monitoramentoPostgres){

    monitoramentoPostgres->setTipoExecucao(monitoramentoPostgres->getServidorConfigDb()->getSgdbTipoExec());

    if (monitoramentoPostgres->getTipoExecucao().compare("BACKUP") == 0) {

        string pg_dumpComando = "pg_dump -Fc -v -b "
                                " -f "+ monitoramentoPostgres->getServidorConfigDb()->getNomeDb() + SystemData::dataHora()+".sql "+
                                " -h "+monitoramentoPostgres->getServidorConfigDb()->getIp() +
                                " -p "+to_string(monitoramentoPostgres->getServidorConfigDb()->getPorta()) +
                                " -U postgres " + monitoramentoPostgres->getServidorConfigDb()->getNomeDb();

        SystemLog::execLog('l', "MonitoramentoPostgres{" + threadId + "}:" + pg_dumpComando);

        char *aux = new char[pg_dumpComando.length() + 1];

        std::strcpy(aux, pg_dumpComando.c_str());
        monitoramentoPostgres->setExito(std::system(aux));

        delete[] aux;
        return;
    }

    if (monitoramentoPostgres->getTipoExecucao().compare("VACUUM") == 0) {

        string vacuumdbComando = "vacuumdb -f -U " + monitoramentoPostgres->getServidorConfigDb()->getNomeDb() +
                                    " -h "+monitoramentoPostgres->getServidorConfigDb()->getIp() +
                                    " -p "+to_string(monitoramentoPostgres->getServidorConfigDb()->getPorta()) +
                                    " postgres > vacuumdb.log";

        SystemLog::execLog('l', "MonitoramentoPostgres{" + threadId + "}:" + vacuumdbComando);

        char *aux = new char[vacuumdbComando.length() + 1];

        std::strcpy(aux, vacuumdbComando.c_str());
        monitoramentoPostgres->setExito(std::system(aux));

        delete[] aux;
        return;
    }

        SystemLog::execLog('e',"MonitoramentoPostgres{" + threadId + "}: O tipo passado não foi um VACUUM nem um BACKUP");

};

void MonitoramentoPostgres::sincronizarConfigLocalComApi(ServidorConfig *srvConfig, ServidorConfigDb *SrvConfigDb, MonitoramentoPostgres *monitoramentoPostgres){

    Result *result;
    //monitoramentoPostgres->setInformacoesMemoria(informacoesMemoria);
    do{
        sleep(SrvConfigDb->getIntervaloExec());
        if(monitoramentoPostgres->getServidorConfigDb()->isAtivo()) {
            string path = "/servidor/informacoes/"+to_string(monitoramentoPostgres->getServidorConfigDb()->getId())+"/monitoramentopostgres";
            Resource resource(path, srvConfig->getHostMonitoramento(), srvConfig->getPorta());

            monitoramentoPostgres->lerMonitorarPostgres(monitoramentoPostgres);

            result = resource.post(monitoramentoPostgres->toJson());

            result->imprimir("MonitoramentoPostgres{"+ monitoramentoPostgres->threadId +"}");

            delete result;
        }else{
            SystemLog::execLog('w',"MonitoramentoPostgres{" + monitoramentoPostgres->threadId + "}: Registro de monitoramento esta desativado.");
        }
    }
    while(srvConfig->isFicarMonitorando());
};

string MonitoramentoPostgres::toJson(){
    ptree pt;
    pt.put ("servidorConfigDb.id", getServidorConfigDb()->getId());
    pt.put ("tipoExecucao", getTipoExecucao());
    pt.put ("exito", getExito());
    pt.put ("mensagem", getMensagem());

    std::ostringstream buf;
    write_json (buf, pt, false);
    string json = buf.str();
    return  json;
};

void MonitoramentoPostgres::threadSincronizarConfigLocalComApi(ServidorConfig *srvConfig, ServidorConfigDb *SrvConfigDb, MonitoramentoPostgres *monitoramentoPostgres){
    SystemLog::execLog('l',"MonitoramentoPostgres: Iniciando uma Thread de Sincronizar local com API");
    threadx = new std::thread(sincronizarConfigLocalComApi, srvConfig, SrvConfigDb, monitoramentoPostgres);

    //Salva o id da thread no monitoramentoPostgres.
    auto myid = threadx->get_id();
    stringstream ss;
    ss << myid;
    threadId = ss.str();

};




