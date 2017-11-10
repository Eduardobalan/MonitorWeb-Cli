//
// Created by eduardo on 09/11/17.
//

#include <thread>
#include "ThreadLerServidorConfigDb.h"
#include "../Util/verbosHttp/Result.h"
#include "../Util/verbosHttp/Get.h"
#include "../Util/SystemLog.h"


bool ThreadLerServidorConfigDb::fromJson(const std::string &json, ServidorConfig *srvConfig, std::map<long, MonitoramentoPostgres*>  *mapMonitoramentoPostgres){
    SystemLog::execLog('l',"ThreadLerServidorConfigDb: Trasformando o json em objetos");
    ptree pt2;
    std::istringstream is (json);
    read_json (is, pt2);

    //Map auxiliar, para saber se um elemento foi removido do map principal
    std::map<long, MonitoramentoPostgres*>  *aux = new std::map<long, MonitoramentoPostgres*> ;
    aux->clear();

    bool novoRegistro = false;

    //percore o json pegando objeto por objeto;
    for(const ptree::value_type& child :  pt2.get_child("")) {

        //pega o id do objeto
        long idKey = child.second.get<long>("id");


        if (mapMonitoramentoPostgres->find(idKey) != mapMonitoramentoPostgres->end()) {
            cout << idKey << "id existe" << endl;
            novoRegistro = false;
        } else {
            novoRegistro = true;
            cout << idKey << "id não existe" << endl;
            MonitoramentoPostgres *montPostgres = new MonitoramentoPostgres();
            mapMonitoramentoPostgres->insert(pair<long, MonitoramentoPostgres*>(idKey, montPostgres));
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


        //inicia a thread se for um novo registro
        cout << "aqui" << endl;
        if(novoRegistro){
            //Inicia a thread de monitoramento
            cout << "iniciou thread" << endl;
            mapMonitoramentoPostgres->at(idKey)->threadSincronizarConfigLocalComApi(srvConfig, mapMonitoramentoPostgres->at(idKey)->getServidorConfigDb(), mapMonitoramentoPostgres->at(idKey));
        }
        novoRegistro = false;
    }

    std::map<long, MonitoramentoPostgres*>::iterator it;
    cout << "___________________________________________________" << endl;
    for(it =  mapMonitoramentoPostgres->begin(); it !=  mapMonitoramentoPostgres->end(); ++it){

        if (aux->find(it->first) != aux->end()) {
            cout << it->first << "id existe nos 2 maps" << endl;
        } else {
            cout << it->first << "id não existe no mpas aux" << endl;
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
        Get get(path, srvConfig->getHostMonitoramento(), srvConfig->getPorta());
        result = get.exec();
        if(result->getStatus() == 200){
            fromJson(result->getResult(), srvConfig, mapMonitoramentoPostgres);
            SystemLog::execLog('l',"ThreadLerServidorConfigDb: Lendo api configurações do servidor db:."+srvConfig->getHostMonitoramento()+":"+to_string(srvConfig->getPorta())+ path);
        }else{
            SystemLog::execLog('e',"ThreadLerServidorConfigDb: Lendo api configurações do servidor db:\n "
                                           "Status:"+result->getResult() +" \n erro:"+ result->getError()+" URL:"+srvConfig->getHostMonitoramento()+":"+to_string(srvConfig->getPorta())+ path);
        }
        delete result;
        sleep(srvConfig->getIntervaloLeituraConfiguracoesDb());
    }
    while(true);

};

void ThreadLerServidorConfigDb::threadSincronizarConfigLocalComApi(ServidorConfig *srvConfig, std::map<long, MonitoramentoPostgres*> *mapMonitoramentoPostgres){
    SystemLog::execLog('l',"ThreadLerServidorConfigDb: Iniciando Thread");
    std::thread threadx(sincronizarConfigLocalComApi, srvConfig, mapMonitoramentoPostgres);
    threadx.detach();
}