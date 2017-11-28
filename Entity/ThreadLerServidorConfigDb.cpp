//
// Created by eduardo on 09/11/17.
//

#include <thread>
#include "ThreadLerServidorConfigDb.h"
#include "../Util/SystemLog.h"
#include "../Util/resource/Resource.h"

ThreadLerServidorConfigDb::ThreadLerServidorConfigDb() {}

ThreadLerServidorConfigDb::~ThreadLerServidorConfigDb() {
    if(threadx != nullptr){
        delete threadx;
    }
}

bool ThreadLerServidorConfigDb::fromJson(const std::string &json, ServidorConfig *srvConfig, std::map<long, MonitoramentoPostgres*>  *mapMonitoramentoPostgres){
    ptree pt2;
    std::istringstream is (json);
    read_json (is, pt2);

    //Map auxiliar, para saber se um elemento foi removido do map principal
    std::map<long, MonitoramentoPostgres*>  *aux = new std::map<long, MonitoramentoPostgres*> ;
    aux->clear();

    bool novoRegistro = false;

    //percore o json pegando objeto por objeto;
    for(const ptree::value_type& child :  pt2.get_child("")) {

        novoRegistro = false;

        //pega o id do objeto
        long idKey = child.second.get<long>("id");

        //
        if (mapMonitoramentoPostgres->find(idKey) == mapMonitoramentoPostgres->end()) {
            novoRegistro = true;
            mapMonitoramentoPostgres->insert(pair<long, MonitoramentoPostgres*>(idKey, new MonitoramentoPostgres()));
            SystemLog::execLog('l',"ThreadLerServidorConfigDb: Novo registro de monitoramento inserido com id = "+to_string(idKey));
        }

        aux->insert(pair<long, MonitoramentoPostgres*> (idKey, mapMonitoramentoPostgres->at(idKey)));

        mapMonitoramentoPostgres->at(idKey)->getServidorConfigDb()->setId(child.second.get<long>("id"));
        mapMonitoramentoPostgres->at(idKey)->getServidorConfigDb()->setNomeSgdb(child.second.get<string>("nomeSgdb"));
        mapMonitoramentoPostgres->at(idKey)->getServidorConfigDb()->setSgdbTipoExec(child.second.get<string>("sgdbTipoExec"));
        mapMonitoramentoPostgres->at(idKey)->getServidorConfigDb()->setNomeDb(child.second.get<string>("nomeDb"));
        mapMonitoramentoPostgres->at(idKey)->getServidorConfigDb()->setPathMain(child.second.get<string>("pathMain"));
        mapMonitoramentoPostgres->at(idKey)->getServidorConfigDb()->setIp(child.second.get<string>("ip"));
        mapMonitoramentoPostgres->at(idKey)->getServidorConfigDb()->setPorta(child.second.get<long>("porta"));
        mapMonitoramentoPostgres->at(idKey)->getServidorConfigDb()->setVersao(child.second.get<string>("versao"));
        mapMonitoramentoPostgres->at(idKey)->getServidorConfigDb()->setIntervaloExec(child.second.get<long>("intervaloExec"));
        mapMonitoramentoPostgres->at(idKey)->getServidorConfigDb()->setAtivo(child.second.get<bool>("ativo"));

        //inicia a thread se for um novo registro
        if(novoRegistro){
            //Inicia a thread de monitoramento
            mapMonitoramentoPostgres->at(idKey)->threadSincronizarConfigLocalComApi(srvConfig, mapMonitoramentoPostgres->at(idKey)->getServidorConfigDb(), mapMonitoramentoPostgres->at(idKey));
        }
    }

    std::map<long, MonitoramentoPostgres*>::iterator it;
    for(it =  mapMonitoramentoPostgres->begin(); it !=  mapMonitoramentoPostgres->end(); ++it){

        if (aux->find(it->first) == aux->end()) {
            SystemLog::execLog('l',"ThreadLerServidorConfigDb: Removendo registro de monitoramento com id = "+to_string(it->first));
            delete mapMonitoramentoPostgres->at(it->first);
            mapMonitoramentoPostgres->erase(it->first);
        }
    }

    delete aux;
    return true;
}


void ThreadLerServidorConfigDb::sincronizarConfigLocalComApi(ServidorConfig *srvConfig, std::map<long, MonitoramentoPostgres*>  *mapMonitoramentoPostgres){

    Result *result;
    ServidorConfigDb servidorConfigDb;
    do{
        string path = "/servidor/"+ to_string(srvConfig->getServidor().getId()) +"/servidorconfiguracoesdb/";
        Resource resource(path, srvConfig->getHostMonitoramento(), srvConfig->getPorta());
        result = resource.get();
        if(result->getStatus() == 200){
            fromJson(result->getResult(), srvConfig, mapMonitoramentoPostgres);
        }
        result->imprimir("ThreadLerServidorConfigDb");
        delete result;
        sleep(srvConfig->getIntervaloLeituraConfiguracoesDb());
    }
    while(srvConfig->isFicarMonitorando());

    // finaliza as threads
    std::map<long, MonitoramentoPostgres*>::iterator it =  mapMonitoramentoPostgres->begin();
    while(it != mapMonitoramentoPostgres->end()){
        if(it->second->getThreadx() != nullptr){
            it->second->getThreadx()->join();
            delete mapMonitoramentoPostgres->at(it->first);
        }
        it ++;
    }
    mapMonitoramentoPostgres->clear();
};

void ThreadLerServidorConfigDb::threadSincronizarConfigLocalComApi(ServidorConfig *srvConfig, std::map<long, MonitoramentoPostgres*> *mapMonitoramentoPostgres){
    SystemLog::execLog('l',"ThreadLerServidorConfigDb: Iniciando Thread");
    threadx = new std::thread(sincronizarConfigLocalComApi, srvConfig, mapMonitoramentoPostgres);
}