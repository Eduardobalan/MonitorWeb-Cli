//
// Created by eduardo on 14/09/17.
//

#include "MonitoramentoCpu.h"
#include "../Util/ConfigFile/ConfigFile.h"
#include "../Util/resource/Resource.h"

using namespace std;

MonitoramentoCpu::MonitoramentoCpu() {}

MonitoramentoCpu::~MonitoramentoCpu() {
    if(threadx != nullptr){
        delete threadx;
    }
}


void MonitoramentoCpu::lerMonitorarCpu(){

    try {
        chdir("/proc/");
        ConfigFile configFile("cpuinfo", ":", true);
        configFile.load();

        setNumeroNucleos(configFile.getInt("cpu cores"));

        std::vector<string> vectorCoreId = configFile.getVector("core id");
        setCoreId(std::stol(vectorCoreId[getNumeroNucleoMonitorado()],nullptr,0));

        std::vector<string> vectorCpuMhz = configFile.getVector("cpu MHz");
        setCpuMhz(std::stol(vectorCpuMhz[getNumeroNucleoMonitorado()],nullptr,0));


        if(configFile.getInt("cpu cores")-1 != getNumeroNucleoMonitorado()){
            setNumeroNucleoMonitorado(getNumeroNucleoMonitorado()+1);
        }else{
            setNumeroNucleoMonitorado(0);
        }

    } catch (FileNotFoundException &ex) {
        std::cout << ex.what() << std::endl;
    } catch (InvalidPropertyName &ex) {
        std::cout << ex.what() << std::endl;
    }
}


void MonitoramentoCpu::monitorarMonitoramentoCpu(ServidorConfig *srvConfig, InformacoesCpu *informacoesCpu, MonitoramentoCpu *monitoramentoCpu){

    Result *result;
    monitoramentoCpu->setInformacoesCpu(informacoesCpu);

    do{
        string path = "/servidor/informacoes/"+to_string(informacoesCpu->getId())+"/monitoramentocpu";
        Resource  resource(path, srvConfig->getHostMonitoramento(), srvConfig->getPorta());

        monitoramentoCpu->lerMonitorarCpu();

        result = resource.post(monitoramentoCpu->toJson());

        result->imprimir("MonitoramentoCpu core ID = "+to_string(monitoramentoCpu->getCoreId()));

        delete result;

        //divide o tempo pelo numero de nucleos que o processador tem;


        usleep(monitoramentoCpu->getNumeroNucleos() > 0 ? (srvConfig->getIntervaloCpu()*1000000) / monitoramentoCpu->getNumeroNucleos() : srvConfig->getIntervaloCpu()*1000000);
    }
    while(srvConfig->isFicarMonitorando());
}

void MonitoramentoCpu::threadMonitorarMonitoramentoCpu(ServidorConfig *srvConfig, InformacoesCpu *informacoesCpu, MonitoramentoCpu *monitoramentoCpu){
    SystemLog::execLog('l',"MonitoramentoCpu: Iniciando Thread ");
    threadx = new std::thread(monitorarMonitoramentoCpu, srvConfig, informacoesCpu, monitoramentoCpu);
};

std::string MonitoramentoCpu::toJson(){
    ptree pt;
    pt.put ("coreId", getCoreId());
    pt.put ("cpuMhz", getCpuMhz());
    pt.put ("informacoesCpu.id", informacoesCpu->getId());

    std::ostringstream buf;
    write_json (buf, pt, false);
    string json = buf.str();
    return  json;
}

bool MonitoramentoCpu::fromJson(const std::string &json){
    ptree pt2;
    std::istringstream is (json);
    read_json (is, pt2);

    setCoreId(pt2.get<long> ("coreId"));
    setCpuMhz(pt2.get<long> ("cpuMhz"));

    return true;
}
void MonitoramentoCpu::print() {
    cout << "---------MonitoramentoCpu-------------" << endl;
    cout << "numeroNucleos: " << getNumeroNucleos() << endl;
    cout << "cpuMhz: " << getCpuMhz() << endl;
    cout << "-------------------------"<< endl;
}
