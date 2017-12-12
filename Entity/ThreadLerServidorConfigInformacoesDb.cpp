//
// Created by eduardo on 13/11/17.
//

#include <thread>
#include "ThreadLerServidorConfigInformacoesDb.h"
#include "../Util/SystemLog.h"
#include "../Util/resource/Resource.h"

ThreadLerServidorConfigInformacoesDb::ThreadLerServidorConfigInformacoesDb() {}

ThreadLerServidorConfigInformacoesDb::~ThreadLerServidorConfigInformacoesDb() {
    if(threadx != nullptr){
        delete threadx;
    }
}


bool ThreadLerServidorConfigInformacoesDb::fromJson(const std::string &json, ServidorConfig *srvConfig, std::map<long, MonitoramentoPostgresInformacoes*>  *mapMonitoramentoPostgresInformacoes){
    ptree pt2;
    std::istringstream is (json);
    read_json (is, pt2);

    //Map auxiliar, para saber se um elemento foi removido do map principal
    std::map<long, MonitoramentoPostgresInformacoes*>  *aux = new std::map<long, MonitoramentoPostgresInformacoes*> ;
    aux->clear();

    bool novoRegistro = false;

    //percore o json pegando objeto por objeto;
    for(const ptree::value_type& child :  pt2.get_child("")) {

        novoRegistro = false;

        //pega o id do objeto
        long idKey = child.second.get<long>("id");

        //
        if (mapMonitoramentoPostgresInformacoes->find(idKey) == mapMonitoramentoPostgresInformacoes->end()) {
            novoRegistro = true;
            mapMonitoramentoPostgresInformacoes->insert(pair<long, MonitoramentoPostgresInformacoes*>(idKey, new MonitoramentoPostgresInformacoes()));
            SystemLog::execLog('l',"ThreadLerServidorConfigInformacoesDb: Novo registro de monitoramento inserido com id = "+to_string(idKey));
        }

        aux->insert(pair<long, MonitoramentoPostgresInformacoes*> (idKey, mapMonitoramentoPostgresInformacoes->at(idKey)));

        mapMonitoramentoPostgresInformacoes->at(idKey)->getServidorConfigInformacoesDb()->setId(child.second.get<long>("id"));
        mapMonitoramentoPostgresInformacoes->at(idKey)->getServidorConfigInformacoesDb()->setNomeSgdb(child.second.get<string>("nomeSgdb"));
        mapMonitoramentoPostgresInformacoes->at(idKey)->getServidorConfigInformacoesDb()->setPathMain(child.second.get<string>("pathMain"));
        mapMonitoramentoPostgresInformacoes->at(idKey)->getServidorConfigInformacoesDb()->setIntervaloExec(child.second.get<long>("intervaloExec"));
        mapMonitoramentoPostgresInformacoes->at(idKey)->getServidorConfigInformacoesDb()->setAtivo(child.second.get<bool>("ativo"));

        //inicia a thread se for um novo registro
        if(novoRegistro){
            //Inicia a thread de monitoramento
            mapMonitoramentoPostgresInformacoes->at(idKey)->threadMonitorarMonitoramentoPostgresInformacoes(srvConfig, mapMonitoramentoPostgresInformacoes->at(idKey)->getServidorConfigInformacoesDb(), mapMonitoramentoPostgresInformacoes->at(idKey));
        }
    }

    std::map<long, MonitoramentoPostgresInformacoes*>::iterator it;
    for(it =  mapMonitoramentoPostgresInformacoes->begin(); it !=  mapMonitoramentoPostgresInformacoes->end(); ++it){

        if (aux->find(it->first) == aux->end()) {
            SystemLog::execLog('l',"ThreadLerServidorConfigInformacoesDb: Removendo registro de monitoramento com id = "+to_string(it->first));
            delete mapMonitoramentoPostgresInformacoes->at(it->first);
            mapMonitoramentoPostgresInformacoes->erase(it->first);
        }
    }

    delete aux;
    return true;
}


void ThreadLerServidorConfigInformacoesDb::sincronizarConfigLocalComApi(ServidorConfig *srvConfig, std::map<long, MonitoramentoPostgresInformacoes*>  *mapMonitoramentoPostgresInformacoes){

    Result *result;
    do{
        string path = "/servidor/"+ to_string(srvConfig->getServidor().getId()) +"/servidorconfiguracoesinformacoesdb/";
        Resource resource(path, srvConfig->getHostMonitoramento(), srvConfig->getPorta());
        result = resource.get();
        if(result->getStatus() == 200){
            fromJson(result->getResult(), srvConfig, mapMonitoramentoPostgresInformacoes);
        }
        result->imprimir("ThreadLerServidorConfigInformacoesDb");
        delete result;
        sleep(srvConfig->getIntervaloLeituraConfiguracoesDb());
    }
    while(srvConfig->isFicarMonitorando());

    // finaliza as threads
    std::map<long, MonitoramentoPostgresInformacoes*>::iterator it =  mapMonitoramentoPostgresInformacoes->begin();
    while(it != mapMonitoramentoPostgresInformacoes->end()){
        if(it->second->getThreadx() != nullptr){
            it->second->getThreadx()->join();
            delete mapMonitoramentoPostgresInformacoes->at(it->first);
        }
        it ++;
    }
    mapMonitoramentoPostgresInformacoes->clear();
};

void ThreadLerServidorConfigInformacoesDb::threadSincronizarConfigLocalComApi(ServidorConfig *srvConfig, std::map<long, MonitoramentoPostgresInformacoes*> *mapMonitoramentoPostgresInformacoes){
    SystemLog::execLog('l',"ThreadLerServidorConfigInformacoesDb: Iniciando Thread");
    threadx = new std::thread(sincronizarConfigLocalComApi, srvConfig, mapMonitoramentoPostgresInformacoes);
}