//
// Created by eduardo on 14/09/17.
//

#include "MonitoramentoCpu.h"
#include "../Util/ConfigFile/ConfigFile.h"
#include "../Util/SystemLog.h"

using namespace std;

MonitoramentoCpu::MonitoramentoCpu() {}

MonitoramentoCpu::~MonitoramentoCpu() {}


void MonitoramentoCpu::lerMonitorarCpu(){

    try {
        chdir("/proc/");
        ConfigFile configFile("cpuinfo", ":");
        configFile.load();
        SystemLog::execLog('l',"MonitoramentoCpu: Lendo arquivo de configurações locais.");

        setNumeroNucleos(configFile.getInt("core id"));

        string cacheSize =  configFile.getString("cpu MHz");
        setCpuMhz(std::stol(cacheSize,nullptr,0));


    } catch (FileNotFoundException &ex) {
        std::cerr << ex.what() << std::endl;
    } catch (InvalidPropertyName &ex) {
        std::cerr << ex.what() << std::endl;
    }
}


void MonitoramentoCpu::monitorarMonitoramentoCpu(ServidorConfig *srvConfig, InformacoesCpu *informacoesCpu, MonitoramentoCpu *monitoramentoCpu){

    Result *result;
    monitoramentoCpu->setInformacoesCpu(informacoesCpu);
    do{
        string path = "/servidor/informacoes/"+to_string(informacoesCpu->getId())+"/monitoramentocpu";
        Post post(path, srvConfig->getHostMonitoramento(), srvConfig->getPorta());
        monitoramentoCpu->lerMonitorarCpu();

        result = post.exec(monitoramentoCpu->toJson());
        if(result->getStatus() == 200){
            //monitoramentoCpu->fromJson(result->getResult());
            SystemLog::execLog('l',"MonitoramentoCpu: "+srvConfig->getHostMonitoramento()+":"+to_string(srvConfig->getPorta())+ path);
        }else{
            SystemLog::execLog('e',"MonitoramentoCpu: Status:"+result->getResult() +" erro:"+ result->getError());
            SystemLog::execLog('e',"json: "+monitoramentoCpu->toJson());

        }
        sleep(srvConfig->getIntervaloCpu());
    }
    while(true);
}

void MonitoramentoCpu::threadMonitorarMonitoramentoCpu(ServidorConfig *srvConfig, InformacoesCpu *informacoesCpu, MonitoramentoCpu *monitoramentoCpu){
    SystemLog::execLog('l',"MonitoramentoCpu: Iniciando Thread Sincronizar Config local com API");
    std::thread threadx(monitorarMonitoramentoCpu, srvConfig, informacoesCpu, monitoramentoCpu);
    threadx.detach();
};

std::string MonitoramentoCpu::toJson(){
    SystemLog::execLog('l',"MonitoramentoCpu: Tranformando Objeto em Json;");
    ptree pt;
    pt.put ("numeroNucleos", getNumeroNucleos());
    pt.put ("cpuMhz", getCpuMhz());
    pt.put ("informacoesCpu.id", informacoesCpu->getId());

    std::ostringstream buf;
    write_json (buf, pt, false);
    string json = buf.str();
    return  json;
}

bool MonitoramentoCpu::fromJson(const std::string &json){
    SystemLog::execLog('l',"MonitoramentoCpu: Trasformando o json em objeto");
    ptree pt2;
    std::istringstream is (json);
    read_json (is, pt2);

    setNumeroNucleos(pt2.get<long> ("numeroNucleos"));
    setCpuMhz(pt2.get<long> ("cpuMhz"));

    return true;
}
void MonitoramentoCpu::print() {
    cout << "---------MonitoramentoCpu-------------" << endl;
    cout << "numeroNucleos: " << getNumeroNucleos() << endl;
    cout << "cpuMhz: " << getCpuMhz() << endl;
    cout << "-------------------------"<< endl;
}
