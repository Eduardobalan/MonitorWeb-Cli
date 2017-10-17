//
// Created by eduardo on 17/10/17.
//

#include <boost/algorithm/string.hpp>
#include <thread>
#include "MonitoramentoSwap.h"
#include "../Util/ConfigFile/ConfigFile.h"
#include "../Util/SystemLog.h"
#include "../Util/verbosHttp/Result.h"
#include "../Util/verbosHttp/Post.h"

MonitoramentoSwap::MonitoramentoSwap() {}

MonitoramentoSwap::~MonitoramentoSwap() {

}

void MonitoramentoSwap::lerMonitorarSwap(){

    try {
        chdir("/proc/");
        ConfigFile configFile("meminfo", ":");
        configFile.load();
        SystemLog::execLog('l',"MonitoramentoSwap: Lendo arquivo de locais.");


        string SwapFree =  configFile.getString("SwapFree");
        boost::erase_all(SwapFree, " KB");
        setFree(std::stol(SwapFree,nullptr,0));

        string SwapCached =  configFile.getString("SwapCached");
        boost::erase_all(SwapCached, " KB");
        setCached(std::stol(SwapCached,nullptr,0));

    } catch (FileNotFoundException &ex) {
        std::cerr << ex.what() << std::endl;
    } catch (InvalidPropertyName &ex) {
        std::cerr << ex.what() << std::endl;
    }

};

void MonitoramentoSwap::monitorarMonitoramentoSwap(ServidorConfig *srvConfig, InformacoesSwap *informacoesSwap, MonitoramentoSwap *monitoramentoSwap){

    Result *result;
    monitoramentoSwap->setInformacoesSwap(informacoesSwap);
    do{
        string path = "/servidor/informacoes/"+to_string(informacoesSwap->getId())+"/monitoramentoswap";
        Post post(path, srvConfig->getHostMonitoramento(), srvConfig->getPorta());
        monitoramentoSwap->lerMonitorarSwap();

        result = post.exec(monitoramentoSwap->toJson());
        if(result->getStatus() == 200){
            //monitoramentoCpu->fromJson(result->getResult());
            SystemLog::execLog('l',"MonitoramentoSwap: "+srvConfig->getHostMonitoramento()+":"+to_string(srvConfig->getPorta())+ path);
        }else{
            SystemLog::execLog('e',"MonitoramentoSwap: Status:"+result->getResult() +" erro:"+ result->getError());
            SystemLog::execLog('e',"json: "+monitoramentoSwap->toJson());

        }
        sleep(srvConfig->getIntervaloSwap());
    }
    while(true);
};

void MonitoramentoSwap::threadMonitorarMonitoramentoSwap(ServidorConfig *srvConfig, InformacoesSwap *informacoesSwap, MonitoramentoSwap *monitoramentoSwap){
    SystemLog::execLog('l',"MonitoramentoSwap: Iniciando Thread");
    std::thread threadx(monitorarMonitoramentoSwap, srvConfig, informacoesSwap, monitoramentoSwap);
    threadx.detach();
};

string MonitoramentoSwap::toJson(){
    SystemLog::execLog('l',"MonitoramentoSwap: Tranformando Objeto em Json;");

    ptree pt;
    pt.put ("free", getFree());
    pt.put ("cached", getCached());
    pt.put ("informacoesSwap.id", informacoesSwap->getId());

    std::ostringstream buf;
    write_json (buf, pt, false);
    string json = buf.str();
    return  json;
};

bool MonitoramentoSwap::fromJson(const std::string &json){
    SystemLog::execLog('l',"MonitoramentoSwap: Trasformando o json em objeto");
    ptree pt2;
    std::istringstream is (json);
    read_json (is, pt2);

    setFree(pt2.get<long> ("free"));
    setCached(pt2.get<long> ("cached"));

    return true;
};

