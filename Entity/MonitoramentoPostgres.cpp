//
// Created by eduardo on 17/10/17.
//

#include <thread>
#include "MonitoramentoPostgres.h"
#include "../Util/SystemLog.h"
#include "../Util/verbosHttp/Result.h"
#include "../Util/verbosHttp/Post.h"
#include "../Util/SystemData.h"

MonitoramentoPostgres::MonitoramentoPostgres() {
    servidorConfigDb = new ServidorConfigDb;
}

MonitoramentoPostgres::~MonitoramentoPostgres() {
    if(thread != nullptr){
        delete thread;
    }
    if(servidorConfigDb != nullptr){
        delete servidorConfigDb;
    }

}

void MonitoramentoPostgres::lerMonitorarPostgres(MonitoramentoPostgres *monitoramentoPostgres){

    monitoramentoPostgres->setTipoExecucao(monitoramentoPostgres->getServidorConfigDb()->getSgdbTipoExec());

    if(monitoramentoPostgres->getTipoExecucao().compare("BACKUP") == 0){

        string pg_dumpComando = "pg_dump -Fc -v -b -f "+
                monitoramentoPostgres->getServidorConfigDb()->getNomeDb() + SystemData::dataHora() +
                ".sql -U postgres "+monitoramentoPostgres->getServidorConfigDb()->getNomeDb()+
                " > BackupLog.log";

        SystemLog::execLog('l',"MonitoramentoPostgres{"+ threadId +"}:"+pg_dumpComando);

        char *aux = new char[pg_dumpComando.length() + 1];

        std::strcpy(aux, pg_dumpComando.c_str());
        monitoramentoPostgres->setExito(std::system(aux));

        delete aux;
        return;
    }

    if(monitoramentoPostgres->getTipoExecucao().compare("VACUUM") == 0){

        string vacuumdbComando = "vacuumdb -f -U "+ monitoramentoPostgres->getServidorConfigDb()->getNomeDb() +" postgres > vacuumdb.log";

        SystemLog::execLog('l',"MonitoramentoPostgres{"+ threadId +"}:"+vacuumdbComando);

        char *aux = new char[vacuumdbComando.length() + 1];

        std::strcpy(aux, vacuumdbComando.c_str());
        monitoramentoPostgres->setExito(std::system(aux));

        delete aux;
        return;
    }

    SystemLog::execLog('e',"MonitoramentoPostgres{"+ threadId +"}: O tipo passado não foi um VACUUM nem um BACKUP");

};

void MonitoramentoPostgres::sincronizarConfigLocalComApi(ServidorConfig *srvConfig, ServidorConfigDb *SrvConfigDb, MonitoramentoPostgres *monitoramentoPostgres){

    Result *result;
    //monitoramentoPostgres->setInformacoesMemoria(informacoesMemoria);
    do{
        sleep(SrvConfigDb->getIntervaloExec());

        string path = "/servidor/informacoes/"+to_string(monitoramentoPostgres->getServidorConfigDb()->getId())+"/monitoramentopostgres";
        Post post(path, srvConfig->getHostMonitoramento(), srvConfig->getPorta());

        monitoramentoPostgres->lerMonitorarPostgres(monitoramentoPostgres);

        result = post.exec(monitoramentoPostgres->toJson());
        if(result->getStatus() == 200){
            //monitoramentoCpu->fromJson(result->getResult());
            SystemLog::execLog('l',"MonitoramentoPostgres{"+ monitoramentoPostgres->threadId +"}: "+srvConfig->getHostMonitoramento()+":"+to_string(srvConfig->getPorta())+ path);
        }else{
            SystemLog::execLog('e',"MonitoramentoPostgres{"+ monitoramentoPostgres->threadId +"}: Status:"+result->getResult() +"\n Erro:"+ result->getError() +"\n Json: "+monitoramentoPostgres->toJson());
        }
        delete result;
    }
    while(true);

};

string MonitoramentoPostgres::toJson(){
    SystemLog::execLog('l',"MonitoramentoPostgres{"+ threadId +"}: Tranformando Objeto em Json;");

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
    SystemLog::execLog('l',"MonitoramentoPostgres: Iniciando Thread Sincronizar local com API");
    thread = new std::thread(sincronizarConfigLocalComApi, srvConfig, SrvConfigDb, monitoramentoPostgres);


    //Salva o id da thread no monitoramentoPostgres.
    auto myid = thread->get_id();
    stringstream ss;
    ss << myid;
    threadId = ss.str();

    thread->detach();
};




