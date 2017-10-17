//
// Created by eduardo on 17/10/17.
//

#include <thread>
#include <boost/algorithm/string.hpp>
#include "MonitoramentoMemoria.h"
#include "../Util/ConfigFile/ConfigFile.h"
#include "../Util/SystemLog.h"
#include "../Util/verbosHttp/Post.h"

MonitoramentoMemoria::MonitoramentoMemoria() {}

MonitoramentoMemoria::~MonitoramentoMemoria() {

}


void MonitoramentoMemoria::lerMonitorarMemoria(){

    try {
        chdir("/proc/");
        ConfigFile configFile("meminfo", ":");
        configFile.load();
        SystemLog::execLog('l',"MonitoramentoMemoria: Lendo arquivo de locais.");


        string Active =  configFile.getString("Active");
        boost::erase_all(Active, " KB");
        setActive(std::stol(Active,nullptr,0));

        string MemFree =  configFile.getString("MemFree");
        boost::erase_all(MemFree, " KB");
        setMemfree(std::stol(MemFree,nullptr,0));

        string MemAvailable =  configFile.getString("MemAvailable");
        boost::erase_all(MemAvailable, " KB");
        setAvailabre(std::stol(MemAvailable,nullptr,0));

        string buffers =  configFile.getString("Buffers");
        boost::erase_all(buffers, " KB");
        setBuffers(std::stol(buffers,nullptr,0));


    } catch (FileNotFoundException &ex) {
        std::cerr << ex.what() << std::endl;
    } catch (InvalidPropertyName &ex) {
        std::cerr << ex.what() << std::endl;
    }
}


void MonitoramentoMemoria::monitorarMonitoramentoMemoria(ServidorConfig *srvConfig, InformacoesMemoria *informacoesMemoria, MonitoramentoMemoria *monitoramentoMemoria){

    Result *result;
    monitoramentoMemoria->setInformacoesMemoria(informacoesMemoria);
    do{
        string path = "/servidor/informacoes/"+to_string(informacoesMemoria->getId())+"/monitoramentomemoria";
        Post post(path, srvConfig->getHostMonitoramento(), srvConfig->getPorta());
        monitoramentoMemoria->lerMonitorarMemoria();

        result = post.exec(monitoramentoMemoria->toJson());
        if(result->getStatus() == 200){
            //monitoramentoCpu->fromJson(result->getResult());
            SystemLog::execLog('l',"MonitoramentoMemoria: "+srvConfig->getHostMonitoramento()+":"+to_string(srvConfig->getPorta())+ path);
        }else{
            SystemLog::execLog('e',"MonitoramentoMemoria: Status:"+result->getResult() +" erro:"+ result->getError());
            SystemLog::execLog('e',"json: "+monitoramentoMemoria->toJson());

        }
        sleep(srvConfig->getIntervaloCpu());
    }
    while(true);
}

void MonitoramentoMemoria::threadMonitorarMonitoramentoMemoria(ServidorConfig *srvConfig, InformacoesMemoria *informacoesMemoria, MonitoramentoMemoria *monitoramentoMemoria){
    SystemLog::execLog('l',"MonitoramentoMemoria: Iniciando Thread Sincronizar Config local com API");
    std::thread threadx(monitorarMonitoramentoMemoria, srvConfig, informacoesMemoria, monitoramentoMemoria);
    threadx.detach();
};

std::string MonitoramentoMemoria::toJson(){
    SystemLog::execLog('l',"MonitoramentoMemoria: Tranformando Objeto em Json;");

    ptree pt;
    pt.put ("active", getActive());
    pt.put ("memfree", getMemfree());
    pt.put ("informacoesMemoria.id", informacoesMemoria->getId());
    pt.put ("availabre", getAvailabre());
    pt.put ("buffers", getBuffers());

    std::ostringstream buf;
    write_json (buf, pt, false);
    string json = buf.str();
    return  json;
}

bool MonitoramentoMemoria::fromJson(const std::string &json){
    SystemLog::execLog('l',"MonitoramentoMemoria: Trasformando o json em objeto");
    ptree pt2;
    std::istringstream is (json);
    read_json (is, pt2);

    setActive(pt2.get<long> ("active"));
    setMemfree(pt2.get<long> ("memfree"));
    setAvailabre(pt2.get<long> ("availabre"));
    setBuffers(pt2.get<long> ("buffers"));

    return true;
}

